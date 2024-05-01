#ifndef wioLedBar
#define wioLedBar

#include "Grove_LED_Bar.h"
#include <map>


enum LedOrientation
{
    RED_FIRST = 0,
    GREEN_FIRST = 1,
};

struct LevelRange
{
    int level;
    float lowerBound;
};

class LedBar
{
    public:
        static const int MIN_LEVEL = 1;  // NOTE: We want to have at minimum 1 LED to always be on
        static const int MAX_LEVEL = 10;

        LedBar(
            int clockPin, 
            int dataPin, 
            LedOrientation orientation, 
            int minDisplayRange = 2, 
            int maxDisplayRange = 16
        );
        void UpdateDisplay(double value);
    private:
        Grove_LED_Bar _ledBar;
        float         _minDisplayRange;
        float         _maxDisplayRange;
        
        void _SetLevel(int level);
};


#endif // wioLedBar

