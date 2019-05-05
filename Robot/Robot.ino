#include "Mapping.h"
#include "Wheel.h"
#include "PIDF.h"
#include <Servo.h>

char action;
bool moving = false;
bool obstacle = false;

Servo loadingServo;

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
  loadingServo.attach(PIN_SERVO_LOAD);

  Wheel::registerLeftRight(&leftWheel, &rightWheel);
}

void loop() {
  // put your main code here, to run repeatedly:
  action=0;
   moving = true;

 if(Serial.available() > 0){
   action = Serial.read();
   Serial.println(action);
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

  case 'l':
    loadingServo.write(loadingServo.read() + 90);
    break;

  case 'u':
    loadingServo.write(0);
    break;

   case 'i':
     int in = Serial.parseInt();
     Serial.print("Got integer: ");
     Serial.println(in);
     break;
 }

  move();
}

void move(){
  if(moving){ //IF WE SHOULD BE MOVING
//    Serial.println("Driving");
    if(!obstacle){ //There is no obstacle 
      //MOTOR LOGIC HERE
      leftWheel.drive(255);
      rightWheel.drive(255);
    } else { //There is an obstacle
      //STOP MOTORS OR SWERVE
      leftWheel.drive(-100);
      rightWheel.drive(0);
    }
  } else{ //IF NOT
    //Turn off motors
//    Serial.println("Braking");
    leftWheel.brake();
    rightWheel.brake();
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
