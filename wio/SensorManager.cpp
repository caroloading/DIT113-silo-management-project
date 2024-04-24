#include "SensorManager.h"


SensorManager::SensorManager(Ranger* ranger, LedBar* ledBar, ModeButton* modeButton, ImperialButton* imperialButton, ThermometerAndHumidity* temphum)
{
    _ranger = ranger;
    _ledBar = ledBar;
    _modeButton = modeButton;
    _imperialButton = imperialButton;
    _temphum = temphum;
}

PublishedMeasurements SensorManager::PublishMeasurements(MqttClient* client)
{
    long distance = _ranger->MeasureRange();
    long temperature = _temphum->GetTemperature();
    long humidity = _temphum->GetHumidity();

    client->Publish(Topic::DISTANCE, _ranger->ToJson((const char*)distance).c_str());
    client->Publish(Topic::TEMPERATURE, _temphum->ToJson((const char*)temperature).c_str());
    client->Publish(Topic::HUMIDITY, _temphum->ToJson((const char*)humidity).c_str());

    return PublishedMeasurements{
        distance,
        temperature,
        humidity
    };
}

