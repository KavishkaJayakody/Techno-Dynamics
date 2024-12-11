//config files to match our robot specificatiojns

#pragma once
#include "esp_system.h"



//*****************************communications******************************* */

const char* SSID = "SLT-4G_WataNandun";//"SLT-ADSL-92776";   // network credentials
const char* PASSWORD = "Nwata@#com";//"J1234567890";

const int LOCAL_PORT = 12345;  // UDP port to listen on

const char* REMOTE_IP = "192.168.1.131";//"192.168.1.3";
const int REMOTE_PORT = 12345;




//*****************************encoder pin allocation***********************
const int LeftEncoderPin1 = 15;
const int LeftEncoderPin2 = 4;

const int RightEncoderPin1 = 17;
const int RightEncoderPin2 = 16; 

//****************************motor********************************************* */
const int LEFT_MOTOR_PWM = 13;
const int LEFT_MOTOR_IN1 = 14;
const int LEFT_MOTOR_IN2 = 12;

const int RIGHT_MOTOR_PWM = 5;
const int RIGHT_MOTOR_IN1 = 18;
const int RIGHT_MOTOR_IN2 = 19;

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
const float ROBOT_RADIUS = 170;  //there is some error in this. Although it says radius put Wheel to wheel diameter
const float DEG_PER_MM_DIFFERENCE = 180.0/(ROBOT_RADIUS*3.14);

const float ARRAY_TO_WHEEL_DISTANCE = 65; //change this accordingly


const float RADIANS_PER_DEGREE = 0.0175;

const float ROT_KP = 0;//7;
const float ROT_KD = 0;//19;
const float ROT_KI = 0;
const float FWD_KP = 2.5;//6.0;//7.0//1.0
const float FWD_KD = 0;//10;
const float FWD_KI = 0;
const float STR_KP = 1.0;//2.2;//100;
const float STR_KD = 2.0;

//****************************************Robot*****************************************//
const float MOVE_SPEED = 100.0;
const float MOVE_ACC = 720; //1000
const float IMMEDIATE_ACC = 2000;

const float OMEGA_TURN = 120.0;
const float ALPHA_TURN = 1500.0;
const float LEFT = -87.0;
const float RIGHT = 87.0;



//*****************************************Sensors************************** */
const float STEERING_ADJUST_LIMIT = 100.0;
const int ERROR_POLARITY = 1;

const int NUM_SENSORS = 8;
const float SENSOR_THRESHOLD = 93.5;
const bool INVERT_COLOR = false;

const int BUTTON_PIN = 0;
const int LED_PIN = 2;

const int LEFT_LINE_PIN = 36;
const int RIGHT_LINE_PIN = 39;

//******************************************Arena Specs********************** */
const float LINE_LENGTH = 300.0;
const float LINE_WIDTH = 30.0;

//******************************************Mechanisms************************ */

const int LIFTING_SERVO_PIN = 27;
const int GRABBING_SERVO_PIN = 26;