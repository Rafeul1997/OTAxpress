# OTAxpress 🚀

Fast, minimal, plug-and-play OTA updates for ESP32.

![ESP32](https://img.shields.io/badge/ESP32-Compatible-blue)
![License](https://img.shields.io/badge/License-MIT-green)
![OTA](https://img.shields.io/badge/OTA-enabled-red)
![WiFi](https://img.shields.io/badge/WiFi-required-blueviolet)

## ✨ Features
- One-line OTA setup
- Automatic hostname generation
- Optional password protection
- LED status indication
- Clean and simple API

## 📦 Installation
Download or clone this repository into your Arduino `libraries` folder.

## 🚀 Example

```cpp
#include <OTAxpress.h>

OTAxpress ota("YOUR_SSID", "YOUR_PASSWORD");

void setup() {
  ota.setStatusLED(2);   // Optional LED
  ota.begin();
}

void loop() {
  ota.handle();

  // Your application code here
}
