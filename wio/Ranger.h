#ifndef wioRanger
#define wioRanger

#include <iostream>
#include "Ultrasonic.h"
#include "LedBar.h"
#include "JsonSerializable.h"


class Ranger : public JsonSerializable
{
    public:
      Ranger(int pin);
      long MeasureRange();
    private:
      Ultrasonic _ultrasonic;
};


#endif // wioRanger
