//config files to match our robot specificatiojns

#pragma once
#include "esp_system.h"

//*****************************encoder pin allocation***********************
const int LeftEncoderPin1 = 33;
const int LeftEncoderPin2 = 32;

const int RightEncoderPin1 = 35;
const int RightEncoderPin2 = 34; 




//******************************robot dimensions*****************************/
const float MM_PER_ROTATION = 1;
const float PULSES_PER_ROTATION = 200;
const float DEG_PER_MM_DIFFERENCE = 10;