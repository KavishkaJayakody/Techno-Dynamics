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
#include "tasks.h"

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
Tasks tasks;
bool pressed=false;


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

  controlTicker.attach(0.005,[](){
      encoders.update();
      motion.update();
      motors.update(motion.velocity(), motion.omega(), sensors.get_steering_feedback());

  });

  sendTicker.attach(0.02, [](){

      // encoders.update();
      // motion.update();
      // motors.update(motion.velocity(), motion.omega(), sensors.get_steering_feedback());
      //communications.send("HI THERE");
      //communications.send("IRSENSORS",sensors.all_IR_readings, NUM_SENSORS+2);
      // communications.send_velocity();
      //communications.check(); 
      sensors.update();


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
  robot.move_straight(0.1);
  delay(1000);

  // robot.move_straight(500, 200);

  tasks.task1(); //  potato field pick
  // tasks.task2(); // muddy road with walls and ramp
  // tasks.task3(); // potato packing 
  // tasks.task4(); // potato box finding
  // // tasks.task5(); 
  // tasks.task6(); // water dry potatoes

  // int potatoJuncs = 0;
  // bool potatoFound = false;

  // robot.move_till_junction(1000); // Pass the first junction
  // robot.move_till_junction(1000); // Stop at second junction
  // robot.turn(RIGHT);

  // for (int i = 0; i < 3; i++) {
  //   robot.move_till_junction(1000); // Move until a junction is found
  // }
  // robot.turn(ABOUTTURN);
  // for (int i = 0; i < 3; i++) {
  //   robot.move_till_junction(1000); // Move until a junction is found
  // }
  // robot.turn(LEFT); // Turn 90 degrees clockwise
}