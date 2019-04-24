#include <L298N.h>

#define EN1 3
#define EN2 4
#define IN1_1 8
#define IN1_2 9
#define IN2_1 10
#define IN2_2 11

#define LED1 10
#define LED2 9
#define LED3 8
#define LED4 7

char action;
bool moving = false;
bool obstacle = false;


void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  Serial.println("Connected");

  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  action=0;

  if(Serial.available() > 0){
    action = Serial.read();
    //Serial.println(action);
  }

  switch(action){
    //Moving start/stop
    case 'm':
      Serial.println("Moving...");
      moving = true;
      
      break;
    case 'n':
      Serial.println("Stopping...");
      moving = false;
      
      break;

    //Obstacle exists/clear
    case 'o':
      if(moving)
        Serial.println("Obstacle encountered, pause.");
      obstacle = true;
      
      break;
    case 'c':
      if(moving)
        Serial.println("Clear to go!");
      obstacle = false;
      
      break;

    //LED exhibition
    case 'd':
      Serial.println("LED BOUNCE ON");
      ledbounce(10);

      break;
    case 's':
      Serial.println("LED LINE ON");
      ledline(10);

      break;
    case 'a':
      Serial.println("LED FLICKER ON");
      altflicker(5);

      break;
    case 'i':
      int integer = Serial.parseInt();
      Serial.print("Got integer: ");
      Serial.println(integer);
  
      break;
  }

  move();
}

void move(){
  if(moving){ //IF WE SHOULD BE MOVING
    digitalWrite(LED1,HIGH);
    if(!obstacle){ //There is no obstacle
      digitalWrite(LED3,LOW);
      digitalWrite(LED4,HIGH);
      
      //MOTOR LOGIC HERE
      
    } else { //There is an obstacle
      digitalWrite(LED3,HIGH);
      digitalWrite(LED4,LOW);

      //STOP MOTORS OR SWERVE
    }
  } else{ //IF NOT
    digitalWrite(LED1,LOW);
    digitalWrite(LED3,LOW);
    digitalWrite(LED4,LOW);

    //Turn off motors
  }
}

void ledline(int n){
  int d = 50;
  for(int i=0; i<n; i++){
    digitalWrite(LED1,HIGH);
    delay(d);
    digitalWrite(LED2,HIGH);
    delay(d);
    digitalWrite(LED3,HIGH);
    digitalWrite(LED1,LOW);
    delay(d);
    digitalWrite(LED4,HIGH);
    digitalWrite(LED2,LOW);
    delay(d);
    digitalWrite(LED3,LOW);
    delay(d);
    digitalWrite(LED4,LOW);
  }
}

void ledbounce(int n){
  int d = 50;
  for(int i=0; i<n; i++){
    digitalWrite(LED1,HIGH);
    delay(d);
    digitalWrite(LED2,HIGH);
    delay(d);
    digitalWrite(LED3,HIGH);
    digitalWrite(LED1,LOW);
    delay(d);
    digitalWrite(LED4,HIGH);
    digitalWrite(LED2,LOW);
    delay(d);
    digitalWrite(LED3,LOW);
    delay(d);
    
    digitalWrite(LED3,HIGH);
    delay(d);
    digitalWrite(LED2,HIGH);
    digitalWrite(LED4,LOW);
    delay(d);
    digitalWrite(LED1,HIGH);
    digitalWrite(LED3,LOW);
    delay(d);
    digitalWrite(LED2,LOW);
    delay(d);
    digitalWrite(LED1,LOW);
  }
}

void altflicker(int n){
  int d = 250;
  for(int i=0;i<n;i++){
    digitalWrite(LED2,LOW);
    digitalWrite(LED4,LOW);
    digitalWrite(LED1,HIGH);
    digitalWrite(LED3,HIGH);
    delay(d);

    digitalWrite(LED2,HIGH);
    digitalWrite(LED4,HIGH);
    digitalWrite(LED1,LOW);
    digitalWrite(LED3,LOW);
    delay(d);
    
  }
  off();
}

void off(){
  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);
  digitalWrite(LED3,LOW);
  digitalWrite(LED4,LOW);
}
