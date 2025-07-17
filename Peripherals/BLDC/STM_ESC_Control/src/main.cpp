#include <Arduino.h>

/*   UART TX=PB6, RX=PB7  */
#define GPS_UART_TX PA9
#define GPS_UART_RX PA10
HardwareSerial SerialPom(GPS_UART_RX, GPS_UART_TX);

static constexpr uint8_t ESC1 = PB4;    // TIM3_CH1
static constexpr uint8_t ESC2 = PB3;    // TIM2_CH2
static constexpr uint8_t ADC_PIN = PA0;  // ADC input

static constexpr uint16_t MIN_US    = 900;  // 1 ms
static constexpr uint16_t MAX_US    = 1600;  // 1.8 ms
static constexpr uint16_t PERIOD_US = 20000; // 20 ms → 50 Hz
static constexpr uint8_t  RES_BITS  = 12;    // 12‐bit PWM resolution

// Konfiguracja dla napięcia odniesienia ADC (np. 3.3V)
static constexpr float ADC_REF_VOLTAGE = 3.3f;
static constexpr uint16_t ADC_MAX = (1 << 12) - 1;  // 4095

// Ostatni czas wysłania przez Serial1
unsigned long lastSendTime = 0;
const unsigned long sendInterval = 500; // ms

// Funkcja przeliczająca µs na duty cycle dla analogWrite
static uint16_t toDuty(uint16_t us) {
  constexpr uint16_t minDuty = uint16_t((float(MIN_US) / PERIOD_US) * ((1u << RES_BITS) - 1));
  constexpr uint16_t maxDuty = uint16_t((float(MAX_US) / PERIOD_US) * ((1u << RES_BITS) - 1));

  float scaled = float(us - MIN_US) / float(MAX_US - MIN_US);
  return minDuty + uint16_t(scaled * (maxDuty - minDuty));
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {}

  SerialPom.begin(9600);

  delay(500);

  analogWriteFrequency(50); // 50 Hz
  analogWriteResolution(RES_BITS);

  pinMode(ESC1, OUTPUT);
  pinMode(ESC2, OUTPUT);

  pinMode(ADC_PIN, INPUT_ANALOG); // ustaw pin PA0 jako wejście analogowe

  // ARMING ESC
  uint16_t d = toDuty(MIN_US);
  analogWrite(ESC1, d);
  analogWrite(ESC2, d);
  delay(2000);

  Serial.println("Podaj wartosc PWM (0–100%):");
}

void loop() {
  if (SerialPom.available()) {
    String input = SerialPom.readStringUntil('\n');
    input.trim();

    int percent = input.toInt();
    Serial.print(input);
    Serial.print(percent);
  }
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    int percent = input.toInt();
    Serial.print(input);
    Serial.print(percent);

    if (percent >= 0 && percent <= 100) {
      uint16_t us = MIN_US + (MAX_US - MIN_US) * (percent / 100.0);
      uint16_t duty = toDuty(us);

      analogWrite(ESC1, duty);
      analogWrite(ESC2, duty);

      Serial.print("Ustawiono PWM na ");
      Serial.print(percent);
      Serial.println("%");
    } else {
      Serial.println("Podaj liczbe z zakresu 0–100!");
    }

    Serial.println("Podaj wartosc PWM (0–100%):");
  }

  // Odczyt ADC i transmicja co 0.5s
  if (millis() - lastSendTime >= sendInterval) {
    uint16_t adcVal = analogRead(ADC_PIN);
    float voltage = (adcVal / float(ADC_MAX)) * ADC_REF_VOLTAGE;
    // String napis = String(voltage);

    SerialPom.println(voltage,3); // 3 miejsca po przecinku

    Serial.print("Napiece ADC (PA0): ");
    Serial.print(voltage, 3); // 3 miejsca po przecinku
    Serial.println(" V");

    lastSendTime = millis();
  }
}
