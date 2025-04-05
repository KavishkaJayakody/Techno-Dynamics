/*last updated on 5/4/2025 8:45PM. function definitions (Yehen). declared and integrated (Nilakna)*/

#ifndef RASPI_H
#define RASPI_H

#include <Arduino.h>
#include <Wire.h>

#define LED_BUILTIN 2 // Define the built-in LED pin for ESP32 (GPIO 2)

class Raspi;
extern Raspi raspi; // Declare the raspi object

class Raspi
{
public:
    Raspi(); // Constructor
    void takeRightPotato(); // Ask Raspberry Pi to take the potato
    bool isRedGood(); // read the april tag and return true if red is good, return false is blue is good
    bool findBoxColour(); // find the box colout=r. return true if red, false if blue
    void openGate(float GOODORBAD); // Open the gate
    
    bool detectDryPot(); // Detect dry potato. return true if dry, false if wet
    void takeWater(); // Ask Raspberry Pi to take water
    void waterPot(); // Ask Raspberry Pi to water the potato
    void playStarman(); // Play Starman song

    void ledOn(); // Turn on the LED
    void ledOff(); // Turn off the LED

    int boxColumnColors(bool goodRed); // Get the box colors of the column
    int rightBoxColumnColors(bool goodRed); // turn camera to right and Get the box colors of the column
    bool takeRightBox(); // Ask Raspberry Pi to take the box

    void waitForResponse(); // Wait for a response from the Raspberry Pi
    bool waitForBoolResponse(); // Wait for a boolean response from the Raspberry Pi
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
        Serial.println("TAKE_POTATO");
        // waitForResponse();
    }

bool Raspi::takeRightBox()
    {
        Serial.println("TAKE_POTATO");
        waitForResponse();
    }

bool Raspi::isRedGood()
    {
        Serial.println("IS_RED_GOOD");
        return waitForBoolResponse();
    }

bool Raspi::findBoxColour()
    {
        Serial.println("FIND_BOX_COLOR");
        return waitForBoolResponse();
    }

void Raspi::openGate(float goodOrBad)
    {
        Serial.print("OPEN_GATE:");
        Serial.println(goodOrBad);
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

#endif // RASPI_H