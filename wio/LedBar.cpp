#include "LedBar.h"


LedBar::LedBar(
    int clockPin,
    int dataPin,
    LedOrientation orientation,
    int minDisplayRange,
    int maxDisplayRange
): _ledBar(clockPin, dataPin, orientation, LedType::LED_BAR_10) 
{
    _ledBar.begin();

    _minDisplayRange = minDisplayRange;
    _maxDisplayRange = maxDisplayRange;
}

void LedBar::_SetLevel(int level)
{
    // NOTE: a silent error here as runtime errors in the embedded world
    // are not something that is really allowed...
    if (level < LedBar::MIN_LEVEL) {
        level = LedBar::MIN_LEVEL;
    } else if (level > LedBar::MAX_LEVEL) {
        level = LedBar::MAX_LEVEL;
    }

    _ledBar.setLevel(level);
}

void LedBar::UpdateDisplay(long value)
{
    _SetLevel(LedBar::MAX_LEVEL - (int)((value * LedBar::MAX_LEVEL) /_maxDisplayRange));
}

