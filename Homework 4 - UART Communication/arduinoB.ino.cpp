#include <Arduino.h>

#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  lcd.print("Temperature");
  Serial.begin(9600);
}

float information;
float celcius;
int kelvin;
int fahrenheit;

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,1);
  if (Serial.available()) {
    information = Serial.read();
    celcius = (information/1023) * 500;
    kelvin = celcius + 273.15;
    fahrenheit = celcius * 9/5 + 32;
    lcd.print(String(int(celcius)) + "*C " + String(kelvin) + "*K " + String(fahrenheit) + "*F");
  }
}

