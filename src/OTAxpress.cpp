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

    // Restart after long failure
    if (retry > 40) {
      Serial.println("\nWiFi Failed! Restarting...");
      ESP.restart();
    }
  }

  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void OTAxpress::begin() {
  Serial.begin(115200);

  connectWiFi();

  // Auto hostname
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

    // Blink LED during OTA
    if (_ledPin != -1) {
      digitalWrite(_ledPin, !digitalRead(_ledPin));
    }
  });

  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("\nError[%u]: ", error);
  });

  ArduinoOTA.begin();

  Serial.println("OTAxpress Ready 🚀");
}

void OTAxpress::handle() {
  // Auto reconnect WiFi if disconnected
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.reconnect();
  }

  ArduinoOTA.handle();
}
