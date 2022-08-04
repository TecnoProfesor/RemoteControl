
int movement = 0;
boolean stop_right = false;
const int timestop = 200;
char reply[100];
#define speakerPin 5

void setup() {
  Serial.begin(115200);

  // Laser receptor
  pinMode(6, INPUT_PULLUP);
  
  // Leds
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);  
  // Buzzer
  pinMode(speakerPin,OUTPUT);  
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

void phrase1() {
    
    int k = random(1000,2000);
    for (int i = 0; i <=  random(100,2000); i++){
        int ledindex = random(2,5);
        digitalWrite(ledindex,HIGH);
        
        tone(speakerPin, k+(-i*2));          
        delay(random(.9,2));        
        digitalWrite(ledindex,LOW);     
    } 
    for (int i = 0; i <= random(100,1000); i++){
        int ledindex = random(2,5);
        digitalWrite(ledindex,HIGH);
        
        tone(speakerPin, k + (i * 10));          
        delay(random(.9,2));             
        digitalWrite(ledindex,LOW);     

    } 
}

void phrase2() {
    
    int k = random(1000,2000);
    for (int i = 0; i <= random(100,2000); i++){
        int ledindex = random(2,5);
        digitalWrite(ledindex,HIGH);
        
        tone(speakerPin, k+(i*2));          
        delay(random(.9,2));             
        digitalWrite(ledindex,LOW);     

    } 
    for (int i = 0; i <= random(100,1000); i++){
        int ledindex = random(2,5);
        digitalWrite(ledindex,HIGH);
        
        tone(speakerPin, k + (-i * 10));          
        delay(random(.9,2));             
        digitalWrite(ledindex,LOW);     

    } 
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

void DesSyncMotors() {
  // L293D
  if (stop_right) {
    digitalWrite(7,HIGH);
    delay(timestop);
    digitalWrite(7,LOW);
    delay(timestop);
    digitalWrite(7,HIGH);
    stop_right = false;
  } else {
    digitalWrite(10,HIGH);
    delay(timestop);
    digitalWrite(10,LOW);
    delay(timestop);
    digitalWrite(10,HIGH);  
    stop_right = true;    
  } 
}

void R2D2() {
    int K = 2000;
    switch (random(1,7)) {
        
        case 1:phrase1(); break;
        case 2:phrase2(); break;
        case 3:phrase1(); phrase2(); break;
        case 4:phrase1(); phrase2(); phrase1();break;
        case 5:phrase1(); phrase2(); phrase1(); phrase2(); phrase1();break;
        case 6:phrase2(); phrase1(); phrase2(); break;
    }
    for (int i = 0; i <= random(3, 9); i++){
        int ledindex = random(2,5);
        digitalWrite(ledindex,HIGH);
        tone(speakerPin, K + random(-1700, 2000));          
        delay(random(70, 170));  
        noTone(speakerPin);         
        delay(random(0, 30));       
        digitalWrite(ledindex,LOW);      
    } 
    noTone(speakerPin);           
}


void loop() {  

  if (digitalRead(6) == HIGH) {
    if (movement == 0) {
      R2D2();
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
    case 1: //Go backwards
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
    case 2: //Go forward
      StopRobot();
      delay(250);
      movement = 2;
      // Leds
      digitalWrite(2,LOW);
      digitalWrite(3,LOW);
      digitalWrite(4,HIGH);
      //DesSyncMotors();
      digitalWrite(7,HIGH);
      digitalWrite(9,HIGH);
      digitalWrite(10,HIGH);          
      digitalWrite(11,HIGH);
      break;
    case 3: //Stop robot
      movement = 0;
      // Leds
      digitalWrite(2,LOW);
      digitalWrite(3,LOW);
      digitalWrite(4,LOW);
      StopRobot();
      break;
    case 4: // Left movement
      if (movement == 1) {
        movement = 3;
        // Leds
        digitalWrite(2,HIGH);
        digitalWrite(3,HIGH);
        digitalWrite(4,LOW);
        // L293D
        // Stop left motor
        digitalWrite(10,LOW);
        digitalWrite(12,LOW);          
      }
      break;
    case 5: // Right movement
      if (movement == 1) {            
        movement = 4;
        // Leds
        digitalWrite(2,LOW);
        digitalWrite(3,HIGH);
        digitalWrite(4,HIGH);
        // L293D
        // Stop left motor
        digitalWrite(7,LOW);
        digitalWrite(8,LOW);          
      }
      break;
    case 6: // Async movement
      if ((movement == 1) or (movement == 2)) {DesSyncMotors();}
      break;
    case 7: // R2D2
      R2D2();
      break;
  }  
  delay(100);
}
