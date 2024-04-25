#ifndef wioSensorManager
#define wioSensorManager

#include "MqttClient.h"
#include "Ranger.h"
#include "LedBar.h"
#include "ModeButton.h"
#include "ImperialButton.h"
#include "ThermometerAndHumidity.h"
#include "Silo.h"
#include "WioDisplay.h"


struct PublishedMeasurements
{
    long distance;
    long temperature;
    long humidity;
};

class SensorManager
{
    public:
        SensorManager(
            Ranger* ranger, 
            LedBar* ledBar, 
            ModeButton* modeButton, 
            ImperialButton* imperialButton, 
            ThermometerAndHumidity* temphum
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

        bool _IsTemperatureOutOfBounds(long temperature);
        bool _IsHumidityOutOfBounds(long humidity);
};


#endif // wioSensorManager

