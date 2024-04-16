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
        static const int MIN_LEVEL = 0;
        static const int MAX_LEVEL = 10;

        LedBar(int clockPin, int dataPin, LedOrientation orientation);

        void UpdateDisplay(long value);
    private:
        Grove_LED_Bar _ledBar;

        void _SetLevel(int level);
};

#endif // wioLedBar
