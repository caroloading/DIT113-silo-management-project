#include "./Ranger.h"


Ranger::Ranger(int pin) : _ultrasonic(pin)
{
    _ultrasonic = Ultrasonic(pin);
};

long Ranger::MeasureRange()
{
    return _ultrasonic.MeasureInCentimeters();
};
