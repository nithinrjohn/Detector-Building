/*
  Linn-Mar Science Olympiad Detector Building 2022 - 2023
*/

#include "display.h"
#include "sampler.h"

// initialize Input Pin
int IN_PIN = 0;

// const float a = 0.463805;
// const float b = 2.47632;
// const float c = 1.77708;
// const float d = 0.330908; 
// const float e = 91.6197;

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

  initLED();
  initLCD();
}

// the loop routine runs over and over again forever:
void loop() {
  // analog to digital conversion
  float rawValue = analogRead(IN_PIN); //10 ADC
  float vOut = rawValue * (5.0 / 1023.0);

  //Serial.println("r: " + String{rawValue});

  if(vOut > 0.2 && n < NUM_SAMPLES) {
    //volt to mass to equation
    //float mass = a * pow(b, (c * vOut + d)) + e;
    float mass = a * pow(vOut, 6) + b * pow(vOut, 5) + c * pow(vOut, 4) + d * pow(vOut, 2) + e * vOut + f;

    ignoreSamples(mass, vOut);

    Serial.print("vOut: " + String(vOut) + ", Mass: " + String(mass));

    n++;

    outputAvgMass();

    Serial.println();
  }
  else if(vOut <= 0.2) {
    clearSamples();
    clear();
  }
  else if(vOut != 0)
  {
    Serial.println("v: " + String(vOut));
  }

  delay(500);
}
