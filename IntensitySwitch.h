#ifndef INTENSITYSWITCH_H
#define INTENSITYSWITCH_H

#include "Arduino.h"

#define MEASURE_SAMPLES 5

// times im miliseconds
#define TOGGLE_ON_DURATION 100
#define TOGGLE_OFF_DURATION 100
#define POWER_ON_DURATION 1200
#define POWER_OFF_DURATION 800
#define ACCELERATE_DURATION 730
#define SENSE_CHANGE_DURATION 90
#define TRAVEL_MAX_DURATION 7000
#define SEQUENCE_TIMEOUT 8000

// values in AD counts
#define MIN_INTENSITY 260
#define MAX_INTENSITY 770
#define DB_INTENSITY (MAX_INTENSITY - MIN_INTENSITY) / 20
#define DB_INTENSITY_CHANGE 1

#define SEQUENCE_IDLE 0x00

// Toggle ON
#define TOGGLE_ON 0x10
#define TOGGLE_ON__FINALIZE 0x11

// Power ON
#define POWER_ON 0x20
#define POWER_ON__TOGGLE_ON 0x21
#define POWER_ON__IS_ON 0x22

// Power OFF
#define POWER_OFF 0x30
#define POWER_OFF__TOGGLE_ON 0x31
#define POWER_OFF__IS_OFF 0x32

// Set Intensity
#define SET_INTENSITY 0x40
#define SET_INTENSITY__GET_ON 0x41
#define SET_INTENSITY__ACCELERATE 0x42
#define SET_INTENSITY__TOGGLE_OFF 0x43
#define SET_INTENSITY__ACCELERATE_OTHER 0x44
#define SET_INTENSITY__GET_TARGET 0x45
#define SET_INTENSITY__FINALIZE 0x46

// Calibrate
#define CALIBRATE 0x50
#define CALIBRATE__ACCELERATE 0x51
#define CALIBRATE__TO_LIMIT 0x52
#define CALIBRATE__TOGGLE_OFF 0x53
#define CALIBRATE__ACCELERATE_OTHER 0x54
#define CALIBRATE__TO_OTHER_LIMIT 0x55


class IntensitySwitch
{
  public:
    byte stateName = SEQUENCE_IDLE;

    IntensitySwitch(int intensityMeasurePin, int switchPin);
    void runSequence();
    int readIntensityCounts();
    int readIntensityPercent();
    void toggleSwitch();
    void power(boolean state);
    void calibrate();
    void setIntensity(int targetIntensity);
    void quit();

  private:
    int _intensityMeasurePin;
    int _switchPin;
    long _stateTimer;
    long _sequenceTimer;
    long _intensityChangeTimer;
    int _lastIntensity;
    int _intensityChange;
    int _targetIntensity;
    bool _targetAbove;
};

#endif

