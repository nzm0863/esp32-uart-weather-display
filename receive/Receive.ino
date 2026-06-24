#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <HTTPClient.h>
#define RXD2 16
#define TXD2 17

#define WIFI_SSID ""
#define WIFI_PASSWORD ""

#define LED_PIN 5
#define LED_COUNT 8
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);


  strip.begin();
  strip.setBrightness(5);
  strip.show();
}

void loop() {
  if(Serial2.available()){
    Serial.print("ok");
  }else{
    Serial.print("ng");
  }


  while (Serial2.available()) {
    String msg = Serial2.readStringUntil('\n');
    msg.trim();
    int LEDCount=msg.toInt();
    Serial.print("受信:");
    Serial.println(LEDCount);
    strip.clear();
    for(int i=0;i<LEDCount;i++){
      strip.setPixelColor(i, 255, 255, 255);
    }
    // if (msg == "ON") {
    //   strip.setPixelColor(0, 255, 255, 255);
    // } else {
    //   strip.clear();
    // }
  }
  strip.show();
  delay(1000);
}
