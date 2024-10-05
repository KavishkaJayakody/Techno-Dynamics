#include <Arduino.h>
#include "config.h"
#include "encoders.h"


class Motors;
// testng
extern Motors motors;

class Motors
{  
public:
    void begin()
  {
    pinMode(LEFT_MOTOR_PWM, OUTPUT);
    pinMode(LEFT_MOTOR_IN1, OUTPUT);
    pinMode(LEFT_MOTOR_IN2, OUTPUT);
    pinMode(RIGHT_MOTOR_IN2, OUTPUT);
    pinMode(RIGHT_MOTOR_IN1, OUTPUT);
    pinMode(RIGHT_MOTOR_PWM, OUTPUT);

    digitalWrite(LEFT_MOTOR_PWM, 0);
    digitalWrite(LEFT_MOTOR_IN1, 0);
    digitalWrite(LEFT_MOTOR_IN2, 0);
    digitalWrite(RIGHT_MOTOR_IN2, 0);
    digitalWrite(RIGHT_MOTOR_IN1, 0);
    digitalWrite(RIGHT_MOTOR_PWM, 0);
    setupPWM();
  }
    void set_left_motor_pwm(int pwm)
  {
    pwm = MOTOR_LEFT_POLARITY * pwm;
    if (pwm < 0)
    {
      pwm = -pwm + M_BALNCE_PWM;
      digitalWrite(LEFT_MOTOR_IN1, HIGH);
      digitalWrite(LEFT_MOTOR_IN2, LOW);
      ledcWrite(2, pwm);
    }
    else
    {
      pwm = pwm + M_BALNCE_PWM;
      digitalWrite(LEFT_MOTOR_IN1, LOW);
      digitalWrite(LEFT_MOTOR_IN2, HIGH);
      ledcWrite(2, pwm);
    }
  }
    void set_right_motor_pwm(int pwm)
  {
    pwm = MOTOR_RIGHT_POLARITY * pwm;
    if (pwm < 0)
    {
      pwm = -pwm - M_BALNCE_PWM;
      digitalWrite(RIGHT_MOTOR_IN1, HIGH);
      digitalWrite(RIGHT_MOTOR_IN2, LOW);
      ledcWrite(1, pwm);
    }
    else
    {
      pwm = pwm - M_BALNCE_PWM;
      digitalWrite(RIGHT_MOTOR_IN1, LOW);
      digitalWrite(RIGHT_MOTOR_IN2, HIGH);
      ledcWrite(1, pwm);
    }
  }

    int calculate_pwm(float desired_percentage)
  {
    int pwm = MAX_MOTOR_PERCENTAGE * PWM_RESOLUTION * desired_percentage / 10000;
    return pwm;
  }

    void setupPWM()
  {
    ledcSetup(2, 5000, PWM_RESOLUTION_BITS);
    ledcAttachPin(LEFT_MOTOR_PWM, 2);
    ledcSetup(1, 5000, PWM_RESOLUTION_BITS);
    ledcAttachPin(RIGHT_MOTOR_PWM, 1);
  }

};