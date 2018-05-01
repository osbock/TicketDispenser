//relay test
#define DRIVEPIN 3
#define NOTCH 5
#define JOYX A0
#define JOYY A1

void setup() {
  pinMode(DRIVEPIN,OUTPUT);
  digitalWrite(DRIVEPIN,LOW);
  pinMode(NOTCH,INPUT_PULLUP);
  Serial.begin(115200);

}
#define DEBUGTIMING
#ifdef DEBUGTIMING
#define STATEOUT Serial.println(reading);
#else
#define STATEOUT delay(10);
#endif
void dispense(int num){

  int reading;
  for(int i = 0; i <num ; i++){
    reading = digitalRead(NOTCH);
    STATEOUT
    digitalWrite(DRIVEPIN,HIGH);
    delay(10);
    // normally high, wait to go low.
    while(reading = digitalRead(NOTCH) == HIGH)
      STATEOUT
    // when it comes back up, we've dispensed one ticket
    while(reading = digitalRead(NOTCH) == LOW)
     STATEOUT
    STATEOUT
    digitalWrite(DRIVEPIN,LOW);
    delay(100);
    while(reading = digitalRead(NOTCH) == LOW)
      STATEOUT
      Serial.println(4);
  }

}
void loop() {

  int x = analogRead(JOYX);
  int y = analogRead(JOYY);

    int reading = digitalRead(NOTCH);
    STATEOUT
  // 1023 is up
  // 0 is down
  // 1023 is left (toward usb)
  // 0 is right
  if (y > 1000){
    dispense(1);
    delay(500);
  }
  if (y < 100){
    dispense (2);
    delay(500);
  }
  if (x > 1000){
    dispense(3);
    delay(500);
  }
  if (x < 100){
    dispense (4);
    delay(500);
  }
  


  if (Serial.available()){
    char c = Serial.read();
    if (c >='1' && c <='9'){
      dispense(int(c-0x30));
    }
  }
}
