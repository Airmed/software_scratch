#include <Stepper.h>
 
const int stepsPerRevolution = 400;  
 
// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8,9,10,11);

int stepCount = 0;         // number of steps the motor has taken
int broken = 0;            // tracks if the beam has been broken: 0 if unbroken, 1 if broken
const byte hBridgeEnable = 12;    // set pin 12 to control the H-bridge
const byte interruptPin = 3;      // set pin 3 as the interrupt pin
int sensorAverage = 0;
int sensorValue = 0;
int i;
int sensorPrev;
 
void setup() {
  // set the speed:
  int stepperSpeed = 100;  // 150 rpm is the max speed
  myStepper.setSpeed(stepperSpeed);

  pinMode(hBridgeEnable, OUTPUT);
  
  // initialize the serial port:
  Serial.begin(9600);

  //pinMode(interruptPin, INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(interruptPin), beamBreak, CHANGE);
  int sensorArray[100];

  for(i = 0; i < 100; i++){
    sensorArray[i] = analogRead(A0);
  }
  int sensorTotal = 0;
  for(i = 0; i < 100; i++){
    sensorTotal = sensorTotal + sensorArray[i];
  }
  sensorAverage = sensorTotal/100;
  Serial.println(sensorAverage);
}
 
void loop() {
  //delay(10000);
  digitalWrite(hBridgeEnable, HIGH);  // enable the H-bridge
  
  while(stepCount < 95) {
    //myStepper.setSpeed(1);
    //digitalWrite(hBridgeEnable, HIGH);  // enable the H-bridge
    // step one step CCW:
    for(i = 0; i < 100; i++){
      sensorPrev = sensorValue;
      sensorValue = analogRead(A0);
      if(i == 1) Serial.println(sensorValue);
      if(sensorValue > sensorAverage + 20 && sensorPrev > sensorAverage + 20){
        Serial.println(sensorValue);
        beamBreak();
      }
      delay(1);
    }
    myStepper.step(-1);
    for(i = 0; i < 100; i++){
      sensorPrev = sensorValue;
      sensorValue = analogRead(A0);
      if(i == 1) Serial.println(sensorValue);
      if(sensorValue > sensorAverage + 20 && sensorPrev > sensorAverage + 20) {
        Serial.println(sensorValue);
        beamBreak();
      }
      delay(1);
    }
    stepCount++;
    //if(broken) break;    
  }

  //myStepper.setSpeed(50);
  myStepper.step(stepCount+4);
  stepCount = 0;
  Serial.println("no drop");
  digitalWrite(hBridgeEnable, LOW);  // disable the H-bridge
  delay(10000);
  //broken = 0;
}

void beamBreak() {
  //myStepper.step(-4);
  delay(10);
  myStepper.step(stepCount+6);
  digitalWrite(hBridgeEnable, LOW);  // disable the H-bridge
  Serial.println("Broken");
  delay(10000);
  int sensorArray[100];

  for(i = 0; i < 100; i++){
    sensorArray[i] = analogRead(A0);
  }
  int sensorTotal = 0;
  for(i = 0; i < 100; i++){
    sensorTotal = sensorTotal + sensorArray[i];
  }
  sensorAverage = sensorTotal/100;
  Serial.println(sensorAverage);
  stepCount = 0;
  digitalWrite(hBridgeEnable, HIGH);  // enable the H-bridge
  /*myStepper.step(-10);
  delay(100);
  myStepper.step(10);
  delay(100);
  myStepper.step(-10);
  delay(100);
  myStepper.step(10);
  delay(100);
  myStepper.step(-10);
  delay(100);
  myStepper.step(10);
  delay(100);
  myStepper.step(-10);
  delay(100);
  myStepper.step(10);
  delay(100);*/
}
