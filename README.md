# Real-Time Hand Gesture Recognition with Arduino Nano 33 BLE Sense

**Embedded Systems | Machine Learning | Signal Processing**

---

## Overview

This project implements a real-time hand gesture recognition system using the Arduino Nano 33 BLE Sense microcontroller. A TinyML model trained on accelerometer data classifies hand gestures on-device with low latency, demonstrating the practical deployment of machine learning at the edge without reliance on cloud infrastructure.

---

## Key Features

- On-device inference using TensorFlow Lite for Microcontrollers
- Real-time gesture classification via the onboard IMU (LSM9DS1)
- Trained and deployed a custom neural network model on a 256 KB flash microcontroller
- Serial output for gesture prediction display and debugging
- Designed for low power consumption and portable deployment

---

## Technical Stack

| Layer | Technology |
|---|---|
| Microcontroller | Arduino Nano 33 BLE Sense |
| Sensor | LSM9DS1 IMU (Accelerometer / Gyroscope) |
| ML Framework | TensorFlow Lite for Microcontrollers |
| Model Training | Python, TensorFlow / Keras |
| Firmware Language | C++ (Arduino) |
| Data Collection | Serial communication via Arduino IDE |

---

## System Architecture

```
IMU Sensor (Accelerometer Data)
        |
        v
  Data Preprocessing
  (Normalization, Windowing)
        |
        v
  TFLite Model Inference
  (Neural Network, on-device)
        |
        v
  Gesture Classification Output
  (Serial Monitor / Output Signal)
```

---

## Machine Learning Pipeline

1. **Data Collection** — Recorded raw accelerometer samples for each target gesture using the Arduino's serial interface.
2. **Preprocessing** — Normalized and windowed samples into fixed-length feature vectors.
3. **Model Design** — Built a fully connected neural network using Keras with ReLU activations and softmax output.
4. **Training** — Trained on labeled gesture data with validation split; exported to `.tflite` format.
5. **Quantization** — Applied post-training quantization to reduce model size for deployment to constrained hardware.
6. **Deployment** — Converted model to a C byte array and integrated into Arduino firmware using the TFLite Micro API.

---

## Hardware Requirements

- Arduino Nano 33 BLE Sense
- USB Micro-B cable
- Arduino IDE or PlatformIO

---

## Project Report

A full technical report documenting the system design, methodology, experimental results, and analysis is included in this repository.

[View Full Project Report (PDF)](./EEL4746-FinalProjectReport.pdf)

---

## Skills Demonstrated

- Embedded C++ firmware development for resource-constrained microcontrollers
- End-to-end machine learning pipeline: data collection through on-device deployment
- TensorFlow Lite model optimization and quantization
- IMU sensor integration and real-time signal processing
- Cross-disciplinary application of software and hardware engineering

---

## Course

**EEL 4746 — Microprocessors** | University of Florida

---

## Author

**Samantha Scott**
[GitHub Profile](https://github.com/samanthapscott)
