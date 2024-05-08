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
    double distance = _ranger->MeasureRange();
    double temperature = _temphum->GetTemperature();
    double humidity = _temphum->GetHumidity();

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

    bool isTempOutOfBounds = _IsTemperatureOutOfBounds(measurements->temperature);
    if (isTempOutOfBounds) {
        display->DisplayWarning("Temperature out of bounds");
    }

    delay(1000); // pause necessary to allow user to see warning

    bool isHumOutOfBounds = _IsHumidityOutOfBounds(measurements->humidity);
    if (isHumOutOfBounds) {
        display->DisplayWarning("Humidity out of bounds");
    }

    if (!isTempOutOfBounds && !isHumOutOfBounds) {
        display->HideWarning(); 
    }
    
    const char *temperatureUnit = "C", *temperatureLabel = "Temp";
    const char *humidityUnit = "%", *humidityLabel = "R.H.";
    const char *distanceUnit = "cm", *distanceLabel = "G. Lvl";

    if (_imperialButton->IsEnabled()) {
        measurements->temperature = _imperialButton->ConvertToFahrenheit(
            measurements->temperature
        );
        measurements->distance = _imperialButton->ConvertToInches(
            measurements->distance
        );
        temperatureUnit = "F";
        distanceUnit = "in";
    }

    display->DisplayMeasurement(
        temperatureLabel, temperatureUnit, measurements->temperature
    );
    display->DisplayMeasurement(
        humidityLabel, humidityUnit, measurements->humidity
    );
    display->DisplayMeasurement(
        distanceLabel, distanceUnit, measurements->distance
    );
}

bool SensorManager::_IsTemperatureOutOfBounds(double temperature)
{
    return temperature < Silo::LOWER_BOUND_TEMPERATURE || temperature > Silo::UPPER_BOUND_TEMPERATURE;
}

bool SensorManager::_IsHumidityOutOfBounds(double humidity)
{
    return humidity < Silo::LOWER_BOUND_HUMIDITY || humidity > Silo::UPPER_BOUND_HUMIDITY;
}

