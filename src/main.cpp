#include <Arduino.h>
#include "motors.h"
#include "Ticker.h"
#include "motion.h"
#include "robot.h"
#include "profile.h"


// put function declarations here:
Motors motors;
Encoders encoders;
Ticker sendTicker;
Robot robot;
Motion motion;
Profile forward;
Profile rotation;


void setup() {
  motors.begin();
  encoders.begin();
  encoders.reset();
  Serial.begin(115200);
  sendTicker.attach(0.0185, [](){
      encoders.update();
      motion.update();
      motors.update(motion.velocity(), motion.omega(), 0);
      //Serial.println(encoders.robotAngle());

      });
  //delay(20000);
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  //delay(5000);
  //encoders.update();
  //motors.set_right_motor_pwm(0);
  //motors.set_left_motor_pwm(0);
  motors.enable_controllers();
  delay(1000);
  //motors.omega = 360;
  //motors.speed = 0;
}

void loop() {


  motion.reset_drive_system();
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
