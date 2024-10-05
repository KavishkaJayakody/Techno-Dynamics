#include <Arduino.h>
#include "motors.h"

// put function declarations here:
Motors motors;
Encoders encoders;

void setup() {
  motors.begin();
  encoders.begin();
  encoders.reset();
  Serial.begin(115200);
  //delay(20000);
  //pinMode(2, OUTPUT);
  //digitalWrite(2, HIGH);
  //delay(5000);
  //encoders.update();
  motors.set_right_motor_pwm(-250);
  motors.set_left_motor_pwm(0);
}

void loop() {
  encoders.update();
  Serial.println(encoders.rightRPS());
  delay(18);
}
