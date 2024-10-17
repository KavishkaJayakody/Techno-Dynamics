#include <Arduino.h>
#include "motors.h"
#include "Ticker.h"
#include "motion.h"
#include "robot.h"
#include "profile.h"
#include "sensors.h"
#include "Wire.h"


// put function declarations here:
Motors motors;
Encoders encoders;
Ticker sendTicker;
Robot robot;
Motion motion;
Profile forward;
Profile rotation;
Sensors sensors;


void setup() {
  motors.begin();
  encoders.begin();
  encoders.reset();
  Serial.begin(115200);
  Wire.begin();
  sensors.begin();
  sensors.calibrate();

  sendTicker.attach(0.02, [](){
      encoders.update();
      motion.update();
      Serial.print(sensors.get_steering_feedback());
      Serial.print("  error ");
      Serial.println(sensors.line_error());
      sensors.update();
      motors.update(motion.velocity(), motion.omega(), sensors.get_steering_feedback());
      //Serial.println(encoders.robotAngle());

      });
  

  delay(2000);
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  //delay(5000);
  //encoders.update();
  //motors.set_right_motor_pwm(500);
  //motors.set_left_motor_pwm(500);
  // delay(1000);
  motors.enable_controllers();
 
  motors.omega = 0;
  motors.speed = 0;
}

void loop() {
//   sensors.set_steering_mode(STEER_NORMAL);
//   delay(5000);
//   motors.stop();
//   delay(1000);
//  for (int i=0;i<10; i++){
//   motors.speed =20*i;
//   delay(100);
//  }
//  while (true){
//   motors.reset_controllers();
//   delay(100);
//  }




  motion.reset_drive_system();
  robot.move(30000);
  delay(250);
  robot.move(-300);
  delay(250);

  robot.turn(90);
  delay(250);
  robot.move(300);
  delay(250);
  robot.turn(-90);
  delay(250);
  robot.move(300);
  delay(250);
  robot.move(-300);
  delay(250);

  robot.turn(90);
  delay(250);
  robot.move(300);
  delay(250);
  robot.turn(-90);
  delay(250);
  robot.move(300);
  delay(250);
  robot.move(-300);
  delay(250);
  robot.turn(-90);
  delay(250);
  robot.move(600);
  delay(250);
  robot.turn(90);
  delay(250);


  
  // while (true){
  //   Serial.println(encoders.robotAngle());
  // }
  //encoders.update();
  //motors.update(0.0, 360.0, 0.0);
  //motors.set_right_motor_pwm(motors.right_feed_forward_percentage(60.0)*1023/100);
  // Serial.print("Speed ");
  // Serial.print(encoders.robot_speed());
  // Serial.print("  omega  ");
  // Serial.println(encoders.robot_omega());


  // float distance = encoders.robotDistance();
  // float travel = 1000;
  // while (encoders.robotDistance()<distance+travel){
  //     if (motors.speed<360){
  //         motors.speed ++;
  //     }
  //     delay(2);
  // }

  // float angle = encoders.robotAngle();
  // float sweep = 180;
  // while (encoders.robotAngle()<angle+sweep){
  //     if (motors.omega<115){
  //         motors.omega ++;
  //     }
  //     delay(2);
  // }
  // while (motors.omega>5){
  //     motors.omega --;
  //     delay(2);
  // }


  //motors.omega = 0;

  //delay(1000);

   
   //Serial.println("h");
  //delay(18);
}
