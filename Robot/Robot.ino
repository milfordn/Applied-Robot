#include "Mapping.h"
#include "Wheel.h"

char action;
bool moving = false;
bool obstacle = false;

Wheel leftWheel(
  PIN_DRIVE_LEFT_EN, 
  PIN_DRIVE_LEFT_IN1, 
  PIN_DRIVE_LEFT_IN2, 
  PIN_ENCODER_LEFT_A, 
  PIN_ENCODER_LEFT_B
);

Wheel rightWheel(
  PIN_DRIVE_RIGHT_EN,
  PIN_DRIVE_RIGHT_IN1,
  PIN_DRIVE_RIGHT_IN2,
  PIN_ENCODER_RIGHT_A,
  PIN_ENCODER_RIGHT_B
);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  Serial.println("Connected");

  pinMode(PIN_DEBUG_LED_1, OUTPUT);
  pinMode(PIN_DEBUG_LED_2, OUTPUT);
  pinMode(PIN_DEBUG_LED_3, OUTPUT);
  pinMode(PIN_DEBUG_LED_4, OUTPUT);

  Wheel::registerLeftRight(&leftWheel, &rightWheel);
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
    digitalWrite(PIN_DEBUG_LED_1,HIGH);
    if(!obstacle){ //There is no obstacle
      digitalWrite(PIN_DEBUG_LED_3,LOW);
      digitalWrite(PIN_DEBUG_LED_4,HIGH);
      
      //MOTOR LOGIC HERE
      leftWheel.drive(-100);
    } else { //There is an obstacle
      digitalWrite(PIN_DEBUG_LED_3,HIGH);
      digitalWrite(PIN_DEBUG_LED_4,LOW);

      //STOP MOTORS OR SWERVE
      leftWheel.drive(100);
    }
  } else{ //IF NOT
    digitalWrite(PIN_DEBUG_LED_1,LOW);
    digitalWrite(PIN_DEBUG_LED_3,LOW);
    digitalWrite(PIN_DEBUG_LED_4,LOW);
    
    //Turn off motors
    leftWheel.drive(0);
  }
}

void ledline(int n){
  int d = 50;
  for(int i=0; i<n; i++){
    digitalWrite(PIN_DEBUG_LED_1,HIGH);
    delay(d);
    digitalWrite(PIN_DEBUG_LED_2,HIGH);
    delay(d);
    digitalWrite(PIN_DEBUG_LED_3,HIGH);
    digitalWrite(PIN_DEBUG_LED_1,LOW);
    delay(d);
    digitalWrite(PIN_DEBUG_LED_4,HIGH);
    digitalWrite(PIN_DEBUG_LED_2,LOW);
    delay(d);
    digitalWrite(PIN_DEBUG_LED_3,LOW);
    delay(d);
    digitalWrite(PIN_DEBUG_LED_4,LOW);
  }
}

void ledbounce(int n){
  int d = 50;
  for(int i=0; i<n; i++){
    digitalWrite(PIN_DEBUG_LED_1,HIGH);
    delay(d);
    digitalWrite(PIN_DEBUG_LED_2,HIGH);
    delay(d);
    digitalWrite(PIN_DEBUG_LED_3,HIGH);
    digitalWrite(PIN_DEBUG_LED_1,LOW);
    delay(d);
    digitalWrite(PIN_DEBUG_LED_4,HIGH);
    digitalWrite(PIN_DEBUG_LED_2,LOW);
    delay(d);
    digitalWrite(PIN_DEBUG_LED_3,LOW);
    delay(d);
    
    digitalWrite(PIN_DEBUG_LED_3,HIGH);
    delay(d);
    digitalWrite(PIN_DEBUG_LED_2,HIGH);
    digitalWrite(PIN_DEBUG_LED_4,LOW);
    delay(d);
    digitalWrite(PIN_DEBUG_LED_1,HIGH);
    digitalWrite(PIN_DEBUG_LED_3,LOW);
    delay(d);
    digitalWrite(PIN_DEBUG_LED_2,LOW);
    delay(d);
    digitalWrite(PIN_DEBUG_LED_1,LOW);
  }
}

void altflicker(int n){
  int d = 250;
  for(int i=0;i<n;i++){
    digitalWrite(PIN_DEBUG_LED_2,LOW);
    digitalWrite(PIN_DEBUG_LED_4,LOW);
    digitalWrite(PIN_DEBUG_LED_1,HIGH);
    digitalWrite(PIN_DEBUG_LED_3,HIGH);
    delay(d);

    digitalWrite(PIN_DEBUG_LED_2,HIGH);
    digitalWrite(PIN_DEBUG_LED_4,HIGH);
    digitalWrite(PIN_DEBUG_LED_1,LOW);
    digitalWrite(PIN_DEBUG_LED_3,LOW);
    delay(d);
    
  }
  off();
}

void off(){
  digitalWrite(PIN_DEBUG_LED_1,LOW);
  digitalWrite(PIN_DEBUG_LED_2,LOW);
  digitalWrite(PIN_DEBUG_LED_3,LOW);
  digitalWrite(PIN_DEBUG_LED_4,LOW);
}
