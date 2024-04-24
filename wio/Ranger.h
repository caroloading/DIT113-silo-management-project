#ifndef wioRanger
#define wioRanger

#include <iostream>
#include "Ultrasonic.h"
#include "LedBar.h"


class Ranger 
{
    public:
      Ranger(int pin);
      std::string GetRangeData();
    private:    
      long _MeasureRange();

      Ultrasonic _ultrasonic;
};

#endif // wioRanger
