#ifndef wioSensorManager
#define wioSensorManager

#include <RTC_SAMD51.h>

#include "MqttClient.h"
#include "Ranger.h"
#include "LedBar.h"
#include "ModeButton.h"
#include "ImperialButton.h"
#include "ThermometerAndHumidity.h"
#include "Silo.h"
#include "WioDisplay.h"
#include "RealTimeClock.h"

extern RTC_SAMD51 rtc;


struct PublishedMeasurements
{
    float distance;
    float temperature;
    float humidity;
};

class SensorManager
{
    public:
        SensorManager(
            Ranger* ranger, 
            LedBar* ledBar, 
            ModeButton* modeButton, 
            ImperialButton* imperialButton, 
            ThermometerAndHumidity* temphum,
            RealTimeClock* realTimeClock
        );
        PublishedMeasurements PublishMeasurements(MqttClient* client);
        void UpdateDisplayWithSensorData(
            WioDisplay* display, 
            PublishedMeasurements* measurements
        );
        void PublishAndUpdateSensorMeasurements(
            MqttClient* client, 
            WioDisplay* display
        );
    private:
        Ranger*                 _ranger;
        LedBar*                 _ledBar;
        ModeButton*             _modeButton;
        ImperialButton*         _imperialButton;
        ThermometerAndHumidity* _temphum;
        RealTimeClock*          _realTimeClock;

        bool _IsTemperatureOutOfBounds(float temperature);
        bool _IsHumidityOutOfBounds(float humidity);
};


#endif // wioSensorManager

