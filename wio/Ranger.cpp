#include "Ranger.h"


Ranger::Ranger(int pin) : _ultrasonic(pin) { }

long Ranger::MeasureRange()
{
  return _ultrasonic.MeasureInCentimeters();
}

