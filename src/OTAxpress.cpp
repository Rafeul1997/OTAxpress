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

void OTAxpress::connectWiFi() {
  WiFi.begin(_ssid, _password);

  Serial.print("Connecting to WiFi");
  int retry = 0;

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    retry++;

    if (retry > 40) {
      Serial.println("\nWiFi Failed! Restarting...");
      ESP.restart();
    }
  }

  Serial.println("\nConnected!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void OTAxpress::begin() {
  Serial.begin(115200);

  // 🔴 STRICT CHECK (IMPORTANT)
  if (_hostname == NULL || _otaPassword == NULL) {
    Serial.println("ERROR: Hostname and OTA Password must be set!");
    while (true); // Stop execution
  }

  connectWiFi();

  ArduinoOTA.setHostname(_hostname);
  ArduinoOTA.setPassword(_otaPassword);

  ArduinoOTA.onStart([this]() {
    Serial.println("\nOTA Start");
    if (_ledPin != -1) digitalWrite(_ledPin, HIGH);
  });

  ArduinoOTA.onEnd([this]() {
    Serial.println("\nOTA End");
    if (_ledPin != -1) digitalWrite(_ledPin, LOW);
  });

  ArduinoOTA.onProgress([this](unsigned int progress, unsigned int total) {
    int percent = (progress * 100) / total;
    Serial.printf("Progress: %d%%\r", percent);

    if (_ledPin != -1) {
      digitalWrite(_ledPin, !digitalRead(_ledPin));
    }
  });

  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("\nError[%u]\n", error);
  });

  ArduinoOTA.begin();

  Serial.println("OTAxpress Ready 🚀");
}

void OTAxpress::handle() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.reconnect();
  }

  ArduinoOTA.handle();
}
