/**
 * @file main.cpp
 * Main function.
 */
// =========================================================================
// This code is placed under the MIT License
// Copyright 2019 Laboratory of sYNsetic Cosmic Science. All rights reserved.
// For the license information refer to LICENSE file in root directory.
// =========================================================================

#include <cstdio>
#include <vector>
#include "SPIbus.hpp"
#include "DPS.hpp"
#include "DPS310.hpp"
#include "ESCdriver.hpp"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_err.h"

#define SPI_CLOCK   10000000  // 10 MHz
#define SPI_MODE    3

#define MISO_PIN    19
#define MOSI_PIN    23
#define SCLK_PIN    18
#define CS_PIN      14

#define PWM_1 15
#define PWM_2 4
#define PWM_3 16
#define PWM_4 17

extern "C" void app_main()
{
    SPI_t &mySPI = hspi;  // vspi and hspi are the default objects

    spi_bus_config_t config;
    config.mosi_io_num = MOSI_PIN;
    config.miso_io_num = MISO_PIN;
    config.sclk_io_num = SCLK_PIN;
    config.quadwp_io_num = -1; // -1 not used
    config.quadhd_io_num = -1; // -1 not used
    config.max_transfer_sz = 4094;
    config.flags = 0;
    config.intr_flags = 0;
    spi_bus_initialize(HSPI_HOST, &config, 0); // 0 DMA not used
    
    dps310::DPS310 myDPS(&mySPI);
    myDPS.dev_init(SPI_MODE,SPI_CLOCK,CS_PIN);
    myDPS.setTmpOversamplingRate(1);
    myDPS.setPrsOversamplingRate(1);

    dps::dps_err_t ret = myDPS.initiarize();
    printf("ret=%d\n",ret);
    if (ret != dps::DPS__SUCCEEDED)
    {
        return;
    }
    
    std::vector<int> pins{PWM_1, PWM_2, PWM_3, PWM_4};

    mcpwm_config_t conf;
    conf.frequency = 50;
    conf.cmpr_a = 0;
    conf.cmpr_b = 0;
    conf.duty_mode = MCPWM_DUTY_MODE_0;
    conf.counter_mode = MCPWM_UP_COUNTER;
    
    esc::ESCdriver myESC;
    myESC.initialize(pins, conf);

    vTaskDelay(1000 / portTICK_PERIOD_MS);
    while (1)
    {
        float H;
        dps::dps_err_t ret;
        ret = myDPS.measureHeightOnce(H, 1);
        printf("H= %f meter ret = %d\n",H, ret);

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
