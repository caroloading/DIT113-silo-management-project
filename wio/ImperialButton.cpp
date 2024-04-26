#include "ImperialButton.h"


ImperialButton::ImperialButton(int pin) : ModeButton(pin) { };

long ImperialButton::ConvertToFahrenheit(long valueCelsius)
{
    return (valueCelsius * 1.8) + 32;
}

long ImperialButton::ConvertToInches(long valueCM)
{
    return valueCM / 2.54;
}

