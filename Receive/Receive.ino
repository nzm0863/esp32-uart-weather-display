#include <Adafruit_NeoPixel.h>
#define RXD2 16
#define TXD2 17

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

  while (Serial2.available()) {
    String msg = Serial2.readStringUntil('\n');
    msg.trim();
    Serial.print("受信:");
    Serial.println("[" + msg + "]");
    if (msg == "ON") {
      strip.setPixelColor(0, 255, 255, 255);
    } else {
      strip.clear();
    }
  }
  strip.show();
  delay(1000);
}
