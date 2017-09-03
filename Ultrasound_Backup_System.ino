/*
**************************************************************************
  Purpose: This project simulates a backup system for an automobile.
  OUTPUTS: LCD display, Piezo Transducer
  Built: 20/08/2017
  By: Kenny Lu
**************************************************************************
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "pitches.h"

const byte LEDY = 2;
const byte LEDR = 3;
const byte trigpin = 9;     // For the ultrasound module
const byte echopin = 10;    // ultrasound module
const byte soundpin = 11;   // For piezo transducer

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Setting LCD I2C Address


/* Measures the distance */
unsigned long ping()
{
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);

  return pulseIn(echopin, HIGH);
}

/* Resets the two LEDs */
void reset()
{
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDY, LOW);
}

/* Lights up the two LEDs */
void lightup(int caseno)
{
  if(caseno == 4)
  {
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDY, LOW);
  }
  else
  {
    digitalWrite(LEDR, LOW);
    digitalWrite(LEDY, HIGH);
  }
  
}

/* Displays distance information on LCD */
void display(unsigned long distance)
{
  lcd.clear();
  lcd.print("Current Dist = ");
  lcd.setCursor(2,1);
  lcd.print(distance);
  lcd.print(" cm");  
}

/* Play the piezo transducer according to caseno */
void play(int caseno)
{
  switch(caseno)
  {
    case 0:
      tone(soundpin, NOTE_C5, 130);
      delay(330);
      break;
    case 1:
      tone(soundpin, NOTE_C5, 130);
      delay(230);
      break;
    case 2:
      tone(soundpin, NOTE_C5, 130);
      delay(130);
      break;
    case 3:
      tone(soundpin, NOTE_C5, 130);
      delay(30);
      break;
    case 4:
      tone(soundpin, NOTE_C5, 130);
      break;
  }
}


void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  pinMode(LEDY, OUTPUT);
  pinMode(LEDR, OUTPUT);
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  pinMode(soundpin, OUTPUT);
  /* LCD initialisation */
  for(byte i = 0; i < 3; i++)
  {
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }
  lcd.backlight();
  reset();
}

unsigned long distance = 0;
int caseno = 0;
byte count = 0;

void loop() {
  // put your main code here, to run repeatedly:
  
  distance = ping() / 58;
  if(distance >= 100)
  {
    reset();
    display(distance);
    delay(200);
    count = 0;
  }
  else if(distance >= 80 && distance < 100)
  {
    caseno = 0;
    lightup(caseno);
    display(distance);
    play(caseno);
    count = 0;
  }
  else if(distance >= 60 && distance < 80)
  {
    caseno = 1;
    lightup(caseno);
    display(distance);
    play(caseno);
    count = 0;
  }
  else if(distance >= 40 && distance < 60)
  {
    caseno = 2;
    lightup(caseno);
    display(distance);
    play(caseno);
    count = 0;
  }
  else if(distance >= 20 && distance < 40)
  {
    caseno = 3;
    lightup(caseno);
    display(distance);
    play(caseno);
    count = 0;
  }
  else
  {
    caseno = 4;
    lightup(caseno);
    if(count == 0)
    {
      lcd.clear();
      lcd.setCursor(5,0);
      lcd.print("STOP");
      count++;
    }
    play(caseno);
  }
  delay(127);
}
