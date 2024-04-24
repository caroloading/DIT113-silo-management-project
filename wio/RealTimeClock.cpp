#include "RealTimeClock.h"


RealTimeClock::RealTimeClock() : _rtc() 
{
    _rtc.begin();
    DateTime now = DateTime(F(__DATE__), F(__TIME__));
    _rtc.adjust(now);
}

DateTime RealTimeClock::GetNow()
{
    return _rtc.now();
}

