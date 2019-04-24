//connect motor controller pins to Arduino digital pins
// motor one
int enA = 10;
int in1 = 9;
int in2 = 8;

int encoder_in = 4;
// motor two  
//int enB = 5;
//int in3 = 7;
//int in4 = 6;

int power = 200;
long timeForSpeed = 0;
int ticks = 0;

void setup() {
  // put your setup code here, to run once:
 // set all the motor control pins to outputs
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(encoder_in, INPUT);
  timeForSpeed = micros();
//  digitalWrite(encoder_in, 0);
  //This is for motor two
  //pinMode(enB, OUTPUT);
  //pinMode(in3, OUTPUT);
  //pinMode(in4, OUTPUT);
  
}

void demoOne()
{
  // this function will run the motors in both directions at a fixed speed
  // turn on motor A
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, power);
  // turn on motor B
  //digitalWrite(in3, HIGH);
  //digitalWrite(in4, LOW);
  // set speed to 200 out of possible range 0~255
  //analogWrite(enB, 200);
  //delay(2000);
  // now change motor directions
  //digitalWrite(in1, LOW);
  //digitalWrite(in2, HIGH);  
  //digitalWrite(in3, LOW);
  //digitalWrite(in4, HIGH); 
  power = 255 - power;
  delay(2000);
  // now turn off motors
  //digitalWrite(in1, LOW);
  //digitalWrite(in2, LOW);  
  //digitalWrite(in3, LOW);
  //digitalWrite(in4, LOW);
}

bool encoder_last = false;

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(encoder_in) != encoder_last){
    ticks++;
    Serial.print("Encoder Moved  at ");
    encoder_last = !encoder_last;
    long current = micros();
    long microDifference = current - timeForSpeed;
    timeForSpeed = current;
    double measuredSpeed = 45. / (microDifference / 1000000.);
    Serial.print(measuredSpeed);
    Serial.print(" Degrees per second, ");
    Serial.print(ticks * 45);
    Serial.println(" Degrees Total ");
  }
  //demoOne();
}
