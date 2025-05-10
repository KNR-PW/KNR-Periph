#include <Arduino.h>

static constexpr uint8_t ESC1 = PB4;    // TIM3_CH1
static constexpr uint8_t ESC2 = PB6;    // TIM4_CH1

static constexpr uint16_t MIN_US    = 1000;  // 1 ms
static constexpr uint16_t MAX_US    = 2000;  // 2 ms
static constexpr uint16_t PERIOD_US = 20000; // 20 ms → 50 Hz
static constexpr uint8_t  RES_BITS  = 12;    // 12‐bit resolution

// konwertuje microsec. → 0…(2^12−1)
static uint16_t toDuty(uint16_t us) {
  float f = float(us) / float(PERIOD_US);
  return uint16_t(f * ((1u << RES_BITS) - 1));
}

void setup() {
  // poczekaj, aż ESC dostanie zasilanie
  delay(500);

  // globalne ustawienie czestotliwosci PWM
  analogWriteFrequency(50);      // 50 Hz
  analogWriteResolution(RES_BITS);

  pinMode(ESC1, OUTPUT);
  pinMode(ESC2, OUTPUT);

  // ARMING: minimalny throttle przez 2 s
  uint16_t d = toDuty(MIN_US);
  analogWrite(ESC1, d);
  analogWrite(ESC2, d);
  delay(2000);
}

void loop() {
  //
  for (uint16_t us = MIN_US; us <= MAX_US; us += 10) {
    uint16_t d = toDuty(us);
    analogWrite(ESC1, d);
    analogWrite(ESC2, d);
    delay(20);
  }
  for (int us = MAX_US; us >= int(MIN_US); us -= 10) {
    uint16_t d = toDuty(us);
    analogWrite(ESC1, d);
    analogWrite(ESC2, d);
    delay(20);
  }
}
