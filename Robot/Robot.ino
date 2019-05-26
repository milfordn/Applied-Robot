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
  PIN_DRIVE_LEFT_IN1,
  PIN_DRIVE_LEFT_IN2,
  PIN_ENCODER_LEFT_A,
  PIN_ENCODER_LEFT_B
);

Wheel rightWheel(
  PIN_DRIVE_RIGHT_PWM,
  PIN_DRIVE_RIGHT_IN1,
  PIN_DRIVE_RIGHT_IN2,
  PIN_ENCODER_RIGHT_A,
  PIN_ENCODER_RIGHT_B
);

//HBridge leftWheel(
//  PIN_DRIVE_LEFT_PWM,
//  PIN_DRIVE_LEFT_IN1,
//  PIN_DRIVE_LEFT_IN2
//);
//
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

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  Serial.println("Connected");
  loadingServo.attach(PIN_SERVO_LOAD);

  Wheel::registerLeftRight(&leftWheel, &rightWheel);

  pinMode(PIN_SWITCH_LATCH_1, INPUT);
  pinMode(PIN_SWITCH_LATCH_2, INPUT);
}

bool endof  = false;

void loop() {
  // put your main code here, to run repeatedly:

  if(leftWheel.getDistance() < 60){
    leftWheel.drive(150);
  }
  else{
    leftWheel.drive(0);
  }

  if(rightWheel.getDistance() < 60){
  }
  else{
    rightWheel.drive(0);
  }

  Serial.println(leftWheel.getDistance());
//  Serial.println(rightWheel.getDistance());

  return;
  
 if(Serial.available() > 0){
   action = Serial.read();
 }

  int lmotor,rmotor,index;
  int mvalsread = 0;
  unsigned long before,after;
 switch(action){

  case 'L':
    lmotor = Serial.parseInt();
//    Serial.print("Left Motor: ");
//    Serial.println(lmotor);
    leftWheel.drive((short)lmotor);
    break;

  case 'R':
    rmotor = Serial.parseInt();
//    Serial.print("Right Motor: ");
//    Serial.println(rmotor);
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
//     catapultMotor.drive(100);
     break;

   case 'k':
     Serial.println("Latching arm");
     while(digitalRead(PIN_SWITCH_LATCH_1) == LOW){ //DRIVE WHILE SWITCH IS OPEN
       latchMotor.drive(100);
     }
     latchMotor.brake();
     break;

   case 'r':
     Serial.println("Releasing Arm motor");
//     catapultMotor.drive(-100);
     break;

   case 's':
     Serial.println("Releasing Latch");
//     latchMotor.drive(-100);
     break;
 }

}
