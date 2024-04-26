#include "RealTimeClock.h"


RealTimeClock::RealTimeClock(
    unsigned long ntpUpdateInterval,
    long utcOffset,
    const char* ntpServer
) : _rtc(), _udp(), _ntp(_udp, ntpServer, utcOffset, ntpUpdateInterval)
{
    _rtc.begin();
    _ntp.begin();
    
    // Adjust the clock using current time
    _rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    
    _ntpUpdateInterval = ntpUpdateInterval;
    _deviceTime = 0;
}

DateTime RealTimeClock::GetNow()
{
    return _rtc.now();
}

void RealTimeClock::UpdateRtcUsingNtp()
{
    _ntp.update(); // get update from NTP server 

    // get the Epoch time, i.e., time in seconds since Jan. 1, 1970
    _deviceTime = _ntp.getEpochTime();
    if (_deviceTime == 0) {
        Serial.println("Failed to get time from network time server.");
    } else {
        // adjust RTC localtime
        Serial.println("Adjust dateTime!");
        _rtc.adjust(DateTime(_deviceTime));

        // get and log the current RTC dateTime
        Serial.print("RTC time is: ");
        // ISO_LOCAL_DATE_TIME
        Serial.println(_rtc.now().timestamp(DateTime::TIMESTAMP_FULL)); 
    } 
}

unsigned long RealTimeClock::GetNtpUpdateInterval()
{
    return _ntpUpdateInterval;
}

