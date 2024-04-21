#ifndef wioImperialButton
#define wioImperialButton

#include "ModeButton.h"

class ImperialButton : public ModeButton {
    public:
      ImperialButton(int pin);
      long convertToFahrenheit(long valueCelsius);
      long convertToInches(long valueCM);
    private:
      void printStatus();
};

#endif