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
enum
{
    STEER_NORMAL,
    STEERING_OFF,
};
enum {
    LINE,
    LEFT_LINE,
    RIGHT_LINE,
    CROSS_OR_T,
    NO_LINE,
};
enum {
    RED,
    BLUE,
    BLACK,
    WHITE,
};

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
    bool sensor_on_line[NUM_SENSORS] = {false,false,false,false,false,false,false,false};
    bool black_surface = true;
    volatile int line_state;
    bool calibrated = false;
    int last_junction = 0;
    bool left_pin_state;
    bool right_pin_state;
    uint8_t g_steering_mode = STEER_NORMAL;

    void begin()
    {   
        Serial.println("ADC begining");
        begin_ADC();
        Serial.println("ADC began");
        pinMode(BUTTON_PIN, INPUT);
        attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleButtonPressISR, CHANGE);
        pinMode(LED_PIN, OUTPUT);
        pinMode(LEFT_LINE_PIN, INPUT);
        pinMode(RIGHT_LINE_PIN, INPUT);
    }

        float get_steering_feedback()
    {
        return m_steering_adjustment;
    };

    float get_cross_track_error()
    {
        return m_cross_track_error;
    };

    void update()
    {
        readSensors();
        if(calibrated){
            map_sensors();
        }

        left_pin_state = !digitalRead(LEFT_LINE_PIN);
        right_pin_state = !digitalRead(RIGHT_LINE_PIN);

        float error=0;
        if (g_steering_mode == STEER_NORMAL){
            error = line_error(black_surface);
        }
        m_cross_track_error = error;
        calculate_steering_adjustment();
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
        // Reading 4 channels from the first ADS1115 (0x48)    (The array is connected in reverse direction)
        adcValues[7] = ads1.readADC(0); // Channel 0
        adcValues[6] = ads1.readADC(1); // Channel 1
        adcValues[5] = ads1.readADC(2); // Channel 2
        adcValues[4] = ads1.readADC(3); // Channel 3

        // Reading 4 channels from the second ADS1115 (0x49)
        adcValues[3] = (ads2.readADC(1)+ads1.readADC(3))/2; // Channel 0
        adcValues[2] = ads2.readADC(1); // Channel 1
        adcValues[1] = ads2.readADC(2); // Channel 2
        adcValues[0] = ads2.readADC(3); // Channel 3




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
    static void handleButtonPressISR(){
        sensors.handleButtonPress();
    }
    void handleButtonPress(){
        button_pressed = true;
    }
    void reset_button(){  // Call this fuction whenever using the button functionality before calling any other button functions
        button_pressed = false;
    }
    bool is_button_pressed(){
        bool button_state;
        noInterrupts();
        button_state = button_pressed;
        interrupts();
        return button_state;
    }

    void led_indicator(bool state){
        if (state){
            digitalWrite(LED_PIN, HIGH);
        }
        else{
            digitalWrite(LED_PIN, LOW);
        }
    }
    void wait_till_button(){
        reset_button();
        while(not is_button_pressed()){
            led_indicator(1);
            delay(250);
            led_indicator(0);
            delay(250);

        }

    }

    float calculate_steering_adjustment()
    {
        // always calculate the adjustment for testing. It may not get used.
        float pTerm = STEERING_KP * m_cross_track_error;
        float dTerm = STEERING_KD * (m_cross_track_error - last_steering_error);
        float adjustment = (pTerm + dTerm) * encoders.loopTime_s();

        //Serial.print("   adjustment  ");
        //Serial.print(adjustment);

        adjustment = constrain(adjustment, -STEERING_ADJUST_LIMIT, STEERING_ADJUST_LIMIT);
        last_steering_error = m_cross_track_error;
        m_steering_adjustment = adjustment;
        return adjustment;
    }
        void set_steering_mode(uint8_t mode)
    {
        last_steering_error = m_cross_track_error;
        m_steering_adjustment = 0;
        g_steering_mode = mode;
    }

    void map_sensors(){



        // Map the raw ADC readings using the min and max values from calibration
        Serial.print(left_pin_state);
        for (int i = 0; i < NUM_SENSORS; i++)
        {
            adcValues[i] = map(adcValues[i], minValues[i], maxValues[i], 0, 100); // Mapping to a range of 0-100
            //Serial.print(i);
            //Serial.print(")  ");
            //Serial.print(adcValues[i]);
            //Serial.print("   ");

            if (!black_surface){ //detect white line in black background
                if (adcValues[i]>SENSOR_THRESHOLD){  //include a code to handle the inverting of colors here
                    sensor_on_line[i] = true; 
                }
                else{
                    sensor_on_line[i] = false;
                }
            }
            else {
                if (adcValues[i]<SENSOR_THRESHOLD){
                    sensor_on_line[i] = true;
                }
                else{
                    sensor_on_line[i] = false;
                }
            }
            Serial.print(sensor_on_line[i]);
        }
        Serial.print(right_pin_state);

        //line state detection
        left_state = true;
        right_state = true;
        no_line = true; 
        int on_line_count =0;
        for (int i = 0; i < NUM_SENSORS; i++)         //detect for a line
        {
            if (sensor_on_line[i]==true){
                no_line = false;
                on_line_count +=1;
            }
        }

        


                                      //Change this accordingly to avoid detecting the adacent colour lines
        for (int i = 0; i < NUM_SENSORS/4; i++)         //detect for a line in left side of the line
        {
            if (sensor_on_line[i]==false){
                left_state = false;
            }
        }
        for (int i = 3*NUM_SENSORS/4; i < NUM_SENSORS; i++)         //detect for a line in right side of the line
        {
            if (sensor_on_line[i]==false){
                right_state = false;
            }
        }


        if (no_line == true){
            line_state = NO_LINE;
            Serial.println("NO_LINE");
        }
        else if (left_state == true and right_state==true and on_line_count >= NUM_SENSORS/2 and left_pin_state==true and right_pin_state == true){
            line_state = CROSS_OR_T;
            //led_indicator(true);
            Serial.println("CROSS_OR_T");
        }
        else if (left_state == true and on_line_count>=((NUM_SENSORS/2)) and left_pin_state==true){
            line_state = LEFT_LINE;
            Serial.println("LEFT_LINE");
        }
        else if (right_state == true and on_line_count>=((NUM_SENSORS/2)) and right_pin_state == true){
            line_state = RIGHT_LINE;
            Serial.println("RIGHT_LINE");
        }
        else //if (left_state == false and right_state==false)
        {
           line_state = LINE;
           Serial.println("LINE");
        }

        
    }

    // Calibrate function to find minimum and maximum values for each sensor channel
    void calibrate()
    {   
        wait_till_button();
        led_indicator(1);
        Serial.println("Callibration Started");
        // Initialize min and max arrays
        for (int i = 0; i < NUM_SENSORS; i++)
        {
            minValues[i] = 32767;  // Start with a high value for minimum
            maxValues[i] = -32768; // Start with a low value for maximum
        }

        // Take multiple readings to find min and max
        int t = millis();
        while (millis() < t + 5000)
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
        Serial.println("Callibration Finished");
        wait_till_button();
        led_indicator(0);
    }

    // Function to compute the line error (position of the line)
    float line_error(bool black_background)
    {
        unsigned long weightedSum = 0;
        unsigned int totalValue = 0;

        for (int i = 0; i < NUM_SENSORS; i++)
        {
        float sensorValue = adcValues[i];

        // Adjust sensor interpretation based on the mode
        if (black_background) {
            // Invert the sensor value for white-on-black mode
            sensorValue = 100 - sensorValue;
        }
            weightedSum += (long)sensorValue * i * 1000;
            totalValue += sensorValue;
        }

        // Handle case where no line is detected
        if (totalValue == 0)
        {
            return 0.0; // Return center (3500) if no line detected
        }
        if (black_background) {
            // Invert the error value for white-on-black mode
            return (ERROR_POLARITY)*((weightedSum / totalValue)-3500.0)/100.0;//  error -35<error<35
        }
        else {
        return (ERROR_POLARITY)*((weightedSum / totalValue)-3500.0)/100.0;//  error -35<error<35
        }
    }
private:
    // variables for steering
    float last_steering_error = 0;
    volatile float m_cross_track_error;
    volatile float m_steering_adjustment;
    volatile bool button_pressed;
    bool left_state;
    bool right_state;
    bool no_line;
};
