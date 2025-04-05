/*last updated on 5/4/2025 8:45PM. function definitions (Yehen). declared and integrated (Nilakna)*/

#ifndef RASPI_H
#define RASPI_H

#include <Arduino.h>
#include <Wire.h>

// #define LED_BUILTIN 2 // Define the built-in LED pin for ESP32 (GPIO 2)

class Raspi;
extern Raspi raspi; // Declare the raspi object

class Raspi
{
public:
    Raspi(); // Constructor
    void takeRightPotato(); // Ask Raspberry Pi to take the potato
    bool isRedGood(); // read the april tag and return true if red is good, return false is blue is good
    int findBoxColour(); // find the box colout=r. return true if red, false if blue
    void openGate(int GOODORBAD); // Open the gate
    
    bool detectDryPot(); // Detect dry potato. return true if dry, false if wet
    void takeWater(); // Ask Raspberry Pi to take water
    void waterPot(); // Ask Raspberry Pi to water the potato
    void playStarman(); // Play Starman song

    void ledOn(); // Turn on the LED
    void ledOff(); // Turn off the LED

    // int boxColumnColors(bool goodRed); // Get the box colors of the column
    // int rightBoxColumnColors(bool goodRed); // turn camera to right and Get the box colors of the column
    void takeRightBox(); // Ask Raspberry Pi to take the box
    void takeFrontBox();
    void placeFrontBox(); // Ask Raspberry Pi to place the box
    void placeRightBox(); // Ask Raspberry Pi to place the box

    void waitForResponse(); // Wait for a response from the Raspberry Pi
    bool waitForBoolResponse(); // Wait for a boolean response from the Raspberry Pi
    int waitForIntResponse(); // Wait for an integer response from the Raspberry Pi
};

// #endif // RASPI_H

// #ifndef RASPI_H
// #define RASPI_H

// class raspi
// {
// public:
Raspi::Raspi()
    {
        Serial.begin(115200);
        while (!Serial)
        {
            delay(10); // Wait for serial connection
        }
        pinMode(LED_BUILTIN, OUTPUT);
        digitalWrite(LED_BUILTIN, LOW);
    }

void Raspi::takeRightPotato()
    {
        // potato at 785 height
        Serial.println("TAKE_POTATO");
        waitForResponse();
    }

void Raspi::takeRightBox()
    {
        // box top at 500 height
        Serial.println("TAKE_RIGHT_BOX");   
        waitForResponse();
        // return waitForBoolResponse();
    }

void Raspi::takeFrontBox()
    {
        // box top at 500 height
        Serial.println("TAKE_FRONT_BOX");   
        waitForResponse();
        // return waitForBoolResponse();
    }

void Raspi::placeRightBox()
    {
        // box top at 500 height
        Serial.println("PLACE_RIGHT_BOX");   
        waitForResponse();
        // return waitForBoolResponse();
    }

void Raspi::placeFrontBox()
    {
        // box top at 500 height
        Serial.println("PLACE_FRONT_BOX");   
        waitForResponse();
        // return waitForBoolResponse();
    }

bool Raspi::isRedGood()
    {
        Serial.println("IS_RED_GOOD");
        return waitForBoolResponse();
    }

int Raspi::findBoxColour()
    {
        Serial.println("FIND_BOX_COLOR");
        return waitForIntResponse();
    }

void Raspi::openGate(int goodOrBad)
    {
        // GOOD = 1, BAD = 0
        Serial.println("OPEN_GATE:" + String(goodOrBad));
        waitForResponse();
    }

bool Raspi::detectDryPot()
    {
        Serial.println("DETECT_DRY_POT");
        return waitForBoolResponse();
    }

void Raspi::takeWater()
    {
        Serial.println("TAKE_WATER");
        waitForResponse();
    }

void Raspi::waterPot()
    {
        Serial.println("WATER_POT");
        waitForResponse();
    }

void Raspi::playStarman()
    {
        Serial.println("PLAY_STARMAN");
        waitForResponse();
    }

void Raspi::ledOn()
    {
        Serial.println("LED_ON");
        digitalWrite(LED_BUILTIN, HIGH);
        waitForResponse();
    }

void Raspi::ledOff()
    {
        Serial.println("LED_OFF");
        digitalWrite(LED_BUILTIN, LOW);
        waitForResponse();
    }

// private:
void Raspi::waitForResponse()
    {
        unsigned long startTime = millis();
        while (millis() - startTime < 5000)
        { // 5 second timeout
            if (Serial.available())
            {
                String response = Serial.readStringUntil('\n');
                response.trim();
                if (response == "OK" || response.startsWith("RESULT:"))
                {
                    return;
                }
            }
        }
        Serial.println("ERROR: Timeout waiting for response");
    }

bool Raspi::waitForBoolResponse()
    {
        unsigned long startTime = millis();
        while (millis() - startTime < 10000)
        { // 5 second timeout
            if (Serial.available())
            {
                String response = Serial.readStringUntil('\n');
                response.trim();
                if (response.startsWith("RESULT:"))
                {
                    String result = response.substring(7);
                    return result == "true";
                }
            }
        }
        Serial.println("ERROR: Timeout waiting for bool response");
        return false;
    }


int Raspi::waitForIntResponse()
    {
        unsigned long startTime = millis();
        while (millis() - startTime < 10000)
        { // 5 second timeout
            if (Serial.available())
            {
                String response = Serial.readStringUntil('\n');
                response.trim();
                if (response.startsWith("RESULT:"))
                {
                    String result = response.substring(7);
                    return result.toInt();
                }
            }
        }
        Serial.println("ERROR: Timeout waiting for int response");
        return -1;
    }

#endif // RASPI_H