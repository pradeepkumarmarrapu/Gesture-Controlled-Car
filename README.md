# Gesture-Controlled Car 🚗🤖

A **gesture-controlled smart car** project using two **ESP32 boards** and **MPU6050 sensors** that move the car based on hand tilt gestures.  
It communicates wirelessly using **ESP-NOW protocol**, allowing seamless control without Wi-Fi networks.

---

## 🧠 Concept

This project detects hand gestures using the MPU6050 sensor and sends corresponding motion commands to another ESP32 controlling the motors.  
The system recognizes gestures like **forward**, **backward**, **left**, **right**, and **stop**.

---

## ⚙️ Components

### 🔩 Hardware
- 2 × ESP32 boards (Transmitter + Receiver)
- 2 × MPU6050 sensors (Accelerometer + Gyroscope)
- 1 × L298N Motor Driver
- 1 × 4WD Chassis with DC Motors
- 4 × Lithium-ion Batteries (Rechargeable)
- Jumper Wires

### 💻 Software
- Arduino IDE
- Libraries:
  - `WiFi.h`
  - `esp_now.h`
  - `Wire.h`
  - `Adafruit_MPU6050.h`
  - `Adafruit_Sensor.h`

---

## 📡 Working Principle

1. The transmitter ESP32 reads accelerometer data from the MPU6050.
2. It interprets tilt angles as motion commands:
   - **Tilt Forward → Car moves forward**
   - **Tilt Backward → Car moves backward**
   - **Tilt Left → Car turns left**
   - **Tilt Right → Car turns right**
   - **Stable → Car stops**
3. Commands are sent to the receiver ESP32 via **ESP-NOW**.
4. The receiver drives the motors using **L298N motor driver**.

---

## 📁 File Structure

```
Gesture-Controlled-Car/
│
├── README.md
├── LICENSE
├── transmitter/
│   └── transmitter.ino
├── receiver/
│   └── receiver.ino
└── documentation/
    └── Gesture-Controlled-Car-A-Robotics-Project.pptx
```

---

## 🔌 Circuit Overview

### Transmitter:
- MPU6050 → ESP32 (I2C)
  - VCC → 3.3V
  - GND → GND
  - SDA → D21
  - SCL → D22

### Receiver:
- ESP32 → L298N Motor Driver
  - ENA → GPIO5  
  - IN1 → GPIO12  
  - IN2 → GPIO14  
  - IN3 → GPIO13  
  - IN4 → GPIO15  
  - ENB → GPIO18  

---

## 🚀 Future Enhancements
- Add obstacle detection (ultrasonic sensor)
- Add Bluetooth or Wi-Fi fallback control
- Use Kalman filter for more stable gesture readings
- Add mobile app interface for mode switching

---

## 📸 Documentation
All design details, code explanation, and working are included in  
[`documentation/Gesture-Controlled-Car-A-Robotics-Project.pptx`](documentation/Gesture-Controlled-Car-A-Robotics-Project.pptx)

---

## 🏷️ License
This project is licensed under the [MIT License](LICENSE).

---

## 👨‍💻 Author
**Pradeep Kumar Marrapu**  
B.Tech ECE | Robotics & Embedded Systems Enthusiast  
