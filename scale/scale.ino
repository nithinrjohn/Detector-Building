/*
  Linn-Mar Science Olympiad Detector Building 2022 - 2023
*/

//these two header files are made to clean up code
//display.h handles the LCD and LEDs
//sampler.h handles the math for averaging readings
#include "display.h"
#include "sampler.h"

// initialize Input Pin
int IN_PIN = 0;

const float a = 1.57152;
const float b = -14.2523;
const float c = 39.8921;
const float d = -154.994; 
const float e = 225.605;
const float f = 0.482326;

// the setup routine runs once when you press reset:
void setup() {
  pinMode(IN_PIN, INPUT);
  Serial.begin(9600);
  Serial.println("Scale initialized.\n");

  //initialize lcd and leds
  initLED();
  initLCD();
}

// the loop routine runs over and over again forever:
void loop() {
  // analog to digital conversion
  float rawValue = analogRead(IN_PIN); //10 ADC
  float vOut = rawValue * (5.0 / 1023.0);

  //if mass is place...
  if(vOut > 0.2 && n < NUM_SAMPLES) {
    //convert volt to mass using the equation
    float mass = a * pow(vOut, 6) + b * pow(vOut, 5) + c * pow(vOut, 4) + d * pow(vOut, 2) + e * vOut + f;

    //ignores the first few readings to compensate for extra mass of placer's hand
    ignoreSamples(mass, vOut);

    Serial.print("vOut: " + String(vOut) + ", Mass: " + String(mass));

    n++;

    //outputs the avg mass and vOut and displays it
    outputAvgMass();

    Serial.println();    
  }
  //if mass is removed...
  else if(vOut <= 0.2 && n == NUM_SAMPLES) {
    clearSamples();
    clear();
  }
  //debug if output does not clear properly to tell user to reset arduino
  else if(vOut != 0)
  {
    Serial.println("v: " + String(vOut));
  }

  delay(500);
}
