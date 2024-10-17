//config files to match our robot specificatiojns

#pragma once
#include "esp_system.h"

//*****************************encoder pin allocation***********************
const int LeftEncoderPin1 = 16;
const int LeftEncoderPin2 = 17;

const int RightEncoderPin1 = 4;
const int RightEncoderPin2 = 15; 

//****************************motor********************************************* */
const int LEFT_MOTOR_PWM = 13;
const int LEFT_MOTOR_IN1 = 12;
const int LEFT_MOTOR_IN2 = 14;

const int RIGHT_MOTOR_PWM = 5;
const int RIGHT_MOTOR_IN1 = 19;
const int RIGHT_MOTOR_IN2 = 18;

const int PWM_RESOLUTION_BITS = 10;
const int PWM_RESOLUTION = 1023; //2^10-1

const int MAX_MOTOR_PERCENTAGE = 95;

const int MOTOR_RIGHT_POLARITY = 1;// change this to change direction of motor direction
const int MOTOR_LEFT_POLARITY = 1;

const int M_BALNCE_PWM = 0; //adjust this value to bring both the motors to same speed

const int MIN_MOTOR_PERCENTAGE = 5;
const int MIN_MOTOR_BIAS = 5;
const int maxMotorPercentage = 100;

//******************************robot dimensions*****************************/
const float MM_PER_ROTATION = 200;//tyre
const float PULSES_PER_ROTATION = 1300.0;
const float ROBOT_RADIUS = 180;  //there is some error in this. Although it says radius put Wheel to wheel diameter
const float DEG_PER_MM_DIFFERENCE = 180.0/(180.0*3.14);


const float RADIANS_PER_DEGREE = 0.0175;

const float rotKp = 5;
const float rotKd = 10;
const float rotKi = 0;
const float fwdKp = 1;
const float fwdKd = 10;
const float fwdKi = 0;
const float STEERING_KP = 6;//100;
const float STEERING_KD = 15;//100;

//****************************************Robot*****************************************//
const float MOVE_SPEED = 150.0;
const float MOVE_ACC = 1000;

const float OMEGA_TURN = 270.0;
const float ALPHA_TURN = 3600.0;

const float STEERING_ADJUST_LIMIT = 100.0;
const int ERROR_POLARITY = -1;

//*****************************************Sensors************************** */
const int NUM_SENSORS = 8;