const int analogPin = A0;
int sensorValue = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(analogPin);
  Serial.println(sensorValue);
  delay(100);
}
