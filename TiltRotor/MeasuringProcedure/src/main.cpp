// Code where main measuring prodecure is conducted and automised
// It was done for STM32F401CCU6 BlackPill microcontroller board


#include <Arduino.h>
#include <ESP32Servo.h>

// Create a Servo object
Servo myServo;

// ADC parameters
const float ADC_MAX_VOLTAGE = 3.6; // Reference voltage for ADC
const int ADC_RESOLUTION = 4095;  // 12-bit resolution
const int SAMPLE_COUNT = 100;     // Number of samples to store

// Arrays to store measured values
float U1Array[SAMPLE_COUNT];
float U2Array[SAMPLE_COUNT];
float ResultArray[SAMPLE_COUNT];

// Index for storing data in arrays
int sampleIndex = 0;

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  Serial.println("Servo initialized");

  // Attach the servo to GPIO19
  myServo.attach(19);
  myServo.write(0); // Set servo to initial position (0 degrees)

  // Wait for serial monitor to start
  while (!Serial) {
    delay(10); // Wait for serial to initialize
  }
}

void loop() {
  // Repeat measurements 6 times
    delay(5000);  

  for (int j = 0; j < 6; j++) {
    Serial.println("Measurement cycle " + String(j + 1));
    delay(500);
    sampleIndex = 0;
    myServo.write(0);  // Start at 0 degrees

    // Move servo to 180 degrees and measure
    for (int pos = 0; pos <= 180; pos++) {
      myServo.write(pos);  // Move servo incrementally
      delay(10);           // Adjust for smooth movement

      if (sampleIndex < SAMPLE_COUNT) {
        // Measure ADC values
        int rawU1 = analogRead(36); // VP pin (ADC1_CH0 on GPIO36)
        int rawU2 = analogRead(39); // VN pin (ADC1_CH3 on GPIO39)

        // Convert raw ADC values to voltage
        // U1Array[sampleIndex] = (rawU1 / (float)ADC_RESOLUTION) * ADC_MAX_VOLTAGE;
        // U2Array[sampleIndex] = (rawU2 / (float)ADC_RESOLUTION) * ADC_MAX_VOLTAGE;

        // Calculate result (voltage difference)
        ResultArray[sampleIndex] = U1Array[sampleIndex] - U2Array[sampleIndex];

        // Print data to serial port
        // Serial.print("Sample " + String(sampleIndex + 1) + ": ");
        // Serial.print("U1 = " + String(U1Array[sampleIndex], 4) + " V, ");
        // Serial.print("U2 = " + String(U2Array[sampleIndex], 4) + " V, ");
        // Serial.println("Result = " + String(ResultArray[sampleIndex], 4) + " V");

        sampleIndex++; // Increment sample index
      }
    }

    delay(2000);  // Wait before the next movement
  }

  // Halt further actions
  Serial.println("Measurement complete. Halting further actions.");
  while (true) {
    // Do nothing, loop forever
  }

  
}
