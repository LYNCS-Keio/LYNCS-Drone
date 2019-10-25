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
#include "MPU9250.hpp"
#include "ESCdriver.hpp"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_err.h"

#define DPS_SPI_CLOCK 10000000 // 10 MHz
#define DPS_SPI_MODE 3

#define DPS_MISO_PIN 19
#define DPS_MOSI_PIN 23
#define DPS_SCLK_PIN 18
#define DPS_CS_PIN 14

#define MPU_SPI_CLOCK 100000 // 100 kHz
#define MPU_SPI_MODE 3

#define MPU_MISO_PIN 19
#define MPU_MOSI_PIN 23
#define MPU_SCLK_PIN 18
#define MPU_CS_PIN 5

#define PWM_1 15
#define PWM_2 4
#define PWM_3 16
#define PWM_4 17

extern "C" void app_main()
{
    SPI_t &mySPI = hspi; // vspi and hspi are the default objects

    spi_bus_config_t config;
    config.mosi_io_num = DPS_MOSI_PIN;
    config.miso_io_num = DPS_MISO_PIN;
    config.sclk_io_num = DPS_SCLK_PIN;
    config.quadwp_io_num = -1; // -1 not used
    config.quadhd_io_num = -1; // -1 not used
    config.max_transfer_sz = 4094;
    config.flags = 0;
    config.intr_flags = 0;
    spi_bus_initialize(HSPI_HOST, &config, 0); // 0 DMA not used

    dps310::DPS310 myDPS(&mySPI);
    myDPS.dev_init(DPS_SPI_MODE, DPS_SPI_CLOCK, DPS_CS_PIN);
    mpu9250::MPU9250 myMPU(&mySPI);
    myMPU.dev_init(MPU_SPI_MODE, MPU_SPI_CLOCK, MPU_CS_PIN);

    myDPS.setTmpOversamplingRate(1);
    myDPS.setPrsOversamplingRate(1);

    dps::dps_err_t ret = myDPS.initiarize();
    printf("ret=%d\n", ret);
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
    myMPU.initialize();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    while (1)
    {
        float H;
        myMPU.initialize();
        dps::dps_err_t ret;
        ret = myDPS.measureHeightOnce(H, 1);
        printf("H= %f meter ret = %d\n", H, ret);
        float Gyro[3];
        myMPU.measureGyro(Gyro);
        printf("Gyro_x=%f\n", Gyro[0]);
        printf("Gyro_y=%f\n", Gyro[1]);
        printf("Gyro_z=%f\n", Gyro[2]);

        float Accel[3];
        myMPU.measureAccel(Accel);
        printf("Accel_x=%f\n", Accel[0]);
        printf("Accel_y=%f\n", Accel[1]);
        printf("Accel_z=%f\n", Accel[2]);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}
