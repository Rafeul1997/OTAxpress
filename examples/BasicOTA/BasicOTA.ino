#include <OTAxpress.h>

OTAxpress ota("YOUR_SSID", "YOUR_PASSWORD");

void setup() {
  ota.setHostname("MyESP32");     // REQUIRED
  ota.setOTAPassword("1234");     // REQUIRED
  ota.setStatusLED(2);            // Optional

  ota.begin();


   // Your setup code here
}

void loop() {
  ota.handle();

   // Your application code here
}
