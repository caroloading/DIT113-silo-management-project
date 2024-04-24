#ifndef wioRealTimeClock
#define wioRealTimeClock

#include <RTC_SAMD51.h>
#include <DateTime.h>


class RealTimeClock
{
    public:
        RealTimeClock();
        DateTime GetNow();  
    private:
        RTC_SAMD51 _rtc;
};


#endif // wioRealTimeClock

