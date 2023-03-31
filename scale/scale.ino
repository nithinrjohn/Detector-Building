/*
  Linn-Mar Science Olympiad Detector Building 2022 - 2023
*/

#include "display.h"
#include "sampler.h"

// initialize Input Pin
int IN_PIN = 0;

float mass = 0;

//coefficient = oldreg + newreg
// const float a = (-26.104 + -21.6787) / 2;
// const float b = (376.423 + 314.796) / 2;
// const float c = (-1844.96 + -1555.59) / 2;
// const float d = (3076.86 + 2617.45) / 2; 
// const float e = 0;

//old calc output
// const float a = -45.33397015;
// const float b = 667.0383726;
// const float c = -3463.684349;
// const float d = 7012.514715; 
// const float e = -3470.181557; //-3520.181557;

//old
// const float a = -26.104;
// const float b = 376.423;
// const float c = -1844.96;
// const float d = 3076.86; 
// const float e = 0;

// //new
// const float a = -22.2405;
// const float b = 325.386;
// const float c = -1614.57;
// const float d = 2728.99; 
// const float e = 0;

const float a = 0.463805;
const float b = 2.47632;
const float c = 1.77708;
const float d = 0.330908; 
const float e = 91.6197;


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

  if(vOut != 0 && n < NUM_SAMPLES) {
    //volt to mass to equation
    mass = a * pow(b, (c * vOut + d)) + e;

    ignoreSamples(mass, vOut);

    Serial.print("vOut: " + String{vOut} + ", Mass: " + String{mass});

    n++;

    outputAvgMass();

    Serial.println();
  }
  else if(vOut == 0) {
    clearSamples();
    clear();
  }
  else if(vOut != 0)
  {
    Serial.println("v: " + String{vOut});
  }

  delay(500);
}
