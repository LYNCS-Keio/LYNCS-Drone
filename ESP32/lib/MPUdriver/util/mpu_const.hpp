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
        MPU__FAIL_COMMUNICATION = -3
    };
    enum Config_Registers_e
    {
        MPU__WHO_AM_I = 0
    };
    const RegMask_t registers[] = {
        {0x75, 0xFF, 0}
    };
} // namespace mpu
