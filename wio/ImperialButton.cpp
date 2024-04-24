#include "ImperialButton.h"


ImperialButton::ImperialButton(int pin) : ModeButton(pin) { };

void ImperialButton::_PrintStatus()
{
  if (IsEnabled()){
    Serial.println("Displaying in imperial units.");
  } else {
    Serial.println("Displaying in metric units.");
  }
}

long ImperialButton::ConvertToFahrenheit(long valueCelsius)
{
  return (valueCelsius * 1.8) + 32;
}

long ImperialButton::ConvertToInches(long valueCM)
{
  return valueCM / 2.54;
}
