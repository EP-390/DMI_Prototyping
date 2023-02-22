const int LED_pin = 9;
int data = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED_pin, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    data = Serial.read();
    analogWrite(LED_pin, data);
  }
}
