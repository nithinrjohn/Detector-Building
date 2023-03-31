/*
  Linn-Mar Science Olympiad Detector Building 2022 - 2023
*/

#include "display.h"
#include "sampler.h"

// initialize Input Pin
int IN_PIN = 0;

float mass = 0;

//coefficient = oldreg + newreg
const float a = (-26.104 + -21.6787) / 2;
const float b = (376.423 + 314.796) / 2;
const float c = (-1844.96 + -1555.59) / 2;
const float d = (3076.86 + 2617.45) / 2; 
const float e = 0;

//old calc output
// const float a = -45.33397015;
// const float b = 667.0383726;
// const float c = -3463.684349;
// const float d = 7012.514715; 
// const float e = -3520.181557;

//old
// const float a = -26.104;
// const float b = 376.423;
// const float c = -1844.96;
// const float d = 3076.86; 
// const float e = 0;

// //new
// const float a = -21.6787;
// const float b = 314.796;
// const float c = -1555.59;
// const float d = 2617.45; 
// const float e = 0;

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

  if(vOut != 5 && n < NUM_SAMPLES) {
    //volt to mass to equation
    mass = a * pow(vOut, 4) + b * pow(vOut, 3) + c * pow(vOut, 2) + d * vOut + e;

    ignoreSamples(mass, vOut)

    Serial.print("vOut: " + vOut + ", Mass: " + mass);

    n++;

    outputAvgMass();
    avg_vOut = outputAvgV();

    if(avg_vOut != 0) {
      mass = a * pow(avg_vOut, 4) + b * pow(avg_vOut, 3) + c * pow(avg_vOut, 2) + d * avg_vOut + e;
      Serial.println("Vmass: " + mass);
    }

    Serial.println();
  }
  else if(vOut == 5) {
    clearSamples();
    clear();
  }

  delay(500);
}
