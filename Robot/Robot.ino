#include "Mapping.h"
#include "Wheel.h"
#include "HBridge.h"
#include "Switch.h"
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

Switch latchOpen(
  PIN_SWITCH_LATCH_OPEN
);

Switch latchClose(
  PIN_SWITCH_LATCH_CLOSE
);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  Serial.println("Connected");
  loadingServo.attach(PIN_SERVO_LOAD);

  Wheel::registerLeftRight(&leftWheel, &rightWheel);

  latchOpen.setInverted(true);
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
     while(!digitalRead(PIN_SWITCH_LATCH_CLOSE)){ //DRIVE WHILE SWITCH IS OPEN
       latchMotor.drive(-255);
     }
    delay(50);
    Serial.println("Arm Latched");
    latchMotor.brake();
    catapultMotor.drive(-150);
    delay(500);
    catapultMotor.brake();
    
     break;

   case 'a':
     Serial.println("Releasing latch");
     while(digitalRead(PIN_SWITCH_LATCH_OPEN)){ //DRIVE WHILE SWITCH IS OPEN
       latchMotor.drive(255);
     }
     latchMotor.brake();
     Serial.println("Latch released");
     break;
  
   case 's':
     Serial.println("Launching Catapult");
     catapultMotor.drive(50);
     delay(1500);
     catapultMotor.drive(0);
     while(digitalRead(PIN_SWITCH_LATCH_OPEN)){ //DRIVE WHILE SWITCH IS OPEN
       latchMotor.drive(255);
     }
      Serial.println("Latch Released");
      latchMotor.brake();
     break;

    case '0':
     catapultMotor.drive(0);
     latchMotor.drive(0);
     leftWheel.drive(0);
     rightWheel.drive(0);

     default:
     break;
 }

}
