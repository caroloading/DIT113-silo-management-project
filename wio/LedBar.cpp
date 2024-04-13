#include "LedBar.h"

LedBar::LedBar(
    int clockPin, int dataPin, LedOrientation orientation
): _ledBar(clockPin, dataPin, orientation, LedType::LED_BAR_10) 
{
    _ledBar = Grove_LED_Bar(clockPin, dataPin, orientation, LedType::LED_BAR_10);
    _ledBar.begin();
};

void LedBar::SetLevel(int level)
{
    // NOTE: a silent error here as runtime errors in the embedded world
    // are not something that is really allowed...
    if (level < 0) {
        level = 0;
    } else if (level > 10) {
        level = 10;
    }

    _ledBar.setLevel(level);
};
