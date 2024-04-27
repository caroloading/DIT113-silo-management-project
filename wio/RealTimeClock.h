#ifndef wioRealTimeClock
#define wioRealTimeClock

#include <RTC_SAMD51.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <DateTime.h>

extern WiFiUDP ntpUDP;
extern NTPClient ntpClient;


class RealTimeClock
{
    public:
        RealTimeClock(
            unsigned long ntpUpdateInterval = 3600000
        );
        DateTime GetNow();
        void UpdateRtcUsingNtp();
        unsigned long GetNtpUpdateInterval();
    private:
        RTC_SAMD51    _rtc;
        unsigned long _ntpUpdateInterval;
        unsigned long _deviceTime;             // RTC localtime (Epoch)
};


#endif // wioRealTimeClock

