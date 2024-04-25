#ifndef wioWioDisplay
#define wioWioDisplay

#include "TFT_eSPI.h"
#include <DateTime.h>


class WioDisplay {
    public:
        WioDisplay();
        void DisplayPause(const char *msg = "Paused for maintenance.");
        void DisplayConnectingToWiFi(const char *msg = "Connecting to WiFi...");
        void DisplayConnectedToWiFi(String ipAddress);
        void DisplayCurrentTime(DateTime now);
        void DisplayWarning(const char *text);
        void DisplayMeasurement(const char* preValue, const char* postValue, long measurement);
        void SetDefaultPreset();
    private:
        TFT_eSPI _tft;
    };


#endif // wioWioDisplay

