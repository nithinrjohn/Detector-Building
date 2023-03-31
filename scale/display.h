/*
  Linn-Mar Science Olympiad Detector Building 2022 - 2023
*/

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

const int LED_RED = 4;
const int LED_GREEN = 3;
const int LED_BLUE = 2;

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
  
// // mass(g) thresholds TBD at competition
const float redzone[2] = {30, 350};
const float greenzone[2] = {351, 670};
const float bluezone[2] = {671, 1000};           

void initLED() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  digitalWrite(LED_RED, HIGH);
  delay(500);
  digitalWrite(LED_RED, LOW);

  digitalWrite(LED_GREEN, HIGH);
  delay(500);
  digitalWrite(LED_GREEN, LOW);
  
  digitalWrite(LED_BLUE, HIGH);
  delay(500);
  digitalWrite(LED_BLUE, LOW);

}

void initLCD() {
  lcd.begin (20,4);
  lcd.home ();
  lcd.setCursor(6, 0);
  lcd.print("Linn-Mar");
  lcd.setCursor(3, 1);
  lcd.print("Sci Oly - C17");
}

void displayMass(float mass) {
  lcd.home ();
  lcd.setCursor(3, 3);
  lcd.print("Mass = ");
  lcd.print(String(mass));
}

// turns on LED based on threshold
void selectLED(float mass) {
  if( mass >= redzone[0] && mass <= redzone[1] )
  {
      digitalWrite(LED_RED, HIGH);
  }
  else if( mass >= greenzone[0] && mass <= greenzone[1] )
  {
      digitalWrite(LED_GREEN, HIGH);
  }
  else if( mass >= bluezone[0] && mass <= bluezone[1] )
  {
      digitalWrite(LED_BLUE, HIGH);
  }
}

void clear() {
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BLUE, LOW);
    lcd.clear();
}