int pinLB = 12; // define pin 12
int pinLF = 3;  // define pin 3
int pinRB = 13; // define pin 13
int pinRF = 11; // define pin 11
int val;
void setup()
{
    Serial.begin(9600);     // define pin for motor output
    pinMode(pinLB, OUTPUT); // pin 12
    pinMode(pinLF, OUTPUT); // pin 3 (PWM)
    pinMode(pinRB, OUTPUT); // pin 13
    pinMode(pinRF, OUTPUT); // pin 11 (PWM)
}
void advance() // move forward
{
    digitalWrite(pinLB, LOW); // right wheel moves forward
    digitalWrite(pinRB, LOW); // left wheel moves forward
    analogWrite(pinLF, 255);
    analogWrite(pinRF, 255);
}
void stopp() // stop
{
    digitalWrite(pinLB, HIGH);
    digitalWrite(pinRB, HIGH);
    analogWrite(pinLF, 0);
    analogWrite(pinRF, 0);
}
void right() // turn right (single wheel)
{
    digitalWrite(pinLB, HIGH); // left wheel moves forward
    digitalWrite(pinRB, LOW);  // right wheel moves backward
    analogWrite(pinLF, 255);
    analogWrite(pinRF, 255);
}
void left() // turn left (single wheel)
{
    digitalWrite(pinLB, LOW);  // left wheel moves forward
    digitalWrite(pinRB, HIGH); // right wheel moves backward
    analogWrite(pinLF, 255);
    analogWrite(pinRF, 255);
}
void back() // move backward
{
    digitalWrite(pinLB, HIGH); // motor moves to left rear
    digitalWrite(pinRB, HIGH); // motor moves to right rear
    analogWrite(pinLF, 255);
    analogWrite(pinRF, 255);
}
void loop()
{
    val = Serial.read();
    if (val == 'U')
        advance();
    if (val == 'D')
        back();
    if (val == 'L')
        left();
    if (val == 'R')
        right();
    if (val == 'S')
        stopp();
}
