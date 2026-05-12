# OTAxpress 🚀

Fast, minimal, plug-and-play OTA updates for ESP32.

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
  ota.begin();
}

void loop() {
  ota.handle();
}
