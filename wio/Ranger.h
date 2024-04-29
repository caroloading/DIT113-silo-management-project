#ifndef wioRanger
#define wioRanger

#include "Ultrasonic.h"
#include "LedBar.h"
#include "JsonSerializable.h"


class Ranger : public JsonSerializable
{
    public:
      Ranger(int pin);
      float MeasureRange();
    private:
      Ultrasonic _ultrasonic;
};


#endif // wioRanger

