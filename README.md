# mini-tank

This is a respository of files and tips for the Keyestudio Tank Robot
<https://wiki.keyestudio.com/index.php/Ks0071_keyestudio_Mini_Tank_Robot>

Tip 1: Remove the Bluetooth module before uploading a sketch. The bluetooth module has priority on comms and will prevent the upload when installed.

Tip 2: Wiring for the motors is specific: Looking from the rear of the robot, the motors should be wired with the left motor then the right motor. The wires should be red, black, black, red.

Tip 3: The servo motor supplied is probably not centered. Test it before mounting.

Tip 4: The 18650 batteries are not easy to remove or install. Charge them before assembly so you get some use before having to remove them for charging. Use a small cable tie to gather up the loose wires at the back. This will prevent the wires from being caught in the treads and will help when removing and installing the batteries.

Tip 5: The assembly instructions show a AA battery pack directly wired to the motor board. The battery pack is not included and is not necessary. The motor board can be powered directly from the Arduino board using the 18650 battery pack. The supplied pack has the correct barrel adaptor to plug into the Arduino UNO.

---

## Introduction

Mini tank robot is a is a learning application development system of microcontroller based on MCU. It has functions such as ultrasonic obstacle avoidance, Bluetooth remote control.
<https://www.keyestudio.com/keyestudio-diy-mini-tank-smart-robot-car-kit-for-arduino-robot-education-programmingmanualpdfonline5-projects-p0392-p0392.html>

## Component list

keyestudio UNO R3 Controller * 1  
keyestudio L298P Shield  * 1  
keyestudio V5 Sensor Shield * 1  
HC-SR04 Ultrasonic Sensor * 1  
keyestudio Bluetooth Module (HC-06) * 1  
Servo Motor (black) * 1  
Tank Driver Wheel * 2  
18650 2-cell Battery Case * 1

tks @aleelatey  
<https://github.com/aleelatey/Arduino-Tank-2>
