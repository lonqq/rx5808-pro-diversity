#include <Arduino.h>

#include "settings.h"
#include "timer.h"

namespace Buzzer
{
    bool buzzerActive = false;
    bool buzzerState = false; // To remember the current pin state
    Timer buzzerTimer = Timer(10);
    int beepCount = 0;
    int beepPattern = 0;
    unsigned long beepDuration = 200; // Duration of each beep
    unsigned long beepDelay = 100;    // Delay between beeps

    void setup()
    {
        pinMode(PIN_BUZZER, OUTPUT);
        digitalWrite(PIN_BUZZER, HIGH); // Ensure buzzer is initially off
        buzzerState = false;            // Buzzer is initially off
    }

    void enable(unsigned int pattern = 1)
    {
        if (buzzerActive)
            return;
        buzzerActive = true;
        beepPattern = pattern;
        beepCount = 0;
        // Start the first beep
        digitalWrite(PIN_BUZZER, LOW);
        buzzerState = true;
        buzzerTimer = Timer(beepDuration);
    }

    void update()
    {
        if (buzzerActive && buzzerTimer.hasTicked())
        {
            if (buzzerState)
            {
                // Buzzer is currently on, turn it off
                digitalWrite(PIN_BUZZER, HIGH);
                buzzerState = false;
                buzzerTimer = Timer(beepDelay);
                beepCount++;
            }
            else
            {
                // Buzzer is currently off, turn it on if more beeps are needed
                if ((beepPattern == 1 && beepCount < 1) ||
                    (beepPattern == 2 && beepCount < 2) ||
                    (beepPattern == 3 && beepCount < 3))
                {
                    digitalWrite(PIN_BUZZER, LOW);
                    buzzerState = true;
                    buzzerTimer = Timer(beepDuration);
                }
                else
                {
                    // No more beeps needed, stop the buzzer
                    buzzerActive = false;
                }
            }
        }
    }
}