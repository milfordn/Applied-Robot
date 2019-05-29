#define PIN 21

void setup(){
    pinMode(PIN, INPUT_PULLUP);
    digitalWrite(PIN, LOW);
    Serial.begin(115200);
}

void loop(){
    Serial.println(digitalRead(PIN));
    delay(250);
}

//RESULTS:
//Wire signal to NC, GND to COM, use INPUT_PULLUP
//1 is pressed, 0 is not pressed
