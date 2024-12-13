#include <Arduino.h>
#include "motors.h"
#include "Ticker.h"
#include "motion.h"
#include "robot.h"
#include "profile.h"
#include "sensors.h"
#include "Wire.h"
#include "communications.h"
#include "mechanisms.h"

// put function declarations here:
Motors motors;
Encoders encoders;
Ticker sendTicker;
Ticker controlTicker;
Robot robot;
Motion motion;
Profile forward;
Profile rotation;
Sensors sensors;
Communications communications;
Mechanisms mechanisms;


void setup() {
  motors.begin();
  encoders.begin();
  encoders.reset();
  Serial.begin(115200);
  Wire.begin();
  sensors.begin();
  communications.begin();
  mechanisms.begin();

  sensors.calibrate();

  // controlTicker.attach(0.005,[](){
  //     encoders.update();
  //     motion.update();
  //     motors.update(motion.velocity(), motion.omega(), sensors.get_steering_feedback());

  // });

  sendTicker.attach(0.02, [](){

      encoders.update();
      motion.update();
      motors.update(motion.velocity(), motion.omega(), sensors.get_steering_feedback());
      
      //communications.send("IRSENSORS",sensors.all_IR_readings, NUM_SENSORS+2);
      //communications.send_velocity();
      //communications.check(); 
      sensors.update();
      // Serial.print("color ");
      // Serial.print(sensors.getProminentColorinword());
      // Serial.print("  Bottom ToF ");
      // Serial.print(sensors.bottom_ToF_reading);
      // Serial.print(sensors.object_infront_bottom_ToF);
      // Serial.print(" Top ToF ");
      // Serial.print(sensors.bottom_ToF_reading);
      // Serial.print(sensors.object_infront_bottom_ToF);
      


      //Serial.print(sensors.get_steering_feedback());
      //Serial.print("  error ");
     // Serial.println(sensors.line_error());
      
      //Serial.print("Steering mode    ");
      //Serial.print(sensors.g_steering_mode);
      //Serial.print(" steering feedback   ");
      //Serial.print(sensors.get_steering_feedback());
      //Serial.print(" ");

      
      //Serial.println(encoders.robotAngle());

      });
  


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

  motion.reset_drive_system();
  robot.move_staright(0.1);
  delay(1000);
  while(1){
     robot.move_till_junction_and_turn();
     delay(1000);
  }
  robot.move_till_junction_and_turn();
  robot.scan_barcode();
  delay(1000);
  robot.move_till_junction_and_turn();
  robot.move_till_junction(3000);
  robot.turn(RIGHT);
  robot.move_till_junction(3000);
  robot.turn(LEFT);
  robot.move_till_junction(3000);
  robot.turn(RIGHT);
  robot.move_till_junction(3000);
  //robot.turn(LEFT);
  robot.move_till_junction(3000);
  robot.turn(RIGHT);
  while (1){}

  delay(5000);
  sensors.led_indicator(1);
  robot.scan_barcode();
  
  while (true){
    //robot.move_staright(500);
    robot.turn(-77);
    motion.stop();
    delay(1000);



    robot.turn(-77);
    motion.stop();
    //delay(1000);

    //robot.move_staright(500);
    //delay(1000);

    robot.turn(75);
    motion.stop();
    //delay(1000);

    robot.turn(75);
    motion.stop();
    //delay(1000);

    //robot.move_staright(500);
    //delay(1000);
  }
  Serial.print("  Moving    ");

  robot.move_till_junction(3000);
  robot.turn(RIGHT);
  robot.move_till_junction(3000);
  robot.turn(LEFT);
  robot.move_till_junction(3000);
  robot.turn(RIGHT);
  robot.move_till_junction(3000);
  robot.turn(LEFT);
  robot.move_till_junction(3000);
  robot.turn(RIGHT);
  while (1){}
  
  while (true){
    robot.move_till_junction_and_turn();
  }

  while (true){
      robot.move(300);
      delay(250);
      robot.move(-300);
      delay(250);
      robot.turn(-90);
      delay(250);
      }

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



}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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