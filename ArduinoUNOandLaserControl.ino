// ***********************************************************
// Template to control ARDUINO UNO using a laser pointer
// by Tecnoprofesor
// ***********************************************************
int movement = 0;
boolean stop_right = false;
const int timestop = 200;
char reply[100];

void setup() {
  Serial.begin(115200);

  // Laser receptor
  pinMode(6, INPUT_PULLUP);
  
  // Leds
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);  
  // L293D
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);  
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);  

  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);

}


void StopRobot() {
  // L293D
  // Stop both motors
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);          
  digitalWrite(12,LOW);
  delay(timestop); 
}

void loop() {  

  if (digitalRead(6) == HIGH) {
    if (movement == 0) {
      reply[0] = '1';
    }
    if (movement == 1) {
      reply[0] = '3';
    }
    //end the string
    reply[1] = '\0';
    Serial.print(reply);
  } else {
    reply[0] = '\0';
    Serial.print(reply);    
  }

  switch (String(reply).toInt()) {
    case 1: //Go fordward
      StopRobot();
      delay(250);
      movement = 1;
      // Leds
      digitalWrite(2,LOW);
      digitalWrite(3,HIGH);
      digitalWrite(4,LOW);
      //DesSyncMotors();
      digitalWrite(7,HIGH);          
      digitalWrite(8,HIGH);
      digitalWrite(10,HIGH);          
      digitalWrite(12,HIGH);
      break;
    case 3: //Stop robot
      movement = 0;
      // Leds
      digitalWrite(2,LOW);
      digitalWrite(3,LOW);
      digitalWrite(4,LOW);
      StopRobot();
      break;
  }  
  delay(100);
}
