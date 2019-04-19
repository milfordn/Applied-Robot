#include <L298N.h>

#define EN1 3
#define EN2 4
#define IN1_1 8
#define IN1_2 9
#define IN2_1 10
#define IN2_2 11

#define LED1 10
#define LED2 9
#define LED3 8
#define LED4 7

char action;


void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  Serial.println("Connected");

  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  action=0;

  if(Serial.available() > 0){
    action = Serial.read();
    //Serial.println(action);
  }

  switch(action){
    case '1':
      digitalWrite(LED1,HIGH);
      delay(500);
      off();
      
      break;
      
    case '2':
      digitalWrite(LED2,HIGH);
      delay(500);
      off();

      break;

    case '3':
      digitalWrite(LED3,HIGH);
      delay(500);
      off();
      
      break;
      
    case '4':
      digitalWrite(LED4,HIGH);
      delay(500);
      off();

      break;

    case 'd':
      ledbounce(10);

      break;
      
    case 's':
      ledline(10);

      break;

    case 'a':
      altflicker(5);

      break;
    
    case 'i':
      int integer = Serial.parseInt();
      Serial.println(integer);
  
      break;
  }
}

void ledline(int n){
  int d = 50;
  for(int i=0; i<n; i++){
    digitalWrite(LED1,HIGH);
    delay(d);
    digitalWrite(LED2,HIGH);
    delay(d);
    digitalWrite(LED3,HIGH);
    digitalWrite(LED1,LOW);
    delay(d);
    digitalWrite(LED4,HIGH);
    digitalWrite(LED2,LOW);
    delay(d);
    digitalWrite(LED3,LOW);
    delay(d);
    digitalWrite(LED4,LOW);
  }
}

void ledbounce(int n){
  int d = 50;
  for(int i=0; i<n; i++){
    digitalWrite(LED1,HIGH);
    delay(d);
    digitalWrite(LED2,HIGH);
    delay(d);
    digitalWrite(LED3,HIGH);
    digitalWrite(LED1,LOW);
    delay(d);
    digitalWrite(LED4,HIGH);
    digitalWrite(LED2,LOW);
    delay(d);
    digitalWrite(LED3,LOW);
    delay(d);
    
    digitalWrite(LED3,HIGH);
    delay(d);
    digitalWrite(LED2,HIGH);
    digitalWrite(LED4,LOW);
    delay(d);
    digitalWrite(LED1,HIGH);
    digitalWrite(LED3,LOW);
    delay(d);
    digitalWrite(LED2,LOW);
    delay(d);
    digitalWrite(LED1,LOW);
  }
}

void altflicker(int n){
  int d = 250;
  for(int i=0;i<n;i++){
    digitalWrite(LED2,LOW);
    digitalWrite(LED4,LOW);
    digitalWrite(LED1,HIGH);
    digitalWrite(LED3,HIGH);
    delay(d);

    digitalWrite(LED2,HIGH);
    digitalWrite(LED4,HIGH);
    digitalWrite(LED1,LOW);
    digitalWrite(LED3,LOW);
    delay(d);
    
  }
  off();
}

void off(){
  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);
  digitalWrite(LED3,LOW);
  digitalWrite(LED4,LOW);
}
