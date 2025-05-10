#pragma once

#include <Arduino.h>
#include "STSCTRL.h"    // using st.WritePosEx() function to write data via UART bus
#include "CONNECT.h"   

// Motion parameters
constexpr uint8_t  SERVO_ID    = 1;
constexpr s16      POS_A       = 20;
constexpr s16      POS_B       = 100;
int16_t SERVO_SPEED = 1000;
constexpr uint8_t  SERVO_ACC   = 10;
constexpr unsigned long INTERVAL_MS = 100;

// Send sine signal as reference
constexpr float FREQ_HZ     = 1.0f;    // 1 Hz
constexpr s16 CENTER_POS    = 15000;     // środek zakresu (tu (0+200)/2)
constexpr s16 AMPLITUDE     = 2000;     // amplituda (tu (200−0)/2)

uint16_t PERIOD_COUNTER = 2000;
bool toggle_flag = 0;

void periodicServoControl() {
    // static unsigned long lastTime = 0;
    // static unsigned long lastTimePeriod = 0;
    // static bool toggle = false;
    // unsigned long now = millis();

      
    for (int i =1; i< 3; i++)
    {

        // st.WritePosEx(1, -1000, SERVO_SPEED, SERVO_ACC);
        st.WritePosEx(10, 1000, SERVO_SPEED, SERVO_ACC);
        delay(3000);
        // st.WritePosEx(1, -1000, SERVO_SPEED, SERVO_ACC);
        st.WritePosEx(10, 1000, SERVO_SPEED, SERVO_ACC);
        delay(3000);
    }
    //   st.WritePosEx(SERVO_ID, 15000, SERVO_SPEED, SERVO_ACC);
    //   delay(5000);
    //   st.WritePosEx(SERVO_ID, 10000, SERVO_SPEED, SERVO_ACC);
    //   delay(5000);
    //   st.WritePosEx(SERVO_ID, 5000, SERVO_SPEED, SERVO_ACC);
    //   delay(5000);
    //   st.WritePosEx(SERVO_ID, 0, SERVO_SPEED, SERVO_ACC);
    //   delay(2000);
    //   st.WritePosEx(SERVO_ID, -5000, SERVO_SPEED, SERVO_ACC);
    //   delay(2000);
    //   st.WritePosEx(SERVO_ID, -10000, SERVO_SPEED, SERVO_ACC);
    //   delay(2000);
    //   st.WritePosEx(SERVO_ID, -15000, SERVO_SPEED, SERVO_ACC);
    //   delay(2000);
    //   st.WritePosEx(SERVO_ID, -20000, SERVO_SPEED, SERVO_ACC);
    //   delay(2000);
  }

  void sineServoControl(unsigned long t) {
    // unsigned long nowMs = millis();
    // float t = nowMs / 1000.0f;                 // czas w sekundach
    float angle = TWO_PI * FREQ_HZ * t;        // kąt: 2πft
    float sinv = sin(angle);                   // -1…+1

    int target = CENTER_POS + int(AMPLITUDE * sinv);
    // upewnij się, że target ∈ [0…30000]
    target = constrain(target, 0, 30000);

    // Speed = 0 → max prędkość
    st.WritePosEx(SERVO_ID, target, 0, SERVO_ACC);
}

constexpr int OFFSET_A =  +1000;
constexpr int OFFSET_B =  -1000;

constexpr int speed =  400;

void gotoOffset_ST(byte servoID, int offset, uint16_t speed, uint8_t acc) {
  // Oblicz pozycję docelową:
  int target = ServoDigitalMiddle_ST + offset;
  // Ogranicz do dopuszczalnego zakresu:
  target = rangeCtrl(target, 0, ServoDigitalRange_ST - 1);
  // Wyślij komendę:
  st.WritePosEx(servoID, target, speed, acc);
}

void moveToA() {
  gotoOffset_ST(SERVO_ID, OFFSET_A, speed, 10);
}

void moveToB() {
  gotoOffset_ST(SERVO_ID, OFFSET_B, speed, 10);
}