#include "LedBar.h"

LedBar::LedBar(
    int clockPin, int dataPin, LedOrientation orientation, int minDisplayRange, int maxDisplayRange
): _ledBar(clockPin, dataPin, orientation, LedType::LED_BAR_10) 
{
    _ledBar = Grove_LED_Bar(clockPin, dataPin, orientation, LedType::LED_BAR_10);
    _ledBar.begin();

    _minDisplayRange = minDisplayRange;
    _maxDisplayRange = maxDisplayRange;
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

int LedBar::_FindDisplayLevel(float value)
{
    LevelRange upperLevelRange { LedBar::MAX_LEVEL, _maxDisplayRange };
    LevelRange lowerLevelRange { LedBar::MIN_LEVEL, _minDisplayRange };

    float levelRangeStep = (_maxDisplayRange - _minDisplayRange) / LedBar::MAX_LEVEL;

    int currentLevel = LedBar::MIN_LEVEL;

    if (value > upperLevelRange.lowerBound) {
        currentLevel = LedBar::MIN_LEVEL;
    } else if (value <= levelRangeStep) {
        currentLevel = LedBar::MAX_LEVEL;
    } else {
        float currentLowerBound = _maxDisplayRange - levelRangeStep;
        for (int i = lowerLevelRange.level; i <= upperLevelRange.level; i++) {
            float currentUpperBound = currentLowerBound + levelRangeStep;

            if (value > currentLowerBound && value <= currentUpperBound) {
                currentLevel = i;
                break;
            }
            
            currentLowerBound = currentLowerBound - levelRangeStep;
        }
    }

    return currentLevel;
};


void LedBar::UpdateDisplay(long value)
{
  _SetLevel(_FindDisplayLevel((float)value));
};
