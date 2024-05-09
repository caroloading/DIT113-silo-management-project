#ifndef wioImperialButton
#define wioImperialButton

#include "ModeButton.h"


class ImperialButton : public ModeButton 
{
    public:
        ImperialButton(int pin);
        double ConvertToFahrenheit(double valueCelsius);
        double ConvertToInches(double valueCM);
};

#endif
