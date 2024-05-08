#include "ImperialButton.h"


ImperialButton::ImperialButton(int pin) : ModeButton(pin) { };

double ImperialButton::ConvertToFahrenheit(double valueCelsius)
{
    return (valueCelsius * 1.8) + 32;
}

double ImperialButton::ConvertToInches(double valueCM)
{
    return valueCM / 2.54;
}

