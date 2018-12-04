
#define PIN_M_ENC_0 (2)
#define PIN_M_ENC_1 (3)
#define PIN_M_EN (11)
#define PIN_M_A (10)
#define PIN_M_B (9)
#define PIN_PB_0 (8)
#define PIN_PB_1 (7)
#define PIN_POT (A0)

int32_t curr_pos = 0;

void encoder_isr()
{
  bool direction = digitalRead(PIN_M_ENC_1);
  if(direction == HIGH) curr_pos++;
  else curr_pos--;
}

void setup()
{
  pinMode(PIN_M_ENC_0, INPUT);
  pinMode(PIN_M_ENC_1, INPUT);
  pinMode(PIN_M_EN, OUTPUT);
  pinMode(PIN_M_A, OUTPUT);
  pinMode(PIN_M_B, OUTPUT);
  pinMode(PIN_PB_0, INPUT);
  pinMode(PIN_PB_1, INPUT);
  
  attachInterrupt(digitalPinToInterrupt(PIN_M_ENC_0), encoder_isr, RISING);
}

void loop()
{
  // set motor speed
  uint16_t pot_val = analogRead(PIN_POT);
  analogWrite(PIN_M_EN, pot_val >> 2);
  
  // set motor direction
  if(digitalRead(PIN_PB_0) == LOW)
  {
    digitalWrite(PIN_M_A, HIGH);
    digitalWrite(PIN_M_B, LOW);
  }
  else if(digitalRead(PIN_PB_1) == LOW)
  {
    digitalWrite(PIN_M_A, LOW);
    digitalWrite(PIN_M_B, HIGH);
  }
  else
  {
    digitalWrite(PIN_M_A, LOW);
    digitalWrite(PIN_M_B, LOW);
  }
}
