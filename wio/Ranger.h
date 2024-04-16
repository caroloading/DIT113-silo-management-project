#ifndef wioRanger
#define wioRanger

#include <iostream>
#include "Ultrasonic.h"  // External lib
#include "LedBar.h"

class Ranger 
{
    public:
        Ranger(int pin);
        long MeasureRange();
    private:
        int _pin;
        Ultrasonic _ultrasonic;
};

#endif // wioRanger
