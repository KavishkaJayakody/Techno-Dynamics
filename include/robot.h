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

    bool barcode_finished = false;
    int inputArray[30] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int box_position;
    int last_scanned_pos = 0;

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
    void scan_barcode(){
        sensors.set_steering_mode(STEERING_OFF);
        motion.reset_drive_system();
        motion.start_move( MAX_BARCODE_LENGTH, MOVE_SPEED, 0, MOVE_ACC);
        while (!motion.move_finished())
        {   
            if (encoders.robotDistance()>=(250-165-15)){
                while(!barcode_finished){
                    if (29.5<(((int)encoders.robotDistance()-(250-165-15))%30)<30.5){
                        if (sensors.line_state == CROSS_OR_T){
                            inputArray[last_scanned_pos] = 1;

                        }
                        else if (sensors.line_state == NO_LINE){
                            inputArray[last_scanned_pos] = 0;

                        }
                        else if (sensors.line_state == LINE){
                            barcode_finished = true;
                            decode_barcode();
                            align_to_juction();
                        }
                        last_scanned_pos++;

                    }
                    delay(2);
                }
            }

            delayMicroseconds(2);
        }
        
    }
    void decode_barcode() {
        int inputIndex = 0;   // Index for traversing the input array.
        int outputIndex = 0;  // Index for storing the decoded values.
        byte decodedArray[15] = {0}; // Initialize decoded array.

        while (inputIndex < 30) {
            // Check if the current bit and the next bit form "11".
            if (inputArray[inputIndex] == 1 && inputArray[inputIndex + 1] == 1) {
                decodedArray[outputIndex] = 1; // Decode as 1.
                inputIndex += 2;               // Skip two bits.
            } else if (inputArray[inputIndex] == 1) {
                decodedArray[outputIndex] = 0; // Decode as 0.
                inputIndex += 1;               // Skip one bit.
            } else {
                inputIndex++;                  // Skip invalid or zero bits.
                continue;
            }

            outputIndex++; // Move to the next output position.
        }

        // Find the index of the last non-zero element in `decodedArray`.
        int decimalValue = 0;
        int effectiveLength = 0;
        for (int i = 14; i >= 0; i--) {
            if (decodedArray[i] != 0) {
                effectiveLength = i + 1;
                break;
            }
        }

        // Convert the truncated `decodedArray` into a decimal number.
        for (int i = 0; i < effectiveLength; i++) {
            decimalValue = (decimalValue << 1) | decodedArray[i];
        }

        // Calculate the box position.
        int box_position = decimalValue % 5;

        // Print the results.
        Serial.print("Decoded Decimal Value: ");
        Serial.println(decimalValue);
        Serial.print("Box Position: ");
        Serial.println(box_position);
    }


    void move_staright(float distance)
    {
        sensors.set_steering_mode(STEERING_OFF);
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