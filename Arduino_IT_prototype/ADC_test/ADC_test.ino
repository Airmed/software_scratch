void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  int sensorArray[100];
  int i;
  for(i = 0; i < 100; i++){
    sensorArray[i] = analogRead(A0);
  }
  int sensorTotal = 0;
  for(i = 0; i < 100; i++){
    sensorTotal = sensorTotal + sensorArray[i];
  }
  int sensorAverage = sensorTotal/100;
  Serial.println(sensorAverage);
  while(1){
    int sensorValue = analogRead(A0);
    // print out the value you read:
    if(sensorValue > sensorAverage + 20){
      Serial.println(sensorValue);
    }
    delay(1);        // delay in between reads for stability
  }
  // read the input on analog pin 0:


  
}
