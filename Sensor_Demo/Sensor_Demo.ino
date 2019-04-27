//#include <FastGPIO.h>

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
int8_t encoderDir = 0;
int motorDir = 1;

void setup() {
  // put your setup code here, to run once:
 // set all the motor control pins to outputs
  Serial.begin(9600);
  Serial.println("Starting!");
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(encoder1a, INPUT);
  pinMode(encoder1b, INPUT);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(encoder1b, LOW);
  analogWrite(enA, 90);
  attachInterrupt(digitalPinToInterrupt(encoder1a), updateMeasurements, CHANGE);
  encoderTime = micros();
  encoderTimeLast = encoderTime - 1000;
}

void updateMeasurements(){
  encoderTimeLast = encoderTime;
  encoderTime = micros();
  encoderDir = (digitalRead(encoder1b) * 2) - 1;
  ticks += encoderDir;
  encoderUpdate = true;
  if(ticks < -32){
    analogWrite(enA, 0);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }
//  if(ticks < -16){
//    digitalWrite(in1, LOW);
//    digitalWrite(in2, HIGH);
//    ticks = 0;
//  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if(encoderUpdate){
    encoderUpdate = false;
    Serial.print("Encoder Moved  at ");
    float measuredSpeed = encoderDir * 45. / ((encoderTime - encoderTimeLast) / 1000000.);
    Serial.print(measuredSpeed);
    Serial.print(" Degrees per second, ");
    Serial.print(ticks * 45);
    Serial.println(" Degrees Total.");
  }
}
