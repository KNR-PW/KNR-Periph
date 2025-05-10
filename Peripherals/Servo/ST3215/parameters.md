# Physical parameters for controlling servomechanism propoerly

int16_t SERVO_SPEED = 1000;
constexpr uint8_t  SERVO_ACC   = 10;
constexpr unsigned long INTERVAL_MS = 100;

      st.WritePosEx(SERVO_ID, 1000, SERVO_SPEED, SERVO_ACC);
      delay(2000);
      st.WritePosEx(SERVO_ID, -1000, SERVO_SPEED, SERVO_ACC);


      # Sterowanie na obrót 90 stopni w tą i z powrotem - 1000 -> 90deg.