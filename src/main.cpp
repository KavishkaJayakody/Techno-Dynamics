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

  //sensors.calibrate();

  controlTicker.attach(0.005,[](){
      encoders.update();
      motion.update();
      motors.update(motion.velocity(), motion.omega(), sensors.get_steering_feedback());

  });

  sendTicker.attach(0.02, [](){
      
      communications.send("IRSENSORS",sensors.all_IR_readings, NUM_SENSORS+2);
      communications.send_velocity();
      communications.check(); 
      // sensors.update();
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

  // for (int i=0;i<1023;i=i+32){

  //   motors.set_left_motor_pwm((sqrt(i*2.5/1000)/0.65)*1000/2.5);
  //   motors.set_right_motor_pwm((pow(2.718,(4*2.5*i)/(3*1000))/25)*1000/2.5);
  //   delay(1000);
  //   Serial.print(i);
  //   Serial.print("left ");
  //   Serial.print(encoders.leftRPS());
  //   Serial.print("  right ");
  //   Serial.println(encoders.rightRPS());
  // }
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
  //mechanisms.lift();
  //mechanisms.lower();
  delay(1000);
  robot.move_staright(1000);
  while (true){
    //robot.move_staright(500);
    robot.turn(-90);
    motion.stop();
    delay(1000);

    robot.turn(-90);
    motion.stop();
    delay(1000);

        robot.turn(90);
    motion.stop();
    delay(1000);

    robot.turn(90);
    motion.stop();
    delay(1000);
  }
  robot.move(1000);


  //  while(true){
  //   robot.turn(77);
  //    delay(250);
  //  }
  Serial.print("  Moving    ");
  //robot.move(30000);

  // while (true){
  // robot.turn(-90);
  // delay(1000);
  // robot.turn(90);
  // delay(1000);
  // }

  while (true){
      robot.move_till_junction(30000);
      delay(250);
      if (sensors.last_junction == CROSS_OR_T){
        sensors.led_indicator(true);
        Serial.print("CROSS_OR_T");
        //robot.move(100);
        delay(250);//robot.turn(77);
      }
      else if (sensors.last_junction == RIGHT_LINE){
        Serial.print("RIGHT_LINE");
        robot.turn(RIGHT);
        delay(1000);
        //robot.move(50);
      }
      else if (sensors.last_junction == LEFT_LINE){
        Serial.print("LEFT_LINE");
        robot.turn(LEFT);
        delay(1000);
        //robot.move(50);
      }
      sensors.last_junction = LINE;
      delay(250);
      sensors.led_indicator(false);
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
