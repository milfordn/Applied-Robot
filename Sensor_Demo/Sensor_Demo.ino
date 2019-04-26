#include <FastGPIO.h>

//connect motor controller pins to Arduino digital pins
// motor one
const int enA = 10;
const int in1 = 9;
const int in2 = 8;

const int encoder1a = 2;
const int encoder1b = 6;
// motor two  
//int enB = 5;
//int in3 = 7;
//int in4 = 6;

int power = 200;
long encoderTime = 0;
long encoderTimeLast = 0;
int ticks = 0;
bool encoderUpdate = false;
int8_t dir = 0;

void setup() {
  // put your setup code here, to run once:
 // set all the motor control pins to outputs
  Serial.begin(9600);
  Serial.print("Starting!");
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(encoder1a, INPUT);
  pinMode(encoder1b, INPUT);
  digitalWrite(encoder1b, 0);
  attachInterrupt(digitalPinToInterrupt(encoder1a), updateMeasurements, CHANGE);
  encoderTime = micros();
  encoderTimeLast = encoderTime - 1000;
}

void updateMeasurements(){
  encoderTimeLast = encoderTime;
  encoderTime = micros();
  dir = (FastGPIO::Pin<encoder1b>::isInputHigh() << 1) - 1;
  ticks += dir;
  encoderUpdate = true;
}

void loop() {
  // put your main code here, to run repeatedly:
  if(encoderUpdate){
    encoderUpdate = false;
    Serial.print("Encoder Moved  at ");
    float measuredSpeed = dir * 45. / ((encoderTime - encoderTimeLast) / 1000000.);
    Serial.print(measuredSpeed);
    Serial.print(" Degrees per second, ");
    Serial.print(ticks * 45);
    Serial.println(" Degrees Total.");
  }
}
