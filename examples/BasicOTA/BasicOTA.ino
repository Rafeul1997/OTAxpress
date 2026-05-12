#include <OTAxpress.h>

OTAxpress ota("YOUR_SSID", "YOUR_PASSWORD");

void setup() {
  ota.setStatusLED(2);   // Optional LED
  ota.begin();

  // Your setup code here
}

void loop() {
  ota.handle();

  // Your application code here
}
