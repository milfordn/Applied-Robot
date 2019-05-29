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

  Wheel::registerLeftRight(&leftWheel, &rightWheel);

  pinMode(PIN_SWITCH_LATCH_OPEN, INPUT_PULLUP);
  pinMode(PIN_SWITCH_LATCH_CLOSE, INPUT_PULLUP);
}

bool endof  = false;

void loop() {
  // put your main code here, to run repeatedly:
  
 if(Serial.available() > 0){
   action = Serial.read();
 }

  int lmotor,rmotor,index;
  int mvalsread = 0;
  unsigned long before,after;

//  Serial.println(digitalRead(PIN_SWITCH_LATCH_OPEN));

//  action = 'k';
 switch(action){

  case 'L':
    lmotor = Serial.parseInt();
    leftWheel.drive((short)lmotor);
    break;

  case 'R':
    rmotor = Serial.parseInt();
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
     catapultMotor.drive(-255);
     break;

   case 'k':
     Serial.println("Latching arm");
     while(digitalRead(PIN_SWITCH_LATCH_CLOSE) == LOW){ //DRIVE WHILE SWITCH IS OPEN
       latchMotor.drive(-150);
     }
    Serial.println("Arm Latched");
    latchMotor.brake();
    catapultMotor.drive(50);
    delay(2000);
    catapultMotor.brake();
    
     break;

   case 'r':
     Serial.println("Releasing Arm motor");
     catapultMotor.drive(-255);
     delay(100);
     catapultMotor.drive(0);
     break;

   case 's':
     Serial.println("Releasing Latch");
     while(digitalRead(PIN_SWITCH_LATCH_OPEN) == HIGH){ //DRIVE WHILE SWITCH IS OPEN
       latchMotor.drive(150);
     }
      Serial.println("Latch Released");
      latchMotor.brake();
     break;

     default:
     break;
 }

}
