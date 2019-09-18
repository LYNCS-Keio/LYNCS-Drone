// =========================================================================
// This code is placed under the MIT License
// Copyright 2019 Laboratory of sYNsetic Cosmic Science. All rights reserved.
// For the license information refer to LICENSE file in root directory.
// =========================================================================

/**
 * @file main.cpp
 * Main function.
 */
#include <iostream>
#include <unistd.h>
#include <vector>
#include "ESCdriver.hpp"

extern "C" void app_main()
{
    std::vector<int> pins{14, 12};

    mcpwm_config_t conf;
    conf.frequency = 50;
    conf.cmpr_a = 0;
    conf.cmpr_b = 0;
    conf.duty_mode = MCPWM_DUTY_MODE_0;
    conf.counter_mode = MCPWM_UP_COUNTER;
    
    ESCdriver esc;
    esc.Intialize(pins, conf);

    while (1) {
        esc.setDuty_in_us(14, 1000);
        esc.setDuty_in_us(12, 1400);
        sleep(1);
        esc.setDuty_in_us(14, 2000);
        esc.setDuty_in_us(12, 1600);
        sleep(1);
    }

}