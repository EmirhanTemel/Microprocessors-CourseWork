#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}
float information;
void loop() {
  // put your main code here, to run repeatedly:
  information = analogRead(1);
  Serial.write(int(information));
  delay(100);
}

