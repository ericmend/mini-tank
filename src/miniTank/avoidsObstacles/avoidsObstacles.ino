//  THIS CODE AVOIDS OBSTACLES
//  IT CAN EITHER ENCOUNTER AN OBSTACLE ON THE RIGHT OR THE LEFT SIDE
//  THEREFORE, WE PROGRAMMED IT TO TURN TO THE LEFT IF IT ENCOUNTERED AN OBSTACLE ON THE RIGHT
//  AND RIGHT IF WE ENCOUNTERED IT ON THE LEFT

//  @author: Pranav

/*
  UltraSonic 1
  Pin 5 Triggers the Pulse (Yellow lead)
  Pin 6 Recieves the Echo  (Orange lead)

  UltraSonic 2
  Pin 7 Triggers the Pulse (Yellow lead)
  Pin 8 Recieves the Echo  (Orange lead)
*/

#include "Servo.h"

Servo motorR;
Servo motorL;
Servo motorS;

// ultrasonic pins
// ultrasonic Right
const int Trig1_pin = 5; // pin for triggering pulse    INPUT
const int Echo1_pin = 6; // pin for recieving echo      OUPUT
long duration1;          // how long it takes for the sound to rebound

// ultrasonic Left
const int Trig2_pin = 7;
const int Echo2_pin = 8;
long duration2;

// motor pins
const int MotorLPin = 2;  // Left
const int MotorRPin = 13; // Right

// spinning ultrasonic motor
const int MotorSpinPin = 3;
int spinCounter = 0;

// sensing or not
boolean isARightWallThere = false;
boolean isALeftWallThere = false;

// which way to turn
boolean Right = true;

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting");
  // ultrasonic 1
  pinMode(Trig1_pin, OUTPUT); // initialize the pulse pin as output:
  pinMode(Echo1_pin, INPUT);  // initialize the echo_pin pin as an input:
  //ultrasonic 2
  pinMode(Trig2_pin, OUTPUT); // initialize the pulse pin as output:
  pinMode(Echo2_pin, INPUT);  // initialize the echo_pin pin as an input:
  // motors
  motorR.attach(MotorRPin);
  motorL.attach(MotorLPin);
  motorS.attach(MotorSpinPin);
}

void loop()
{
  while (1 == 1)
  {

    if (spinCounter < 2)
    {
      motorS.write(160);
    }
    else
    {
      motorS.write(20);
    }
    if (spinCounter >= 3)
    {
      spinCounter = 0;
    }

    spinCounter++;

    checkTheRightWall();
    checkTheLeftWall();

    if (isARightWallThere == false && isALeftWallThere == false)
    {
      motorR.write(120);
      motorL.write(72);
    }
    else
    {

      if (isARightWallThere == true && isALeftWallThere == true)
      {

        motorR.write(0);
        motorL.write(180);
        delay(300);
        motorR.write(80);
        motorL.write(80);
        delay(500);
        motorR.write(0);
        motorL.write(180);
      }

      else
      {
        if (isARightWallThere == false && isALeftWallThere == true)
        {

          motorR.write(50);
          motorL.write(90);
        }
        else
        {
          if (isARightWallThere == true && isALeftWallThere == false)
          {

            motorR.write(90);
            motorL.write(140);
          }
        }
      }
    }
  }
}

void checkTheRightWall()
{
  digitalWrite(Trig1_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig1_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig1_pin, LOW);
  duration1 = pulseIn(Echo1_pin, 10);
  Serial.println("Duration1:  ");
  Serial.println(duration1, DEC);

  if ((duration1 > 4000 || duration1 == 0))
  {
    isARightWallThere = false;
  }
  else
  {
    isARightWallThere = true;
  }
}

void checkTheLeftWall()
{
  digitalWrite(Trig2_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig2_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig2_pin, LOW);
  duration2 = pulseIn(Echo2_pin, 10);
  Serial.println("Duration2:  ");
  Serial.println(duration2, DEC);

  if ((duration2 > 4000 || duration2 == 0))
  {
    isALeftWallThere = false;
  }
  else
  {
    isALeftWallThere = true;
  }
}
