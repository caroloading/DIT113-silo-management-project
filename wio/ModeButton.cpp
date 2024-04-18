#include "ModeButton.h"

ModeButton::ModeButton(int pin){
    _pin = pin;
    _isEnabled = false;
    pinMode(pin, INPUT_PULLUP);
};

bool ModeButton::ChangeIfPressed(){
  if (digitalRead(_pin) == LOW){
    if (_isEnabled){
      _isEnabled = false;
    } else {
      _isEnabled = true;
    }
  }
}

bool ModeButton::isEnabled(){
  return _isEnabled;
}