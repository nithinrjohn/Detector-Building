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
float v_samples[NUM_SAMPLES];

float samples_new[NUM_SAMPLES];
float samples_old[NUM_SAMPLES];

int n = -1*NUM_TO_IGNORE;

float mass_new = 0;
float mass_old = 0;

float mass = 0;

//mass(g) thresholds TBD at competition
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
  // analog to digital conve  rsion
  float rawValue = analogRead(IN_PIN); //10 ADC
  float vOut = rawValue * (5.0 / 1023.0);

  if(vOut != 5 && n < NUM_SAMPLES) {
    // put volt to mass to equation here
    mass = vOut
    mass_new = vOut;
    mass_old = vOut;

    if(n >= 0) {
      push(mass, samples);
      push(vOut, v_samples);

      push(mass_new, samples_new);
      push(mass_old, samples_old);
    }
    else
    {
      Serial.print("Ignoring... ");
    }
    Serial.print("vOut: ");
    Serial.print(vOut);
    Serial.print(", Mass: ");
    Serial.print(mass);

    Serial.print(", New: ");
    Serial.print(mass_new);
    Serial.print(", Old: ");
    Serial.print(mass_old);

    n++;

    if(n == NUM_SAMPLES) {
      Serial.print("\nAVG: ");
      Serial.print(mean(samples, n));

      Serial.print("\nNEW: ");
      Serial.print(mean(samples_new, n));
      Serial.print("\nOLD: ");
      Serial.print(mean(samples_new, n));
      
      Serial.print("\nV: ");
      Serial.print(mean(v_samples, n));

      Serial.println();
      selectLED(mean(samples, n));
    }

    Serial.println();
  }
  else if(vOut == 5) {
    n = -1*NUM_TO_IGNORE;

    for(int i = 0; i < NUM_SAMPLES; i++) {
      samples[i] = 0;
    }

    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BLUE, LOW);
  }

  delay(500);
}
