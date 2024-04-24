#ifndef wioWioDisplay
#define wioWioDisplay

#include "TFT_eSPI.h"


class WioDisplay
{
    public:
        WioDisplay();
        void DisplayPause(const char* msg = "Paused for maintenance.");        
    private:
        TFT_eSPI _tft;
};


#endif // wioWioDisplay

