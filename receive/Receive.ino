#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include "../wifi_config.h"

#define RXD2 16
#define TXD2 17

#define LED_PIN 5
#define LED_COUNT 8

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);


  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("WiFi connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  Serial.print("IP:");
  Serial.println(WiFi.localIP());

  Serial.print("RSSI:");
  Serial.println(WiFi.RSSI());

  strip.begin();
  strip.setBrightness(10);
  strip.show();
}

void loop() {
  if (Serial2.available()) {
    Serial.print("ok");
  } else {
    Serial.print("ng");
  }

  String msg = "";
  while (Serial2.available()) {
    msg = Serial2.readStringUntil('\n');
  }
  msg.trim();
  int LEDCount = msg.toInt();
  Serial.print("受信:");
  Serial.println(LEDCount);
  strip.clear();
  for (int i = 0; i < LEDCount; i++) {
    strip.setPixelColor(i, 255, 0, 0);
  }
  WiFiClientSecure client;
  client.setInsecure();

  HTTPClient http;
  http.begin(client, String(SUPABASE_URL) + "sensor_value");
  http.addHeader("apikey", SUPABASE_KEY);
  http.addHeader("Authorization", "Bearer " + String(SUPABASE_KEY));
  http.addHeader("Content-Type", "application/json");
  String json =
    "{\"value\":" + String(LEDCount) + "}";

  int httpCode = http.POST(json);

  Serial.print("HTTP:");
  Serial.println(httpCode);
  // Serial.println(String(SUPABASE_URL) + "sensor_value");

  String response = http.getString();
  Serial.println(response);

  http.end();

  strip.show();

  delay(100);
}
