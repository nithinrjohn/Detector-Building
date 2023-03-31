/*
  Linn-Mar Science Olympiad Detector Building 2022 - 2023
*/

const int NUM_SAMPLES = 5;
const int NUM_TO_IGNORE = 2;
float m_samples[NUM_SAMPLES];
float v_samples[NUM_SAMPLES];

int n = -1*NUM_TO_IGNORE;

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

void ignoreSamples(float mass, float vOut) {
    if(n >= 0) {
      push(mass, m_samples);
      push(vOut, v_samples);
    }
    else {
      Serial.print("Ignoring... ");
    }
}

void outputAvgMass() {
    if(n == NUM_SAMPLES)
    {
      float avg_m = mean(m_samples, n);
      
      Serial.print("\nAVG MASS: ");
      Serial.print(avg_m);

      selectLED(avg_m);

      float avg_v = mean(v_samples, n);

      Serial.print("\nAVG vOut: ");
      Serial.print(avg_v);
      Serial.println();

      displayMass(avg_m, avg_v);
    }
}

void clearSamples() {
    n = -1*NUM_TO_IGNORE;

    for(int i = 0; i < NUM_SAMPLES; i++) 
    {
      m_samples[i] = 0;
      v_samples[i] = 0;
    }
}