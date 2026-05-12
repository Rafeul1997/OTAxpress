#include "OTAxpress.h"

OTAxpress::OTAxpress(const char* ssid, const char* password) {
  _ssid = ssid;
  _password = password;
}

void OTAxpress::setHostname(const char* hostname) {
  _hostname = hostname;
}

void OTAxpress::setOTAPassword(const char* otaPassword) {
  _otaPassword = otaPassword;
}

void OTAxpress::setStatusLED(int pin) {
  _ledPin = pin;
  pinMode(_ledPin, OUTPUT);
}

void OTAxpress::begin() {
  Serial.begin(115200);

  WiFi.begin(_ssid, _password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Auto hostname if user didn't set one
  if (String(_hostname) == "OTAxpress-ESP32") {
    String mac = WiFi.macAddress();
    mac.replace(":", "");
    String autoName = "OTAxpress-" + mac.substring(6);
    ArduinoOTA.setHostname(autoName.c_str());
  } else {
    ArduinoOTA.setHostname(_hostname);
  }

  if (_otaPassword != NULL) {
    ArduinoOTA.setPassword(_otaPassword);
  }

  ArduinoOTA.onStart([this]() {
    Serial.println("OTA Start");
    if (_ledPin != -1) digitalWrite(_ledPin, HIGH);
  });

  ArduinoOTA.onEnd([this]() {
    Serial.println("\nOTA End");
    if (_ledPin != -1) digitalWrite(_ledPin, LOW);
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress * 100) / total);
  });

  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]\n", error);
  });

  ArduinoOTA.begin();
  Serial.println("OTAxpress Ready 🚀");
}

void OTAxpress::handle() {
  ArduinoOTA.handle();
}
