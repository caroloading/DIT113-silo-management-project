#include "IntervalController.h"


// INTERVAL

void Interval::UpdateLastRun(unsigned long lastRun)
{
    _lastRun = lastRun;
}

unsigned int Interval::GetLastRun()
{
    return _lastRun;
}


// CHECK BUTTON INTERVAL

CheckButtonInterval::CheckButtonInterval(
    ImperialButton* imperialButton, 
    ModeButton* pauseButton, 
    unsigned int intervalMillis
)
{
    UpdateLastRun(0);
    _intervalMillis = intervalMillis;
    _imperialButton = imperialButton;
    _pauseButton = pauseButton;
}

bool CheckButtonInterval::IsOverInterval(unsigned long currentMillis)
{
    return (currentMillis - GetLastRun()) >= _intervalMillis;
}

void CheckButtonInterval::RunIntervalAction()
{
    _pauseButton->ChangeIfPressed();
    _imperialButton->ChangeIfPressed();
}


// PUBLISH INTERVAL

PublishInterval::PublishInterval(
    ModeButton* pauseButton, 
    CustomWiFi* wifi, 
    MqttClient* client, 
    SensorManager* sensorManager, 
    WioDisplay* display, 
    RealTimeClock* realTimeClock,
    unsigned int intervalMillis
)
{
    UpdateLastRun(0);
    _intervalMillis = intervalMillis;
    _pauseButton = pauseButton;
    _wifi = wifi;
    _client = client;
    _sensorManager = sensorManager;
    _display = display;
    _realTimeClock = realTimeClock;
}

bool PublishInterval::IsOverInterval(unsigned long currentMillis)
{
    return (currentMillis - GetLastRun()) >= _intervalMillis;
}

void PublishInterval::RunIntervalAction()
{
    if (_pauseButton->IsEnabled()) {
        _display->DisplayPause();
        return;
    }

    _wifi->CheckConnection();
    _client->CheckConnection();

    _sensorManager->PublishAndUpdateSensorMeasurements(_client, _display);
    _display->DisplayCurrentTime(_realTimeClock->GetNow());
}


// INTERVAL CONTROLLER

IntervalController::IntervalController()
{
    _intervals = std::vector<Interval*>();
}

void IntervalController::AddInterval(Interval* interval)
{
    _intervals.push_back(interval);
}

void IntervalController::RunIntervals(unsigned long currentMillis)
{
    for (unsigned int i = 0; i < _intervals.size(); i++) {
        Interval* currentInterval = _intervals.at(i);

        if (currentInterval->IsOverInterval(currentMillis)) {
            currentInterval->UpdateLastRun(currentMillis);
            currentInterval->RunIntervalAction();
        }
    }
}

