#include "Mapping.h"
#include "Wheel.h"
#include "HBridge.h"
#include <Servo.h>

char action;
bool moving = false;
bool obstacle = false;

Servo loadingServo;

Wheel leftWheel(
  PIN_DRIVE_LEFT_PWM,
  PIN_ENCODER_LEFT_A,
  PIN_ENCODER_LEFT_B
);

Wheel rightWheel(
  PIN_DRIVE_RIGHT_PWM,
  PIN_ENCODER_RIGHT_A,
  PIN_ENCODER_RIGHT_B
);

//HBridge leftWheel(
//  PIN_DRIVE_LEFT_EN,
//  PIN_DRIVE_LEFT_IN1,
//  PIN_DRIVE_LEFT_IN2
//);
//HBridge rightWheel(
//  PIN_DRIVE_RIGHT_PWM,
//  PIN_DRIVE_RIGHT_IN1,
//  PIN_DRIVE_RIGHT_IN2
//);

HBridge latchMotor(
  PIN_MOTOR_LATCH_EN,
  PIN_MOTOR_LATCH_IN1,
  PIN_MOTOR_LATCH_IN2
);

HBridge catapultMotor(
  PIN_MOTOR_CATAPULT_EN,
  PIN_MOTOR_CATAPULT_IN1,
  PIN_MOTOR_CATAPULT_IN2
);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  Serial.println("Connected");
  loadingServo.attach(PIN_SERVO_LOAD);

  // Wheel::registerLeftRight(&leftWheel, &rightWheel);
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
int mvalsread = 0;
unsigned long before,after;
 switch(action){

   //joystick
//  case 'M':
//     while(mvalsread<2){
//       validate = Serial.read();
//       if(validate=='L'){
//         lmotor = Serial.parseInt();
//         mvalsread++;
//       } 
//       else if(validate == 'R'){
//         rmotor = Serial.parseInt();
//         mvalsread++;  
//       }
//     }
//     if(mvalsread == 2){
//       Serial.print("Left Motor: ");
//       Serial.println(lmotor);
//       Serial.print("Right Motor: ");
//       Serial.println(rmotor);     
//       rightWheel.drive((byte)rmotor);
//       leftWheel.drive((byte)lmotor);
//     } else {
//       Serial.println("Malformed String for Motor!");
//     }
//    break;

  case 'L':
    lmotor = Serial.parseInt();
    Serial.print("Left Motor: ");
    Serial.println(lmotor);
    leftWheel.drive((short)lmotor);
    break;

  case 'R':
    rmotor = Serial.parseInt();
    Serial.print("Right Motor: ");
    Serial.println(rmotor);
    rightWheel.drive((short)rmotor);
    break;
    
  case 'l':
    Serial.println("Moving Loading servo");
    loadingServo.write(loadingServo.read() + 90);
    break;

  case 'u':
    Serial.println("Resetting servo");
    loadingServo.write(0);
    break;

   case 'p':
     Serial.println("Pulling arm back");
     catapultMotor.drive(100);
     break;

   case 'k':
     Serial.println("Latching arm");
     if(digitalRead(PIN_SWITCH_LATCH)){
       latchMotor.drive(100);
     }
     else{
       latchMotor.brake();
     }
     break;

   case 'r':
     Serial.println("Releasing Arm motor");
     catapultMotor.drive(-100);
     break;

   case 's':
     Serial.println("Releasing Latch");
     latchMotor.drive(-100);
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
    rightWheel.ss();
  }
}
 */
