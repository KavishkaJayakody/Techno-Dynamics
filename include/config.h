//config files to match our robot specificatiojns

#pragma once
#include "esp_system.h"

//*****************************encoder pin allocation***********************
const int LeftEncoderPin1 = 17;
const int LeftEncoderPin2 = 16;

const int RightEncoderPin1 = 4;
const int RightEncoderPin2 = 15; 

//****************************motor********************************************* */
const int LEFT_MOTOR_PWM = 25;
const int LEFT_MOTOR_IN1 = 26;
const int LEFT_MOTOR_IN2 = 27;

const int RIGHT_MOTOR_PWM = 5;
const int RIGHT_MOTOR_IN1 = 19;
const int RIGHT_MOTOR_IN2 = 18;

const int PWM_RESOLUTION_BITS = 8;
const int PWM_RESOLUTION = 255; //2^8-1

const int MAX_MOTOR_PERCENTAGE = 90;

const int MOTOR_RIGHT_POLARITY = 1;// change this to change direction of motor direction
const int MOTOR_LEFT_POLARITY = 1;

const int M_BALNCE_PWM = 0; //adjust this value to bring both the motors to same speed


//******************************robot dimensions*****************************/
const float MM_PER_ROTATION = 200;
const float PULSES_PER_ROTATION = 1300.0;
const float DEG_PER_MM_DIFFERENCE = 10;