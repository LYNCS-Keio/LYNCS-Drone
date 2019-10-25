#pragma once
#include "MPU.hpp"
namespace mpu9250
{
using namespace mpu;
class MPU9250 : public MPU
{
private:
    GYRO_FS m_gyro_fs_sel_;
    ACCEL_FS m_accel_fs_sel_;

public:
    MPU9250(mpu_bus_t *bus);
    ~MPU9250();
    mpu_err_t initialize();
    /**
     * @brief Set the Gyro Full Scale Select object
     * 
     * @param gyro_fs_sel 
     * @return mpu_err_t 
     */
    mpu_err_t setGyroFullScaleSelect(GYRO_FS gyro_fs_sel);
    mpu_err_t setAccelFullScaleSelect(ACCEL_FS accel_fs_sel);
    mpu_err_t measureGyro(float result[3]);
    mpu_err_t measureAccel(float result[3]);
};

} // namespace mpu9250
