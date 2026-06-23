#define RXD2 16
#define TXD2 17
#define SENSOR_PIN 32

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
}

bool currentState = false;
bool lastState = false;

void loop() {

  int sensorValue = analogRead(SENSOR_PIN);
  currentState = sensorValue > 3500;
  if (currentState != lastState) {
    Serial2.println(currentState ? "ON" : "OFF");
    lastState = currentState;
  }
  delay(200);
}
