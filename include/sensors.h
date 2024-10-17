#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <ADS1X15.h> // Include the ADS1X15 library
#include "config.h"
ADS1115 ads1(0x48);
ADS1115 ads2(0x49);

class Sensors;

extern Sensors sensors;


// Enum for different steering states
// enum
// {
//     STEER_NORMAL,
//     STEERING_OFF,
// };

class Sensors
{
public:
    // ADS1115 objects for reading ADC values
    // ADS1115 ads1;
    // ADS1115 ads2;
    volatile int16_t adcValues[NUM_SENSORS]={0,0,0,0,0,0,0,0}; // To store ADC readings
    int16_t minValues[NUM_SENSORS];          // To store minimum values
    int16_t maxValues[NUM_SENSORS];          // To store maximum values
    int16_t mappedValues[NUM_SENSORS];       // To store mapped ADC values
    bool calibrated = false;

    void begin()
    {   
        Serial.println("ADC begining");
        begin_ADC();
        Serial.println("ADC began");
    }

    void update()
    {
        readSensors();
        //Serial.println(adcValues[0]);
    }

    // Initialize the ADS1115 sensors
    void begin_ADC()
    {   
        Serial.println("ADC starting");
        // Initialize the first ADS1115 with I2C address 0x48
        ads1.begin();

        ads1.setGain(0);
    

        // Initialize the second ADS1115 with I2C address 0x49
        ads2.begin();
        ads2.setGain(0);

        // Set the data rate for faster conversions (use the correct constant from the library)
        ads1.setDataRate(7); // Set to 1600 SPS (samples per second)
        ads2.setDataRate(7); // Set to 1600 SPS (samples per second)
    }

    // Function to read values from all ADS1115 channels
    void readSensors()
    {
        // Reading 4 channels from the first ADS1115 (0x48)
        adcValues[0] = ads1.readADC(0); // Channel 0
        adcValues[1] = ads1.readADC(1); // Channel 1
        adcValues[2] = ads1.readADC(2); // Channel 2
        adcValues[3] = ads1.readADC(3); // Channel 3

        // Reading 4 channels from the second ADS1115 (0x49)
        adcValues[4] = ads2.readADC(0); // Channel 0
        adcValues[5] = ads2.readADC(1); // Channel 1
        adcValues[6] = ads2.readADC(2); // Channel 2
        adcValues[7] = ads2.readADC(3); // Channel 3

        if(calibrated){
            map_sensors();
        }

        
        // Serial.print("  A0  ");
        // Serial.print(adcValues[0]);
        // Serial.print("  A1  ");
        // Serial.print(adcValues[1]);
        // Serial.print("  A2  ");
        // Serial.print(adcValues[2]);
        // Serial.print("  A3  ");
        // Serial.print(adcValues[3]);
        // Serial.print("  A4  ");
        // Serial.print(adcValues[4]);
        // Serial.print("  A5  ");
        // Serial.print(adcValues[5]);
        // Serial.print("  A6  ");
        // Serial.print(adcValues[6]);
        // Serial.print("  A7  ");
        // Serial.println(adcValues[7]);
        
    }

    void map_sensors(){

        // Map the raw ADC readings using the min and max values from calibration
        for (int i = 0; i < NUM_SENSORS; i++)
        {
            adcValues[i] = map(adcValues[i], minValues[i], maxValues[i], 0, 10); // Mapping to a range of 0-100
        }
    }

    // Calibrate function to find minimum and maximum values for each sensor channel
    void calibrate()
    {
        // Initialize min and max arrays
        for (int i = 0; i < NUM_SENSORS; i++)
        {
            minValues[i] = 32767;  // Start with a high value for minimum
            maxValues[i] = -32768; // Start with a low value for maximum
        }

        // Take multiple readings to find min and max
        int t = millis();
        while (millis() < t + 10000)
        {
            readSensors(); // Read current values

            // Check and update min/max values for each channel
            for (int i = 0; i < NUM_SENSORS; i++)
            {
                noInterrupts();
                if (adcValues[i] < minValues[i])
                    minValues[i] = adcValues[i]; // Update min value
                if (adcValues[i] > maxValues[i])
                    maxValues[i] = adcValues[i]; // Update max value
                interrupts();
            }
            delay(15);
        }
        calibrated = true;
    }

    // Function to compute the line error (position of the line)
    float line_error()
    {
        unsigned long weightedSum = 0;
        unsigned int totalValue = 0;

        for (int i = 0; i < NUM_SENSORS; i++)
        {
            weightedSum += (long)adcValues[i] * i * 1000;
            totalValue += adcValues[i];
        }

        // Handle case where no line is detected
        if (totalValue == 0)
        {
            return (NUM_SENSORS - 1) * 1000 / 2; // Return center (3500) if no line detected
        }

        return weightedSum / totalValue;
    }
};
