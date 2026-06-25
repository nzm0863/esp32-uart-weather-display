#define RXD2 16
#define TXD2 17
#define SENSOR_PIN 32

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
}

bool lastState = false;
int LEDCount = 0;
void loop() {
  int sensorValue = analogRead(SENSOR_PIN);
  // if (sensorValue < 3000) {
  //   LEDCount = 1;
  // } else if (sensorValue < 3200) {
  //   LEDCount = 2;
  // } else if (sensorValue < 3400) {
  //   LEDCount = 3;
  // } else if (sensorValue < 3600) {
  //   LEDCount = 4;
  // } else if (sensorValue < 3800) {
  //   LEDCount = 5;
  // } else if (sensorValue < 4000) {
  //   LEDCount = 6;
  // } else if (sensorValue < 4200) {
  //   LEDCount = 7;
  // } else {
  //   LEDCount = 8;
  // }

  LEDCount = constrain(
    map(sensorValue, 2000, 4000, 1, 8),
    1,
    8);

  Serial2.println(LEDCount);
  Serial.println(LEDCount);
  Serial.println(sensorValue);

  delay(500);
}
