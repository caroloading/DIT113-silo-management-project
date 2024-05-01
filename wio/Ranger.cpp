#include "Ranger.h"


Ranger::Ranger(int pin) : _ultrasonic(pin) { }

double Ranger::MeasureRange()
{
  return _ultrasonic.MeasureInCentimeters();
}

