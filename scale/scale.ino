/*
  Linn-Mar Science Olympiad Detector Building 2022 - 2023
*/

// initialize LEDs and Input Pin
int IN_PIN = 0;

int LED_RED = 4;
int LED_GREEN = 3;
int LED_BLUE = 2;

const int NUM_SAMPLES = 5;
const int NUM_TO_IGNORE = 2;
float samples[NUM_SAMPLES]; 
int n = -1*NUM_TO_IGNORE;

float mass = 0;

// // mass(g) thresholds TBD at competition
float redzone[2] = {30, 350};
float greenzone[2] = {351, 670};
float bluezone[2] = {671, 1000};           

void push(float f, float* array) {
  for (int i = NUM_SAMPLES-1; i > 0; i--) {
    array[i] = array[i-1];      
  }
  array[0] = f;
}

float mean(float* array, float num) {
  float sum = 0;
  for (int i = 0; i < num; i++) {
    sum = sum + array[i];
  }
  return sum/num;
}

// the setup routine runs once when you press reset:
void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(IN_PIN, INPUT);    
  //pinMode(T_PIN, INPUT);
  Serial.begin(9600);
  Serial.println("Scale initialized.\n");
}

// turns on LED based on threshold
void selectLED(float mass)
{
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

// the loop routine runs over and over again forever:
void loop() {
  // if(sample_count < 10) {
  //   sample_count += 1; // ensures that the average for the first 10 samples is correct
  // }

  // analog to digital conve  rsion
  float rawValue = analogRead(IN_PIN); //10 ADC
  //float rawT = analogRead(T_PIN); //10 ADC
  float vOut = rawValue * (5.0 / 1023.0);

  // print values
  // Serial.print("Raw: ");
  // Serial.print(rawValue);  
  if(vOut != 5 && n < NUM_SAMPLES)
  {
    // put volt to mass to equation here
    //mass = pow(-11.99466834 * vOut + 62.0256739, 2);
    mass = -45.33397014705 * pow(vOut, 4) + 667.0383726410 * pow(vOut, 3) - 3463.6843488301 * pow(vOut, 2) + 7012.5147149015 * vOut - 3470.1815571696;
    // mass = map(vOut, 0, 5, 30, 1000); 

    if(n >= 0) {
      push(mass, samples);
    }
    else
    {
      Serial.print("Ignoring... ");
    }
    Serial.print("vOut: ");
    Serial.print(vOut);
    Serial.print(", Mass: ");
    Serial.print(mass);

    n++;

    if(n == NUM_SAMPLES)
    {
      Serial.print("\nAVG MASS: ");
      Serial.print(mean(samples, n));
      Serial.println();
      selectLED(mean(samples, n));
    }

    Serial.println();
  }
  else if(vOut == 5)
  {
    n = -1*NUM_TO_IGNORE;
    for(int i = 0; i < NUM_SAMPLES; i++) 
    {
      samples[i] = 0;
    }

    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BLUE, LOW);
  }


  delay(1000);
}
