// =========================================================================
// This code is placed under the MIT License
// Copyright 2019 Laboratory of sYNsetic Cosmic Science. All rights reserved.
// For the license information refer to LICENSE file in root directory.
// =========================================================================

/**
 * @file main.cpp
 * Main function.
 */
#include <stdio.h>
#include "SPIbus.hpp"
#include "DPS.hpp"
#include "DPS310.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_err.h"
#include "math.h"

#define SPI_CLOCK   10000000  // 10 MHz
#define SPI_MODE    3

#define MISO_PIN    19
#define MOSI_PIN    23
#define SCLK_PIN    18
#define CS_PIN      14

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
    
    dps310::DPS310 myDPS(&mySPI, CS_PIN);
    myDPS.dev_init(SPI_MODE,SPI_CLOCK,CS_PIN);
    myDPS.setTmpOversamplingRate(1);
    myDPS.setPrsOversamplingRate(1);

    dps::dps_err_t ret = myDPS.initiarize();
    printf("ret=%d\n",ret);
    if (ret != dps::DPS__SUCCEEDED)
    {
        return;
    }
    
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    while (1)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}