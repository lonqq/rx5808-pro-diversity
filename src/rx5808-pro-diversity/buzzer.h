#ifndef BUZZER_H
#define BUZZER_H


#include "settings.h"
#include "timer.h"


namespace Buzzer {
    
    void setup();
    void update();
    void enable(unsigned int duration = 1000);
}


#endif