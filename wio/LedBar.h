#ifndef wioLedBar
#define wioLedBar

#include "Grove_LED_Bar.h"


enum LedOrientation
{
    RED_FIRST = 0,
    GREEN_FIRST = 1,
};


class LedBar
{
    public:
        LedBar(int clockPin, int dataPin, LedOrientation orientation);
        void SetLevel(int level);
    private:
        Grove_LED_Bar _ledBar;
};

#endif // wioLedBar
