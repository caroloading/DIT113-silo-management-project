#ifndef wioRanger
#define wioRanger

#include <iostream>
#include "Ultrasonic.h"  // External lib
#include "LedBar.h"

#include <RTC_SAMD51.h>

class Ranger 
{
    public:
      Ranger(int pin);
      std::string getRangeData();
    private:    
      long measureRange();
      Ultrasonic _ultrasonic;
};

#endif // wioRanger
