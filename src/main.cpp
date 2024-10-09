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
  encoders.update();
  motors.set_right_motor_pwm(0);
  motors.set_left_motor_pwm(0);
  motors.enable_controllers();
}

void loop() {
  encoders.update();
  motors.update(0.0, 360.0, 0.0);
  //motors.set_right_motor_pwm(motors.right_feed_forward_percentage(60.0)*1023/100);
  Serial.print("Speed ");
  Serial.print(encoders.robot_speed());
  Serial.print("  omega  ");
  Serial.println(encoders.robot_omega());

   
   //Serial.println("h");
   delay(18);
}
