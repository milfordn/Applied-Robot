#include "Mapping.h"
#include "Wheel.h"
#include "HBridge.h"
#include "Switch.h"
#include "RealTimeDelay.h"
#include <Servo.h>

#define STATE_DEFAULT 0 //catapult unpulled, latch disengaged, can drive
#define STATE_PULLBACK 1 //catapult motor pulling back
#define STATE_LATCHING 2 //latch engaging
#define STATE_LATCHED 3 //latch engaged
#define STATE_UNLATCHING 4 //latch disengaging
#define STATE_LOAD 5 //latched
#define STATE_LOAD_RESET 6

#define BUTTON_DRIVE_LEFT 'L'
#define BUTTON_DRIVE_RIGHT 'R'
#define BUTTON_LOAD 'l'
#define BUTTON_LOAD_RESET 'u'
#define BUTTON_ARM_PULL 'p'
#define BUTTON_LATCH 'k'
#define BUTTON_UNLATCH 'a'
#define BUTTON_ARM_UNWIND 's'
#define BUTTON_RESET '0'

char action;
byte state = STATE_DEFAULT;
RealTimeDelay rtDelay;

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
  pinMode(PIN_SERVO_LOAD, OUTPUT);
  loadingServo.attach(PIN_SERVO_LOAD);
  loadingServo.write(0);

  Wheel::registerLeftRight(&leftWheel, &rightWheel);

  latchOpen.setInverted(true);
}

void setState(byte next){
  Serial.println(next);
  state = next;
}

//if action matches the given transition, then go to the next state
void pollAction(char transitionAction, byte nextState){
  if(action == transitionAction){
    setState(nextState);
  }
}

void drive(char action){
  if(action == BUTTON_DRIVE_LEFT){
    leftWheel.drive(Serial.parseInt());
  }
  else if(action == BUTTON_DRIVE_RIGHT){
    rightWheel.drive(Serial.parseInt());
  }
}

void loadOne(){
  loadingServo.write(loadingServo.read() + 90);
}

void loop() {
  // put your main code here, to run repeatedly:
 if(Serial.available() > 0){
   action = Serial.read();
 }

//Valid transitions:
//STATE_DEFAULT -> STATE_PULLBACK
//STATE_PULLBACK -> STATE_LATCHING
//STATE_LATCHING -> STATE_LATCHED
//STATE_LATCHED -> STATE_UNLATCHING
//STATE_UNLATCHING -> STATE_DEFAULT
//STATE_DEFAULT -> STATE_UNLATCHING
//(any state) -> STATE_DEFAULT

  drive(action);

  switch(state){
    case STATE_DEFAULT:
      //run drive motors
      catapultMotor.drive(0);
      latchMotor.brake();
      pollAction(BUTTON_ARM_PULL, STATE_PULLBACK);
      pollAction(BUTTON_UNLATCH, STATE_UNLATCHING);
      pollAction(BUTTON_LOAD_RESET, STATE_LOAD_RESET);
      break;
    case STATE_PULLBACK:
      //run catapult motor
      catapultMotor.drive(-255);
      pollAction(BUTTON_LATCH, STATE_LATCHING);
      pollAction(BUTTON_RESET, STATE_DEFAULT);
      break;
    case STATE_LATCHED:
      //unwind motor
      if(!rtDelay.complete()){
        catapultMotor.drive(50);
      }
      else{
        //wait for launch
        catapultMotor.brake();
        pollAction(BUTTON_LOAD, STATE_LOAD);
        pollAction(BUTTON_UNLATCH, STATE_UNLATCHING);
      }
      pollAction(BUTTON_RESET, STATE_DEFAULT);
      pollAction(BUTTON_LOAD_RESET, STATE_LOAD_RESET);
      break;
    case STATE_LATCHING:
      //run latch motor
      rtDelay.setDelay(500);
      //poll for switch
      if(digitalRead(PIN_SWITCH_LATCH_CLOSE)){
        //Switch Pressed
        if(rtDelay.complete()){
          //set up delay for unwinding motor
          rtDelay.reset();
          rtDelay.setDelay(1700);
          setState(STATE_LATCHED);
        }
        latchMotor.brake();
        catapultMotor.drive(-100);
      }
      else{
//        Serial.println("Waiting for close switch");
        //Switch Open
        latchMotor.drive(-255);
        catapultMotor.drive(-255);
        rtDelay.reset();
        //reset if we need to
        pollAction(BUTTON_RESET, STATE_DEFAULT);
      }
      break;
    case STATE_UNLATCHING:
      //run latch motor
      if(!digitalRead(PIN_SWITCH_LATCH_OPEN)){
        //switch pressed
        latchMotor.brake();
        setState(STATE_DEFAULT);
      }
      else{
        latchMotor.drive(255);
      }
      //poll for switch
      break;

    case STATE_LOAD:
      loadOne();
      setState(STATE_LATCHED);
      break;

    case STATE_LOAD_RESET:
      loadingServo.write(0);
      setState(STATE_DEFAULT);
      break;
  }
}
