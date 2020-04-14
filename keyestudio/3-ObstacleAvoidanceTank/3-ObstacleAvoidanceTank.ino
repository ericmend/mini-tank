/*
    L = Left
    R = Right
    F = forward
    B = backward
*/
#include <Servo.h>
int pinLB = 12;       // define pin 12
int pinLF = 3;        // define pin 3
int pinRB = 13;       // define pin 13
int pinRF = 11;       // define pin 11
////////////////////////////////
int inputPin = 4;     // define pin for sensor echo
int outputPin = 5;    // define pin for sensor trig

int Fspeedd = 0;      // forward speed
int Rspeedd = 0;      // right speed
int Lspeedd = 0;      // left speed
int directionn = 0;   // forward=8 backward=2 left=4 right=6
Servo myservo;        // set myservo
int delay_time = 250; // settling time after steering servo motor moving B
int Fgo = 8;          // Move F
int Rgo = 6;          // move to the R
int Lgo = 4;          // move to the L
int Bgo = 2;          // move B
int homeSM = 100;     // home set the servo motor

void setup()
{
  Serial.begin(9600);          // Define motor output pin
  pinMode(pinLB, OUTPUT);      // pin 12
  pinMode(pinLF, OUTPUT);      // pin 3 (PWM)
  pinMode(pinRB, OUTPUT);      // pin 13
  pinMode(pinRF, OUTPUT);      // pin 11 (PWM)
  pinMode(inputPin, INPUT);    // define input pin for sensor
  pinMode(outputPin, OUTPUT);  // define output pin for sensor
  myservo.attach(9);           // Define servo motor output pin to D9 (PWM)
}

void advance()      // move forward
{
  digitalWrite(pinLB, LOW);   // right wheel moves forward
  digitalWrite(pinRB, LOW);   // left wheel moves forward
  analogWrite(pinLF, 255);
  analogWrite(pinRF, 255);
}

void stopp()        // stop
{
  digitalWrite(pinLB, HIGH);
  digitalWrite(pinRB, HIGH);
  analogWrite(pinLF, 0);
  analogWrite(pinRF, 0);
}

void right()        // turn right (single wheel)
{
  digitalWrite(pinLB, HIGH); // wheel on the left moves forward
  digitalWrite(pinRB, LOW);  // wheel on the right moves backward
  analogWrite(pinLF, 255);
  analogWrite(pinRF, 255);
}

void left()         // turn left (single wheel)
{
  digitalWrite(pinLB, LOW);  // wheel on the left moves backward
  digitalWrite(pinRB, HIGH); // wheel on the right moves forward
  analogWrite(pinLF, 255);
  analogWrite(pinRF, 255);
}

void back()         // move backward
{
  digitalWrite(pinLB, HIGH); // motor moves to left rear
  digitalWrite(pinRB, HIGH); // motor moves to right rear
  analogWrite(pinLF, 255);
  analogWrite(pinRF, 255);
}

void detection()    // measure 3 angles (20.100.180)
{
  ask_pin_F();              // read the distance ahead
  if (Fspeedd < 10)         // if distance ahead is <10cm
  {
    stopp();                // clear data
    delay(100);
    back();                 // move backward for 0.2S
    delay(200);
  }
  if (Fspeedd < 25)         // if distance ahead is <25cm
  {
    stopp();
    delay(100);             // clear data
    ask_pin_L();            // read distance on the left
    delay(delay_time);      // stabilizing time for servo motor
    ask_pin_R();            // read distance on the right
    delay(delay_time);      // stabilizing time for servo motor

    if (Lspeedd > Rspeedd)                   // if distance on the left is >distance on the right
    {
      directionn = Lgo;                      // move to the L
    }
    else if (Lspeedd <= Rspeedd)             // if distance on the left is <= distance on the right
    {
      directionn = Rgo;                      // move to the right
    }

    if (Lspeedd < 10 && Rspeedd < 10)        // if distance on left and right are both <10cm
    {
      directionn = Bgo;                      // move backward
    }
  }
  else                                       // if distance ahead is >25cm
  {
    directionn = Fgo;                        // move forward
  }
}

void ask_pin_F()    // measure the distance ahead
{
  myservo.write(homeSM);
  digitalWrite(outputPin, LOW);               // ultrasonic sensor transmit low level signal 2μs
  delayMicroseconds(2);
  digitalWrite(outputPin, HIGH);              // ultrasonic sensor transmit high level signal10μs, at least 10μs
  delayMicroseconds(10);
  digitalWrite(outputPin, LOW);               // keep transmitting low level signal
  float Fdistance = pulseIn(inputPin, HIGH);  // read the time in between
  Fdistance = Fdistance / 5.8 / 10;           // convert time into distance (unit: cm)
  Fspeedd = Fdistance;                        // read the distance into Fspeedd
  Serial.println("Fspeedd: " + String(Fspeedd));
}

void ask_pin_L()    // measure distance on the left
{
  myservo.write(homeSM - 80);
  delay(delay_time);
  digitalWrite(outputPin, LOW);               // ultrasonic sensor transmit low level signal 2μs
  delayMicroseconds(2);
  digitalWrite(outputPin, HIGH);              // ultrasonic sensor transmit high level signal10μs, at least 10μs
  delayMicroseconds(10);
  digitalWrite(outputPin, LOW);               // keep transmitting low level signal
  float Ldistance = pulseIn(inputPin, HIGH);  // read the time in between
  Ldistance = Ldistance / 5.8 / 10;           // convert time into distance (unit: cm)
  Lspeedd = Ldistance;                        // read the distance into Lspeedd
  Serial.println("Lspeedd: " + String(Lspeedd));
}

void ask_pin_R()    //  measure distance on the right
{
  myservo.write(homeSM + 80);
  delay(delay_time);
  digitalWrite(outputPin, LOW);               // ultrasonic sensor transmit low level signal 2μs
  delayMicroseconds(2);
  digitalWrite(outputPin, HIGH);              // ultrasonic sensor transmit high level signal10μs, at least 10μs
  delayMicroseconds(10);
  digitalWrite(outputPin, LOW);               // keep transmitting low level signal
  float Rdistance = pulseIn(inputPin, HIGH);  // read the time in between
  Rdistance = Rdistance / 5.8 / 10;           // convert time into distance (unit: cm)
  Rspeedd = Rdistance;                        // read the distance into Rspeedd
  Serial.println("Rspeedd: " + String(Rspeedd));
}

void loop()
{
  myservo.write(homeSM);  // home set the servo motor, ready for next measurement
  detection();            // measure the angle and determine which direction to move
  if (directionn == Bgo)  // if directionn= 2
  {
    Serial.println("Backward");
    back();
    delay(800);           //  go backward
    left();
    delay(200);           // Move slightly to the left (to prevent stuck in dead end)
  }
  if (directionn == Rgo)  // if directionn = 6
  {
    Serial.println("Right");
    back();
    delay(100);
    right();
    delay(600);           // turn right
  }
  if (directionn == Lgo)  // if directionn = 4
  {
    Serial.println("Left");
    back();
    delay(100);
    left();
    delay(600);           // turn left
  }
  if (directionn == Fgo)  // if directionn = 8
  {
    Serial.println("Forward");
    advance();            // move forward
    delay(100);
  }
}
