#include "IntervalController.h"


// INTERVAL

Interval::Interval()
{
    _lastRun = 0;
}

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
    WioDisplay* display, 
    SensorManager* sensorManager, 
    unsigned int intervalMillis
)
{
    _intervalMillis = intervalMillis;
    _imperialButton = imperialButton;
    _pauseButton = pauseButton;
    _display = display;
    _sensorManager = sensorManager;
}

bool CheckButtonInterval::IsOverInterval(unsigned long currentMillis)
{
    return (currentMillis - GetLastRun()) >= _intervalMillis;
}

void CheckButtonInterval::RunIntervalAction()
{
    bool pauseStatusChanged = _pauseButton->ChangeIfPressed();
    bool unitStatusChanged = _imperialButton->ChangeIfPressed();

    if (pauseStatusChanged) {
        if (_pauseButton->IsEnabled()){
            _display->DisplayPause();
        } else {
            _display->DisplayPause("Resuming measures...");
        }
    }

    if (unitStatusChanged) {
        PublishedMeasurements measurements = PublishedMeasurements {
            WioDisplay::savedDistance,
            WioDisplay::savedTemperature,
            WioDisplay::savedHumidity
        }; 
        _sensorManager->UpdateDisplayWithSensorData(_display, &measurements);
    }
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
        return;
    }

    _wifi->CheckConnection();
    _client->CheckConnection();

    _sensorManager->PublishAndUpdateSensorMeasurements(_client, _display);
    _display->DisplayCurrentTime(_realTimeClock->GetNow());
}


// NTP UPDATE INTERVAL

NtpUpdateInterval::NtpUpdateInterval(RealTimeClock* realTimeClock)
{
    _realTimeClock = realTimeClock;
}

bool NtpUpdateInterval::IsOverInterval(unsigned long currentMillis)
{
    return (currentMillis - GetLastRun()) >= _realTimeClock->GetNtpUpdateInterval(); 
}

void NtpUpdateInterval::RunIntervalAction()
{
    _realTimeClock->UpdateRtcUsingNtp();
}


// DISPLAY INTERVAL

DisplayInterval::DisplayInterval(
    CustomWiFi* wifi, 
    MqttClient* client, 
    WioDisplay* display, 
    RealTimeClock* realTimeClock,
    unsigned int intervalMillis
)
{
    _intervalMillis = intervalMillis;
    _wifi = wifi;
    _client = client;
    _display = display;
    _realTimeClock = realTimeClock;
}

bool DisplayInterval::IsOverInterval(unsigned long currentMillis)
{
    return (currentMillis - GetLastRun()) >= _intervalMillis;
}

void DisplayInterval::RunIntervalAction()
{
    _display->DisplayWifiStatus(_wifi->IsConnected());
    _display->DisplayCurrentTime(_realTimeClock->GetNow());
    _wifi->IsConnected() ? _display->DisplayMqttStatus(_client->IsConnected()) : _display->DisplayMqttStatus(false);   
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

