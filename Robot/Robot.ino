#define EN1 10
#define EN2 13
#define IN1_1 9
#define IN1_2 8
#define IN2_1 12
#define IN2_2 11

#define ENC_1A 2
#define ENC_1B 6

#include "Mapping.h"

class Wheel{
    int pin_en;
    int pin_in1;
    int pin_in2;
    int pin_enc_a;
    int pin_enc_b;

    long encoderTime = 0;
    long encoderTimeLast = 0;
    int ticks = 0;
    bool encoderUpdate = false;
    int encoderDir = 0;
    int motorDir = 1;

    float speed;
public:
    void updateWheel();

    void drive(int dir, int vel);

    Wheel(int en, int in1, int in2, int enc_a, int enc_b);

};


char action;
bool moving = false;
bool obstacle = false;

Wheel leftwheel(EN1, IN1_1, IN1_2, ENC_1A, ENC_1B);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  Serial.println("Connected");

  pinMode(PIN_DEBUG_LED_1, OUTPUT);
  pinMode(PIN_DEBUG_LED_2, OUTPUT);
  pinMode(PIN_DEBUG_LED_3, OUTPUT);
  pinMode(PIN_DEBUG_LED_4, OUTPUT);
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
      leftwheel.drive(0,100);
    } else { //There is an obstacle
      digitalWrite(PIN_DEBUG_LED_3,HIGH);
      digitalWrite(PIN_DEBUG_LED_4,LOW);

      //STOP MOTORS OR SWERVE
      leftwheel.drive(1,100);
    }
  } else{ //IF NOT
    digitalWrite(PIN_DEBUG_LED_1,LOW);
    digitalWrite(PIN_DEBUG_LED_3,LOW);
    digitalWrite(PIN_DEBUG_LED_4,LOW);
    
    //Turn off motors
    leftwheel.drive(0,0);
  }
}


void Wheel::updateWheel(){
    encoderTimeLast = encoderTime;
    encoderTime = micros();
    encoderDir = (digitalRead(pin_enc_a) * 2) - 1;
    ticks += encoderDir;
    encoderUpdate = true;

    speed = encoderDir * 45. / ((encoderTime - encoderTimeLast) / 1000000.);
}

void Wheel::drive(int dir, int vel){
    if(dir){
      digitalWrite(pin_in1,HIGH);
      digitalWrite(pin_in2,LOW);
    }
    else{
      digitalWrite(pin_in1,HIGH);
      digitalWrite(pin_in2,LOW);
    }
    analogWrite(pin_en,vel);
}

Wheel::Wheel(int en, int in1, int in2, int enc_a, int enc_b){
    pin_en = en;
    pin_in1 = in1;
    pin_in2 = in2;
    pin_enc_a = enc_a;
    pin_enc_b = enc_b;

    pinMode(pin_en, OUTPUT);
    pinMode(pin_in1, OUTPUT);
    pinMode(pin_in2, OUTPUT);
    pinMode(pin_enc_a, INPUT);
    pinMode(pin_enc_b, INPUT);

    analogWrite(pin_en, 0);

    digitalWrite(pin_enc_b, LOW);
    encoderTime = micros();
    encoderTimeLast = encoderTime - 1000;

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
