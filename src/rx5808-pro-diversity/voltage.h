#ifndef VOLTAGE_H
#define VOLTAGE_H


#include "settings.h"
#include "timer.h"


namespace Voltage {
    
    extern uint8_t voltage;
    extern uint8_t voltageDec;
    extern uint16_t prevVoltageRaw;
    extern uint8_t isCharging;
    extern String batteryLevel;
    
    void setup();
    void update();
}


#endif