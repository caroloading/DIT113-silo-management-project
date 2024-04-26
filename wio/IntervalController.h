#ifndef wioIntervalController
#define wioIntervalController

#include <iostream>
#include <vector>
#include "ImperialButton.h"
#include "ModeButton.h"
#include "CustomWiFi.h"
#include "MqttClient.h"
#include "SensorManager.h"
#include "WioDisplay.h"
#include "RealTimeClock.h"


class Interval
{
    public:
        virtual bool IsOverInterval(unsigned long currentMillis);
        virtual void RunIntervalAction();
        void UpdateLastRun(unsigned long lastRun);
        unsigned int GetLastRun();
    private:
        unsigned long _lastRun;
};


class CheckButtonInterval : public Interval
{
    public:
        CheckButtonInterval(
            ImperialButton* imperialButton, 
            ModeButton* pauseButton, 
            WioDisplay* display,
            unsigned int intervalMillis = 200
        );
        bool IsOverInterval(unsigned long currentMillis) override;
        void RunIntervalAction() override;
    private:
        unsigned int    _intervalMillis;
        ImperialButton* _imperialButton;
        ModeButton*     _pauseButton;
        WioDisplay*     _display;
};


class PublishInterval : public Interval
{
    public:
        PublishInterval(
            ModeButton* pauseButton, 
            CustomWiFi* wifi, 
            MqttClient* client, 
            SensorManager* sensorManager, 
            WioDisplay* display, 
            RealTimeClock* realTimeClock, 
            unsigned int intervalMillis = 15000
        );
        bool IsOverInterval(unsigned long currentMillis) override;
        void RunIntervalAction() override;
    private:
        unsigned int   _intervalMillis;
        ModeButton*    _pauseButton;
        CustomWiFi*    _wifi;
        MqttClient*    _client;
        SensorManager* _sensorManager;
        WioDisplay*    _display;
        RealTimeClock* _realTimeClock;
};


class NtpUpdateInterval : public Interval
{
    public:
        NtpUpdateInterval(
            RealTimeClock* realTimeClock
        );
        bool IsOverInterval(unsigned long currentMillis) override;
        void RunIntervalAction() override;
    private:
        RealTimeClock* _realTimeClock;
};


class IntervalController
{
    public:
        IntervalController();
        void RunIntervals(unsigned long currentMillis);
        void AddInterval(Interval* interval);
    private:
        std::vector<Interval*> _intervals;
};


#endif // wioIntervalController

