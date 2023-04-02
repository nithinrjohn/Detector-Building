/*
  Linn-Mar Science Olympiad Detector Building 2022 - 2023
*/

//libraries to run the LCD display board
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int LED_RED = 4;
int LED_GREEN = 3;
int LED_BLUE = 2;

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

// mass(g) thresholds TBD at competition
const float redzone[2] = { 0, 250 };
const float greenzone[2] = { 251, 500 };
const float bluezone[2] = { 501, 1000 };

//tests leds at init
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
  lcd.begin(20, 4);
  lcd.home();
  lcd.setCursor(6, 0);
  lcd.print("Linn-Mar");
  lcd.setCursor(3, 1);
  lcd.print("Sci Oly - C17");
}

void displayMass(float mass, float vOut) {
  lcd.home();
  lcd.setCursor(4, 2);
  lcd.print("vOut = ");
  lcd.print(String(vOut));
  lcd.setCursor(4, 3);
  lcd.print("Mass = ");
  lcd.print(String(mass));
}

// turns on LED based on threshold
void selectLED(float mass) {
  if (mass >= redzone[0] && mass <= redzone[1]) {
    digitalWrite(LED_RED, HIGH);
  } else if (mass >= greenzone[0] && mass <= greenzone[1]) {
    digitalWrite(LED_GREEN, HIGH);
  } else if (mass >= bluezone[0] && mass <= bluezone[1]) {
    digitalWrite(LED_BLUE, HIGH);
  }
}

void clear() {
  lcd.setCursor(4, 2);
  lcd.print("vOut = 0.0    ");
  lcd.setCursor(4, 3);
  lcd.print("Mass = 0.0    ");
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, LOW);
}