#ifndef wioRealTimeClock
#define wioRealTimeClock

#include <RTC_SAMD51.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <DateTime.h>


class RealTimeClock
{
    public:
        RealTimeClock(
            unsigned long ntpUpdateInterval = 3600000,
            long utcOffset = 7200, // UTC+2
            const char* ntpServer = "europe.pool.ntp.org"
        );
        DateTime GetNow();
        void UpdateRtcUsingNtp();
        unsigned long GetNtpUpdateInterval();
    private:
        RTC_SAMD51    _rtc;
        WiFiUDP       _udp;                    // UDP object 
        NTPClient     _ntp;                    // NTP object 
        unsigned long _ntpUpdateInterval;
        unsigned long _deviceTime;             // RTC localtime (Epoch)
};


#endif // wioRealTimeClock

