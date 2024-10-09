//config files to match our robot specificatiojns

#pragma once
#include "esp_system.h"

//*****************************encoder pin allocation***********************
const int LeftEncoderPin1 = 16;
const int LeftEncoderPin2 = 17;

const int RightEncoderPin1 = 4;
const int RightEncoderPin2 = 15; 

//****************************motor********************************************* */
const int LEFT_MOTOR_PWM = 25;
const int LEFT_MOTOR_IN1 = 26;
const int LEFT_MOTOR_IN2 = 27;

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
const float MM_PER_ROTATION = 200;
const float PULSES_PER_ROTATION = 1300.0;
const float DEG_PER_MM_DIFFERENCE = 0.273;

const float ROBOT_RADIUS = 210;
const float RADIANS_PER_DEGREE = 0.0175;

const float rotKp = 150;
const float rotKd = 0;
const float rotKi = 500;
const float fwdKp = 25;
const float fwdKd = 25;
const float fwdKi = 1;