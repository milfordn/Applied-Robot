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
 }

int lmotor,rmotor,index;
bool failure;
char validate;
 switch(action){

   //joystick
  case 'L':
    lmotor = Serial.parseInt();
    Serial.println(lmotor);
    leftWheel.drive(lmotor);
    break;

  case 'R':
    rmotor = Serial.parseInt();
    Serial.println(rmotor);
    rightWheel.drive(rmotor);
    break;

  case 'l':
    Serial.println("Got L");
    loadingServo.write(loadingServo.read() + 90);
    break;

  case 'u':
    loadingServo.write(0);
    break;

   case 'i':
     Serial.println(">i<");
     break;
 }

  //move();
}
/* 
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
 */
