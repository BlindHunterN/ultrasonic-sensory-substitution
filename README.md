# Ultrasonic Sensory Substitution Device 🦇

An Arduino-based wearable embedded system designed to assist visually impaired individuals by mapping spatial proximity to real-time haptic/acoustic feedback.

## 📌 Project Overview
This project processes distance measurements from an ultrasonic sensor (HC-SR04) and converts distance metrics into dynamic output responses. By modulating pulse frequencies, the device provides intuitive proximity warnings to the user in real time.

## 🛠 Hardware Components
* **Microcontroller:** Arduino Uno / Nano
* **Distance Sensor:** HC-SR04 Ultrasonic Sensor
* **Feedback Mechanism:** Piezo Buzzer / Vibration Motor (Haptic feedback)
* **Prototyping:** Breadboard, jumpers, 220Ω resistor

## 🔌 Circuit & Pinout Configuration
| Component | Arduino Pin | Description |
| :--- | :--- | :--- |
| **HC-SR04 VCC** | 5V | Power supply |
| **HC-SR04 GND** | GND | Ground |
| **HC-SR04 Trig** | Pin 9 | Pulse trigger output |
| **HC-SR04 Echo** | Pin 10 | Distance echo input |
| **Buzzer (+)** | Pin 11 | PWM / Frequency Output |

## 🚀 Features
* **Real-time Obstacle Detection:** Measures distance between 2cm and 400cm with high accuracy.
* **Non-blocking Code:** Designed for continuous sensor sampling and fast feedback loop response.
* **Adaptive Warning System:** Frequency of audio/haptic pulses increases as obstacles get closer.

## 💻 Firmware Code Structure
The standard implementation uses `pulseIn()` or interrupt-driven timing to calculate distance based on the speed of sound ($343 \text{ m/s}$):

$$\text{Distance (cm)} = \frac{\text{Duration } (\mu\text{s}) \times 0.0343}{2}$$

## 👤 Author
**Николай Стоянов**
* LinkedIn: [nikolay-stoyanov-ce](https://www.linkedin.com/in/nikolay-stoyanov-ce)
* GitHub: [BlindHunterN](https://github.com/BlindHunterN)
