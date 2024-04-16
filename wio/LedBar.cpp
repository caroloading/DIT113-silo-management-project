#include "LedBar.h"

LedBar::LedBar(
    int clockPin, int dataPin, LedOrientation orientation
): _ledBar(clockPin, dataPin, orientation, LedType::LED_BAR_10) 
{
    _ledBar = Grove_LED_Bar(clockPin, dataPin, orientation, LedType::LED_BAR_10);
    _ledBar.begin();
};

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
};

void LedBar::UpdateDisplay(long value)
{
    // TODO: it can probably be done better, right?
    if (value > 16) {
        _SetLevel(10);
    } else if (value > 14 && value <= 16) {
        _SetLevel(8);
    } else if (value > 12 && value <= 14) {
        _SetLevel(6);
    } else if (value > 10 && value <= 12) {
        _SetLevel(5);
    } else if (value > 8 && value <= 10) {
        _SetLevel(4);
    } else if (value > 6 && value <= 8) {
        _SetLevel(3);
    } else if (value > 4 && value <= 6) {
        _SetLevel(2);
    } else if (value > 2 && value <= 4) {
        _SetLevel(1);
    } else if (value > 0 && value <= 2) {
        _SetLevel(0);
    }
};
