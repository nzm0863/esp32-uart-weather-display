#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "../wifi_config.h"

#define RXD2 16
#define TXD2 17

void getWeather() {
  HTTPClient http;

  // 浜松(西部)の天気
  http.begin("https://weather.tsukumijima.net/api/forecast?city=220040");

  int httpCode = http.GET();


  if (httpCode > 0) {
    String payload = http.getString();

    JsonDocument doc;

    deserializeJson(doc, payload);

    for (int i = 0; i < 3; i++) {
      const char* date = doc["forecasts"][i]["date"];
      String telop = weatherToEnglish(doc["forecasts"][i]["telop"]);
      const char* maxTemp = doc["forecasts"][0]["temperature"]["max"]["celsius"];

      Serial.print(date);
      Serial.print(" : ");
      Serial.print(telop);
      Serial.println(maxTemp);
      Serial2.print(date);
      Serial2.print(" : ");
      Serial2.print(telop);
      Serial2.print(",");
      Serial2.println(maxTemp);
      delay(50);
    }
  } else {
    Serial.println("通信失敗");
  }

  http.end();
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi接続");
  getWeather();
}

String weatherToEnglish(const char* weather) {
  String w = weather;
  // if (strcmp(weather, "晴れ") == 0) return "Sunny";
  // if (strcmp(weather, "曇り") == 0) return "Cloudy";
  // if (strcmp(weather, "雨") == 0) return "Rain";
  // if (strcmp(weather, "雪") == 0) return "Snow";


  if (w.indexOf("雪") >= 0) return "Snow";
  if (w.indexOf("雨") >= 0) {
    if (w.indexOf("雷") >= 0) return "Thunder";
    return "Rain";
  };
  if (w.indexOf("曇") >= 0) return "Cloudy";
  if (w.indexOf("晴") >= 0) return "Sunny";

  return "Unknown";
}

unsigned long lastUpdate = 0;
const unsigned long interval = 30UL * 60 * 1000;  // 30分

void loop() {
  if (millis() - lastUpdate >= interval) {
    getWeather();
    lastUpdate = millis();
  }
}
