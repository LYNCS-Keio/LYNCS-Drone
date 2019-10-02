#pragma once
#include "mpu_register.hpp"

namespace mpu
{
    // status code
    enum mpu_err_t
    {
        MPU__SUCCEEDED = 0,
        MPU__FAIL_UNKNOWN = -1,
        MPU__FAIL_INIT_FAILED = -2,
    MPU__FAIL_COMMUNICATION = -3,
    MPU__FAIL_WRONG_DEVICE = -4
};

enum GYRO_FS
{
    GYRO_FS_SEL_250DPS = 0,
    GYRO_FS_SEL_500DPS,
    GYRO_FS_SEL_1000DPS,
    GYRO_FS_SEL_2000DPS
};

const int32_t gyro_full_scale[] = 
{
    250,
    500,
    1000,
    2000
    };

    enum Config_Registers_e
    {
    GYRO_FS_SEL = 0,
    WHO_AM_I,
        BYPASS_EN,
        H_RESET,
        SLEEP,
        CYCLE,
        GYRO_STANDBY,
        PD_PTAT,
        CLKSEL
    };
    const RegMask_t registers[] = {
    {0x1B, 0x18, 3},    //GYRO_FS_SEL
        {0x75, 0xFF, 0},    //WHO_AM_I
        {0x37, 0x02, 1},    //BYPASS_EN        
        {0x6B, 0x80, 7},    //H_RESET
        {0x6B, 0x40, 6},    //SLEEP
        {0x6B, 0x20, 5},    //CYCLE
        {0x6B, 0x10, 4},    //GYRO_STANDBY
        {0x6B, 0x08, 3},    //PD_PTAT
        {0x6B, 0x07, 0},    //CLKSEL
    };
} // namespace mpu
