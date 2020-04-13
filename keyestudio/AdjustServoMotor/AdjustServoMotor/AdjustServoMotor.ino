#include <Servo.h>
Servo myservo;
int homeSM = 100;      // home set the servo motor
void setup() {
  // put your setup code here, to run once:
  myservo.attach(9);    // Define servo motor output pin to D9 (PWM)
}

void loop() {
  // put your main code here, to run repeatedly:
  myservo.write(homeSM - 80);  // home set the servo motor
  delay(1000);
  myservo.write(homeSM);
  delay(1000);
  myservo.write(homeSM + 80);
  delay(1000);
//  myservo.write(90);
//  delay(1000);
}
