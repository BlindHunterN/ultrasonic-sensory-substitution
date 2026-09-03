/**
 * @file main.cpp
 * @brief Ultrasonic Sensory Substitution Device Firmware
 * @author Nikolai Stoyanov
 * 
 * Embedded system that measures distance using an HC-SR04 ultrasonic sensor
 * and maps spatial proximity to dynamic audio/haptic feedback.
 */

#include <Arduino.h>

// --- Pin Definitions ---
constexpr uint8_t TRIG_PIN = 9;
constexpr uint8_t ECHO_PIN = 10;
constexpr uint8_t BUZZER_PIN = 11;

// --- Distance & Threshold Configurations (in centimeters) ---
constexpr float MAX_DISTANCE_CM = 200.0f;  // Maximum sensing distance
constexpr float MIN_DISTANCE_CM = 5.0f;    // Minimum critical distance
constexpr float SOUND_SPEED_CM_US = 0.0343f; // Speed of sound (~343 m/s)

// --- Non-blocking Timing Variables ---
unsigned long previousMillis = 0;
bool buzzerState = false;

/**
 * @brief Reads the distance from HC-SR04 sensor in centimeters.
 * @return Distance in cm, or MAX_DISTANCE_CM if out of range/timeout.
 */
float readDistanceCM() {
  // Clear trigger pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Send a 10us HIGH pulse to trigger the sensor
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read Echo pulse duration (timeout at 30ms ~ 5m)
  unsigned long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0) {
    return MAX_DISTANCE_CM; // No barrier detected or out of range
  }

  // Distance formula: (Time * Speed of Sound) / 2
  float distance = (duration * SOUND_SPEED_CM_US) / 2.0f;
  return constrain(distance, MIN_DISTANCE_CM, MAX_DISTANCE_CM);
}

void setup() {
  // Initialize Pin Modes
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Initialize Serial for telemetry/debugging
  Serial.begin(115200);
  Serial.println(F("--- Ultrasonic Sensory Substitution System Initialized ---"));
}

void loop() {
  float distance = readDistanceCM();

  // Print telemetry data to Serial Monitor
  Serial.print(F("Distance: "));
  Serial.print(distance, 1);
  Serial.println(F(" cm"));

  // If object is beyond maximum tracking threshold, turn off feedback
  if (distance >= MAX_DISTANCE_CM) {
    noTone(BUZZER_PIN);
    return;
  }

  // Map distance to pulse interval (closer object = faster beep/vibration)
  // 5cm -> 50ms interval (rapid warning)
  // 200cm -> 800ms interval (slow ping)
  unsigned long pulseInterval = map((long)distance, (long)MIN_DISTANCE_CM, (long)MAX_DISTANCE_CM, 50, 800);

  // Non-blocking timer for buzzer pulse generation
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= pulseInterval) {
    previousMillis = currentMillis;
    buzzerState = !buzzerState;

    if (buzzerState) {
      tone(BUZZER_PIN, 2000); // 2kHz warning tone
    } else {
      noTone(BUZZER_PIN);
    }
  }
}
