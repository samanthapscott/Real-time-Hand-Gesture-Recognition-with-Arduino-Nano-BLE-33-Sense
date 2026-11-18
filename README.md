# Real-Time Hand Gesture Recognition and Wi-Fi Dashboard

**FIU EEL4746 — Microcomputers I | Arduino Nano 33 BLE Sense Rev2 | Edge Impulse | ESP8266**

## Overview
A four-person course project using the **Arduino Nano 33 BLE Sense Rev2** to sample motion sensors and run a gesture-classification model trained in **Edge Impulse Studio**. The Arduino sends prediction labels and scores over **UART** to a **NodeMCU ESP8266**, which serves a local web dashboard displaying the detected gesture and class scores.

The four classes are **Circle**, **Idle**, **Right-Left**, and **Up-Down**. This is an embedded TinyML + IoT implementation, not a webcam-based hand tracker.

## Architecture
```text
Arduino Nano 33 BLE Sense Rev2
  IMU (BMI270/BMM150) -> Edge Impulse inference
           |
           | UART / Serial1 at 9600 baud
           v
NodeMCU ESP8266 -> local Wi-Fi -> HTTP server (port 80)
                                     |-- /      HTML/JavaScript dashboard
                                     +-- /data  comma-separated prediction scores
```

## Repository contents
- [Final technical report](./EEL4746-FinalProjectReport.pdf) — original project report, design, troubleshooting, and results
- [ESP8266 firmware](./firmware/esp8266/ESP8266_FinalWifi.ino) — local Wi-Fi server and live browser dashboard
- [Arduino inference firmware](./firmware/arduino/ML_FinalProject_Arduino_V2.ino) — Edge Impulse sensor fusion and UART output (formatting normalized from the supplied sketch)
- **Edge Impulse library** — generated `final_project_inferencing` library is **not redistributed here** pending confirmation of its license terms

## Reproducing the project
1. Use an **Arduino Nano 33 BLE Sense Rev2** and **NodeMCU ESP8266**.
2. In Edge Impulse Studio, train or open the original gesture-classification impulse and export its **Arduino library** as `final_project_inferencing.zip`. Install it via Arduino IDE **Sketch → Include Library → Add .ZIP Library**. The original Arduino sketch includes `<final_project_inferencing.h>`.
3. Install the Arduino board support and required libraries, including `Arduino_BMI270_BMM150` and the sensor libraries referenced by the original sketch.
4. Configure a Wi-Fi SSID/password in the ESP8266 firmware **locally**; never commit actual credentials.
5. Connect the Arduino UART TX and ESP8266 RX with compatible logic levels and common ground, verify pin mapping, and upload the respective sketches.
6. Connect a browser on the same local network to the IP printed by the ESP8266. The page polls `/data` for current scores.

**Important:** The firmware and generated Edge Impulse library were supplied from the original project archive. A complete clean-room build and hardware retest have **not** been performed for this repository update. The Arduino sketch is included; the exported Edge Impulse library is not redistributed in this repository.

## Engineering lessons and limitations
- The university WPA2-Enterprise network was incompatible with the ESP8266's basic WPA2-PSK setup; the team tested with a laptop hotspot.
- The model initially struggled to generalize to different movement speeds and amplitudes. Additional gesture samples and filtering improved recognition, although **Circle** and **Up-Down** could still overlap.
- The web dashboard was **locally hosted** on the ESP8266; a remotely hosted/cloud dashboard was a proposed future improvement.
- The supplied ESP8266 sketch uses a simple positional serial protocol. This is a course prototype, not a hardened network service.

## Team and attribution
**Samantha Scott, Andrew Mendez, Sharnece Young, and Ryan Berish** — FIU EEL4746 project team. See the original report for documentation and project context.

## License and safety
The generated Edge Impulse inference ZIP is intentionally excluded pending confirmation of applicable redistribution terms. Wi-Fi credentials from the archived ESP8266 sketch have been replaced with placeholders. Do not publish personal passwords, private datasets, or licensed dependencies without permission.
