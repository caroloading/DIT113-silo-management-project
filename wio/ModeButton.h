#ifndef wioModeButton
#define wioModeButton

#include "TFT_eSPI.h"  


class ModeButton 
{
    public:
        ModeButton(int pin);
        bool ChangeIfPressed();
        bool IsEnabled();
    private:
        bool _isEnabled;
        int  _pin;

        virtual void _PrintStatus();
};

#endif
