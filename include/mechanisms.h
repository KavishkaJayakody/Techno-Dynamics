#pragma once
#include <ESP32Servo.h>
#include "config.h"
#include  "Arduino.h"

class Mechanisms;
extern Mechanisms mechanisms;

class Mechanisms
{
public:
        Servo lifting_servo;
        Servo grabbing_servo;
void begin()
{
        lifting_servo.attach(LIFTING_SERVO_PIN);
        grabbing_servo.attach(GRABBING_SERVO_PIN);
}
void lift(){
    for (int pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    lifting_servo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
}
void lower(){
    for (int pos = 180; pos >=0; pos -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    lifting_servo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
}
void grab(){
      for (int pos = 180; pos >=0; pos -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    lifting_servo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
}
void release(){
      for (int pos = 180; pos >=0; pos -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    lifting_servo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
}
};