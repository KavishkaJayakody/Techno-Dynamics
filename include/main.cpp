#include <Arduino.h>
#include "encoders.h"


Encoders encoders;

void setup()
{
    encoders.begin();
    encoders.reset();
}
void loop()
{
    
}