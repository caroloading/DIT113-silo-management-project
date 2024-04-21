#include "ImperialButton.h"

ImperialButton::ImperialButton(int pin) : ModeButton(pin) { };

void ImperialButton::printStatus(){
  if (isEnabled()){
    Serial.println("Displaying in imperial units.");
  } else {
    Serial.println("Displaying in metric units.");
  }
}

long ImperialButton::convertToFahrenheit(long valueCelsius){
  return (valueCelsius * 1.8) + 32;
}

long ImperialButton::convertToInches(long valueCM){
  return valueCM / 2.54;
}