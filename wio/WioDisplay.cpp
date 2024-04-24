#include "WioDisplay.h"


WioDisplay::WioDisplay() : _tft() 
{
    _tft.begin();
}

void WioDisplay::DisplayPause(const char* msg)
{
   _tft.fillScreen(TFT_GREEN);
   _tft.setCursor(10, 10);
   _tft.println(msg);
}
