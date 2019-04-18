#include <L298N.h>

#define EN1 3
#define EN2 4
#define IN1_1 8
#define IN1_2 9
#define IN2_1 10
#define IN2_2 11

char action;

L298N motor1(EN1,IN1_1,IN1_2);
L298N motor2(EN2,IN2_1,IN2_2);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  action=0;

  if(Serial.available() > 0){
    action = Serial.read();
  }
  
  if(action == 'f'){
    driveForward(3000);
    turn(1,500);
    driveForward(3000);
  }
  
}




void stopMotor(L298N m){
  m.stop();
}

void backwardSpeed(L298N m,int s){
  m.setSpeed(s);
  m.backward();
}

void forwardSpeed(L298N m,int s){
  m.setSpeed(s);
  m.forward();
}


//BLOCKING
void driveForward(int t){
  forwardSpeed(motor1,255);
  forwardSpeed(motor2,255);
  delay(t);
  stopMotor(motor1);
  stopMotor(motor2);
}

//Dir is 1 or 0
//BLOCKING
void turn(int dir, int t){
  if(dir==0){
    forwardSpeed(motor1,255);
    backwardSpeed(motor2,255);
  } else {
    forwardSpeed(motor2,255);
    backwardSpeed(motor1,255);
  }
  delay(t);
  stopMotor(motor1);
  stopMotor(motor2);
}