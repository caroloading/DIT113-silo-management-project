#include "SensorManager.h"


SensorManager::SensorManager(
    Ranger* ranger, 
    LedBar* ledBar, 
    ModeButton* modeButton, 
    ImperialButton* imperialButton, 
    ThermometerAndHumidity* temphum,
    RealTimeClock* realTimeClock
)
{
    _ranger = ranger;
    _ledBar = ledBar;
    _modeButton = modeButton;
    _imperialButton = imperialButton;
    _temphum = temphum;
    _realTimeClock = realTimeClock;
}

void SensorManager::PublishAndUpdateSensorMeasurements(
    MqttClient* client, 
    WioDisplay* display
)
{
    PublishedMeasurements publishedMeasurements = PublishMeasurements(client);
    UpdateDisplayWithSensorData(display, &publishedMeasurements);
}

PublishedMeasurements SensorManager::PublishMeasurements(MqttClient* client)
{
    float distance = _ranger->MeasureRange();
    float temperature = _temphum->GetTemperature();
    float humidity = _temphum->GetHumidity();

    // ISO_LOCAL_DATE_TIME
    std::string now = std::string(
        _realTimeClock->GetNow().timestamp(DateTime::TIMESTAMP_FULL).c_str()
    ); 

    client->Publish(
        Topic::DISTANCE, _ranger->ToJson(distance, now).c_str()
    );
    client->Publish(
        Topic::TEMPERATURE, _temphum->ToJson(temperature, now).c_str()
    );
    client->Publish(
        Topic::HUMIDITY, _temphum->ToJson(humidity, now).c_str()
    );

    return PublishedMeasurements{
        distance,
        temperature,
        humidity
    };
}

void SensorManager::UpdateDisplayWithSensorData(
    WioDisplay* display, 
    PublishedMeasurements* measurements
)
{
    _ledBar->UpdateDisplay(measurements->distance);

    display->SetDefaultPreset();

    if (_IsTemperatureOutOfBounds(measurements->temperature)) {
        display->DisplayWarning("Temperature out of bounds");
    }
    if (_IsHumidityOutOfBounds(measurements->humidity)) {
        display->DisplayWarning("Humidity out of bounds");
    }
    
    const char* temperatureUnit = "C";
    const char* distanceUnit = " cm";

    if (_imperialButton->IsEnabled()) {
        measurements->temperature = _imperialButton->ConvertToFahrenheit(
            measurements->temperature
        );
        measurements->distance = _imperialButton->ConvertToInches(
            measurements->distance
        );
        temperatureUnit = "F";
        distanceUnit = " inches";
    }

    display->DisplayMeasurement(
        "Temperature", temperatureUnit, measurements->temperature
    );
    display->DisplayMeasurement(
        "Humidity", "%", measurements->humidity
    );
    display->DisplayMeasurement(
        "Distance", distanceUnit, measurements->distance
    );
}

bool SensorManager::_IsTemperatureOutOfBounds(float temperature)
{
    return temperature < Silo::LOWER_BOUND_TEMPERATURE || temperature > Silo::UPPER_BOUND_TEMPERATURE;
}

bool SensorManager::_IsHumidityOutOfBounds(float humidity)
{
    return humidity < Silo::LOWER_BOUND_HUMIDITY || humidity > Silo::UPPER_BOUND_HUMIDITY;
}

