#include "ModeButton.h"

ModeButton::ModeButton(int pin){
    _pin = pin;
    _isEnabled = false;
    pinMode(pin, INPUT_PULLUP);
};

bool ModeButton::ChangeIfPressed(){
  if (digitalRead(_pin) == LOW){
    _isEnabled = !_isEnabled;
    if (_isEnabled){
      Serial.println("Paused for maintenance.");
    } else {
      Serial.println("Resuming measures.");
    }
  }
}

bool ModeButton::isEnabled(){
  return _isEnabled;
}