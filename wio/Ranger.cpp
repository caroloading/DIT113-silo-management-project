#include "./Ranger.h"


Ranger::Ranger(int pin) : _ultrasonic(pin)
{
    _ultrasonic = Ultrasonic(pin);
};

long Ranger::measureRange()
{
  return _ultrasonic.MeasureInCentimeters();
};

std::string Ranger::getRangeData(){
    return "{\"value\": " + std::to_string(measureRange()) + "}";
}