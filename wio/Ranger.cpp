#include "Ranger.h"


Ranger::Ranger(int pin) : _ultrasonic(pin) { }

float Ranger::MeasureRange()
{
  return (float)_ultrasonic.MeasureInCentimeters();
}

