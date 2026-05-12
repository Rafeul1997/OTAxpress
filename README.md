# OTAxpress 🚀

Fast, minimal OTA updates for ESP32.

![ESP32](https://img.shields.io/badge/ESP32-Compatible-blue)
![License](https://img.shields.io/badge/License-MIT-green)
![OTA](https://img.shields.io/badge/OTA-enabled-red)
![WiFi](https://img.shields.io/badge/WiFi-required-blueviolet)

## Features
- One-line OTA setup
- Auto hostname
- WiFi auto reconnect
- LED status indicator

## Example

```cpp
#include <OTAxpress.h>

OTAxpress ota("YOUR_SSID", "YOUR_PASSWORD");

void setup() {
  ota.setStatusLED(2);   // Built-in LED (optional)
  ota.begin();

  // Your setup code here
}

void loop() {
  ota.handle();

  // Your application code here
}
void loop() {
  ota.handle();
}
