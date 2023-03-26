/*
  Linn-Mar Science Olympiad Detector Building 2021 - 2022
*/

// initialize LEDs and Input Pin
int IN_PIN = 0;
int LED_RED = 2;
int LED_GREEN = 3;
int LED_BLUE = 4;

float ppm = 0;

// ppm thresholds TBD at competition
float redzone[2] = {0, 1666};
float greenzone[2] = {1667, 3333};
float bluezone[2] = {3334, 5000};

// the setup routine runs once when you press reset:
void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(IN_PIN, INPUT);
  Serial.begin(9600);
}

// turns on LED based on threshold
void selectLED(float ppm)
{
  if( ppm >= redzone[0] && ppm <= redzone[1] )
  {
      digitalWrite(LED_RED, HIGH);
  }
  else if( ppm >= greenzone[0] && ppm <= greenzone[1] )
  {
      digitalWrite(LED_GREEN, HIGH);
  }
  else if( ppm >= bluezone[0] && ppm <= bluezone[1] )
  {
      digitalWrite(LED_BLUE, HIGH);
  }
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, LOW);

  // analog to digital conversion
  float rawValue = analogRead(IN_PIN);
  float vOut = rawValue * (5.0 / 1023.0);
  float vW = 5.0 - vOut;
  
  // print values
  Serial.print("Raw: ");
  Serial.print(rawValue);
  Serial.print(", V_out: ");
  Serial.print(vOut);
  Serial.print(", V_W: ");
  Serial.print(vW);
  Serial.println();

  // put volt to ppm to equation here
  
  //Exponential 
  //ppm = (0.0000265258 * pow(28.5941, vOut)) * 1000;

  //Exponential Piecewise
  if(vOut < 3.168)
  {
    ppm = (0.00919202 * pow(4.4544, vOut)) * 1000;    
  }

  if(vOut > 3.168)
  {
    ppm = (0.0000177423 * pow(32.0208, vOut)) * 1000;    
  }


  Serial.print(ppm);
  Serial.println();

  selectLED(ppm);

  delay(500);
}
