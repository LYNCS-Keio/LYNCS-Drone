#pragma once

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
} // namespace mpu
