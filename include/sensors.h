#pragma once

#include <Arduino.h>
#include <config.h>
#include <Wire.h>

class Sensors;

extern Sensors sensors;

enum
{
    STEER_NORMAL,
    STEERING_OFF,
};

class Sensors
{
public:
};