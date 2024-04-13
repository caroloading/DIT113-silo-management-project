#include "./Ranger.h"


Ranger::Ranger(int pin) : _ultrasonic(pin)
{
    _pin = pin;
    _ultrasonic = Ultrasonic(pin);
}

long Ranger::MeasureRange()
{
    long range;

    return _ultrasonic.MeasureInCentimeters();
}
