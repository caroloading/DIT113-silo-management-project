#include "ModeButton.h"


ModeButton::ModeButton(int pin)
{
    _pin = pin;
    _isEnabled = false;
    pinMode(pin, INPUT_PULLUP);
};

bool ModeButton::ChangeIfPressed()
{
  if (digitalRead(_pin) == LOW){
    _isEnabled = !_isEnabled;
  } 
  _PrintStatus();
}

bool ModeButton::IsEnabled()
{
  return _isEnabled;
}

// NOTE: that is purely for debug, right?
void ModeButton::_PrintStatus()
{
  if (_isEnabled){
    Serial.println("Paused for maintenance.");
  } else {
    Serial.println("Measuring.");
  }
}
