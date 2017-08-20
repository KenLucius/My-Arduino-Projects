#include "pitches.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
const byte SP_PIN = 11;
const byte LEDG = 2;
const byte LEDR = 3;

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);


void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  pinMode(SP_PIN, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(LEDR, OUTPUT);
  
  for(int i = 0; i < 3; i++)
  {
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }
  lcd.backlight();
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDR, LOW);
}

float value;
float ans;
void loop() {
  // put your main code here, to run repeatedly:
  value = analogRead(A0);
  ans = value * 0.004883;
  lcd.clear();
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDR, LOW);
  
  if(ans < 3.5)
  {
    digitalWrite(LEDG, HIGH);
    lcd.setCursor(0,0);
    lcd.print("Voltage = ");
    lcd.setCursor(0,1);
    lcd.print(ans, 2);
    lcd.setCursor(6,1);
    lcd.print("volts"); 
  }
  else
  {
    while(ans > 3.5)
    {
      digitalWrite(LEDR, HIGH);
      lcd.backlight();
      lcd.setCursor(3,0);
      tone(SP_PIN, NOTE_C5, 175);
      lcd.print("Warning...");
      delay(300);
      lcd.clear();
      delay(100);
      value = analogRead(A0);
      ans = value * 0.004883;
    }
    digitalWrite(LEDR, LOW);
  }
  delay(1000);
}
