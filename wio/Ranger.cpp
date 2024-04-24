#include "./Ranger.h"


Ranger::Ranger(int pin) : _ultrasonic(pin)
{
    _ultrasonic = Ultrasonic(pin);
};

long Ranger::_MeasureRange()
{
  return _ultrasonic.MeasureInCentimeters();
};

std::string Ranger::GetRangeData()
{
    return "{\"value\": " + std::to_string(_MeasureRange()) + "}";
}
