#ifndef OTAXPRESS_H
#define OTAXPRESS_H

#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoOTA.h>

class OTAxpress {
  public:
    OTAxpress(const char* ssid, const char* password);

    void setHostname(const char* hostname);
    void setOTAPassword(const char* otaPassword);
    void setStatusLED(int pin);

    void begin();
    void handle();

  private:
    const char* _ssid;
    const char* _password;
    const char* _hostname = "OTAxpress-ESP32";
    const char* _otaPassword = NULL;
    int _ledPin = -1;

    void connectWiFi();
};

#endif
