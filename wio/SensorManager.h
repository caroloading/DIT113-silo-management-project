#ifndef wioSensorManager
#define wioSensorManager

#include "MqttClient.h"
#include "Ranger.h"
#include "LedBar.h"
#include "ModeButton.h"
#include "ImperialButton.h"
#include "ThermometerAndHumidity.h"


struct PublishedMeasurements
{
    long distance;
    long temperature;
    long humidity;
};

class SensorManager
{
    public:
        SensorManager(Ranger* ranger, LedBar* ledBar, ModeButton* modeButton, ImperialButton* imperialButton, ThermometerAndHumidity* temphum);
        PublishedMeasurements PublishMeasurements(MqttClient* client);

    private:
        Ranger*                 _ranger;
        LedBar*                 _ledBar;
        ModeButton*             _modeButton;
        ImperialButton*         _imperialButton;
        ThermometerAndHumidity* _temphum;
};


#endif // wioSensorManager

