void setup(void) { pinMode(13, OUTPUT); }

void loop(void) {
  Serial.begin(9600);

  Serial.print("Hello World!\n");

  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
}
