
byte counter = 0;

void setup(){
    Serial.begin(9600);
    pinMode(6, OUTPUT);
}

void loop(){
    analogWrite(6, 255 - counter);
    counter++;
    Serial.println(counter);
    delay(10);
}
