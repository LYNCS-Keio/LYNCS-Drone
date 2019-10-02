#pragma once
#include "MPU.hpp"
namespace mpu9255
{
    using namespace mpu;
    class MPU9255 : public MPU
    {
    private:
    GYRO_FS m_gyro_fs_sel_;
    mpu_err_t setGyroFullScaleSelect(GYRO_FS gyro_fs_sel);

    public:
        MPU9255(mpu_bus_t* bus);
        ~MPU9255();
        mpu_err_t initialize();
    };
    
} // namespace mpu9255
