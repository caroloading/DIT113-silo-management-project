#include "./Ranger.h"

extern RTC_SAMD51 rtc;

Ranger::Ranger(int pin) : _ultrasonic(pin)
{
    _ultrasonic = Ultrasonic(pin);
};

long Ranger::measureRange()
{
  return _ultrasonic.MeasureInCentimeters();
};

std::string Ranger::getRangeData(){
  std::string now = std::string(rtc.now().timestamp(DateTime::TIMESTAMP_FULL).c_str()); // ISO_LOCAL_DATE_TIME
  return "{\"value\": " + std::to_string(measureRange()) + ", \"dateTime\": \"" + now + "\"}";
}