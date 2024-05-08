#ifndef wioWioDisplay
#define wioWioDisplay

#include <cstdio>
#include "TFT_eSPI.h"
#include <DateTime.h>

extern TFT_eSPI tft;


class WioDisplay {
    public:
        WioDisplay();
        void DisplayBackground();
        void DisplayLines();
        void DisplayLabels();
        void DisplayWifiStatus(bool isConnected);
        void DisplayMqttStatus(bool isConnected);
        void DisplayPause(const char *msg = "Paused for maintenance.");
        void DisplayWarning(const char *text);
        void HideWarning();
        void DisplayConnectingToWiFi(const char *msg = "Connecting to WiFi...");
        void DisplayConnectedToWiFi(String ipAddress);
        void DisplayCurrentTime(DateTime now);
        void DisplayMeasurement(
            const char* label, 
            const char* m_unit, 
            double measurement
        );
        static double savedTemperature;
        static double savedHumidity;
        static double savedDistance; 
    };

#endif // wioWioDisplay

