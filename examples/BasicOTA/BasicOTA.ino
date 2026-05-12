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
