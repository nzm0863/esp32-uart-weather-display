#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include "../wifi_config.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define RXD2 16
#define TXD2 17

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

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

  // SDA=21 SCL=22（ESP32の標準）
  Wire.begin(21, 22);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED initialization failed");
    while (true)
      ;
  }

  display.clearDisplay();
  display.setTextSize(2);  // 文字サイズ
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.display();
}

String forecast[3];
int receiveIndex = 0;
int showIndex = 0;

void loop() {
  if (Serial2.available()) {
    forecast[receiveIndex] = Serial2.readStringUntil('\n');
    forecast[receiveIndex].trim();
    Serial.print("受信:");
    Serial.println(forecast[showIndex]);
    receiveIndex++;
    if (receiveIndex >= 3) {
      receiveIndex = 0;
    }
  }
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.println(forecast[showIndex]);
  display.display();
  showIndex++;
  if (showIndex >= 3) {
    showIndex = 0;
  }
  delay(1000);
}
