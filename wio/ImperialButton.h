#ifndef wioImperialButton
#define wioImperialButton

#include "ModeButton.h"


class ImperialButton : public ModeButton 
{
    public:
        ImperialButton(int pin);
        long ConvertToFahrenheit(long valueCelsius);
        long ConvertToInches(long valueCM);
};

#endif
