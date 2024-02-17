# Detector-Building

My codebase for past Science Olympiad Detector Building events

https://www.soinc.org/detector-building-c

## 2021 - 2022 Electrical Conductivity Tester

Returns the concentration of a salt water solution in ppm

![Labeled Sensor](https://github.com/nithinrjohn/Detector-Building/assets/51685976/dbf265fb-fdac-442b-97f3-e2560e9456b6)

![Exponential Piecewise Function](https://github.com/nithinrjohn/Detector-Building/assets/51685976/634d053d-5412-4a18-8ce2-abf0a7423588)

## 2022 - 2023 Mass Sensing Device (1st place Iowa SciOly State Championship)

Returns the mass of an object in grams

The mass sensing device consists of an Arduino and an Interlink FSR 406, which is set up in a voltage divider configuration with two 5.1k ohm resistors in series for a total resistance of 10.2 ohms. The FSR (force sensitive resistor) is placed under a custom 3D printed box, which is designed to allow for the placement of larger weights than the FSR's size. The box concentrates the force of the weights onto the FSR. In addition to the FSR and 3D printed box, the device includes three LEDs (red, green, and blue), each attached to a 330 ohm resistor and the digital PWM pins of the Arduino to show varying mass thresholds. The voltage divider is attached to the first analog pin of the Arduino, and the entire device is powered by 5V from the Arduino. The mass sensing device is constructed using a wooden base, on top of which the Interlink FSR 406 is placed. To protect the FSR from damage, a layer of paper is placed over it. The custom 3D printed box is then placed on top of the FSR and secured to the wooden base. On top of the 3D printed box, a clear plastic CD case serves as the platform for the weights to be placed. The reading is then processed and the output voltage and mass are displayed on a Liquid Crystal Display (LCD) board.

![detector](https://github.com/nithinrjohn/Detector-Building/assets/51685976/706bea8f-9030-4a14-b9bc-19258b9ad0c5)

![Data](https://github.com/nithinrjohn/Detector-Building/assets/51685976/053dab3b-06ea-4281-b20e-2c6a232bdeef)
