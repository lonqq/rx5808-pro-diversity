#include <Arduino.h>

#include "voltage.h"
#include "settings_eeprom.h"
#include "settings.h"
#include "timer.h"
#include "ui.h"
#include "buzzer.h"

namespace Voltage
{

    uint16_t voltageRaw = 0;
    uint8_t voltage;
    uint8_t voltageDec;
    uint16_t prevVoltageRaw = 0;
    Timer voltageUpdateTimer = Timer(1000);
    Timer alarmTimer = Timer(5000);
    uint8_t isCharging = 0;
    String batteryLevel;

    void setup()
    {
        voltageUpdateTimer.reset();
        alarmTimer.reset();
    }

    String getBatteryLevelString()
    {
        float voltage = voltageRaw / 10.0f;
        char buffer[10];
        dtostrf(voltage, 4, 1, buffer); // Convert float to string with 1 decimal place
        return String(buffer) + "V";
    }

    void update()
    {
        if (!voltageUpdateTimer.hasTicked())
            return;

        voltageRaw = 0;
        for (uint8_t i = 0; i < 8; i++)
        {
            voltageRaw += analogRead(PIN_VBAT);
        }
        voltageRaw /= 8;

        if (prevVoltageRaw == 0)
            prevVoltageRaw = voltageRaw;

        // voltageRaw = voltageRaw / 5 + 4 * prevVoltageRaw / 5;
        prevVoltageRaw = voltageRaw;

        voltageRaw = voltageRaw * 10 / VBAT_SCALE;

        voltage = voltageRaw / 10;
        voltageDec = voltageRaw % 10;
        isCharging = digitalRead(PIN_CHRG);
        voltageUpdateTimer.reset();
        batteryLevel = getBatteryLevelString();

        if (alarmTimer.hasTicked())
        {

            if (voltageRaw < CRITICAL_VOLTAGE && voltageRaw > 10)
            {
                Buzzer::enable(CRITICAL_BEEPS);
            }
            else if (voltageRaw < WARNING_VOLTAGE && voltageRaw > 10)
            {
                Buzzer::enable(WARNING_BEEPS);
            }

            alarmTimer.reset();
        }
    }

} // namespace Voltage