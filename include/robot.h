#pragma once

#include <Arduino.h>
#include "encoders.h"
#include "config.h"
#include "motion.h"
#include "sensors.h"

class Robot;
extern Robot robot;

class Robot
{
public:
    void move(float distance)
    {
        sensors.set_steering_mode(STEER_NORMAL);
        motion.reset_drive_system();
        motion.start_move( distance, MOVE_SPEED, 0, MOVE_ACC);
        while (!motion.move_finished())
        {   
            // if (sensors.line_state == LINE){
            //     sensors.g_steering_mode = STEER_NORMAL;
            // }
            // else {
            //     sensors.g_steering_mode = STEERING_OFF;
            // }
            delayMicroseconds(2);

            //if (sensors.frontWallExist)
            //{
            //    stopAndAdjust();
            //    break;
            //}
        }
    }

    void move_till_junction(float distance)
    {   
        bool junction_detected = false;
        sensors.set_steering_mode(STEER_NORMAL);
        motion.reset_drive_system();
        motion.start_move( distance , MOVE_SPEED, 0, MOVE_ACC);
        while (!motion.move_finished())
        {   
            if (sensors.line_state == LINE){
                sensors.g_steering_mode = STEER_NORMAL;
            }
            else {
                sensors.g_steering_mode = STEERING_OFF;
            }
            
            if (sensors.line_state ==LEFT_LINE or sensors.line_state ==RIGHT_LINE){  //detect if the expected junction is reached
                junction_detected = true;
                delay(61);
                sensors.last_junction = sensors.line_state;
            }
            if (sensors.line_state == CROSS_OR_T){  //detect if the expected junction is reached
                junction_detected = true;
                sensors.last_junction = sensors.line_state;
            }
            if (junction_detected){//only allign to the junction if (expected junction distance reached and) junction passed.
                align_to_juction();
                break;
            }
            delayMicroseconds(2);

        }
    }
    void align_to_juction(){
        sensors.set_steering_mode(STEERING_OFF);
        motion.reset_drive_system();
        motion.start_move( ARRAY_TO_WHEEL_DISTANCE , encoders.robot_speed(), 0, MOVE_ACC);
        while (!motion.move_finished()){ 
            // if (sensors.line_state == LINE){
            //     sensors.g_steering_mode = STEER_NORMAL;
            // }
            // else {
            //     sensors.g_steering_mode = STEERING_OFF;
            // }
            delay(2);
          }

    }

    void turn_180()
    {
        sensors.set_steering_mode(STEERING_OFF);
        static int direction = 1;
        direction *= -1; // alternate direction each time it is called

        motion.reset_drive_system();

        motion.start_turn(direction * 180, OMEGA_TURN, 0, ALPHA_TURN);

        while (!motion.turn_finished())
        {
            delayMicroseconds(2);
        }
        delay(1);
    }
    void turn(float angle)
    {
        sensors.set_steering_mode(STEERING_OFF);
        motion.reset_drive_system();
        motion.start_turn(-angle, OMEGA_TURN, 0, ALPHA_TURN);

        while (!motion.turn_finished())
        {
            delayMicroseconds(2);
        }
    }

    // void maze(int barcode)
    // {
        
    //     if (barcode == 0)
    //     {
    //         //move forward until T junction release, turn right, pick,move forward

    //     }

    //     if (barcode == 1)
    //     {
    //         //turn left move fwd until 1st T junction turn left pick move fwd 1st T junc
    //     }
    // }
};