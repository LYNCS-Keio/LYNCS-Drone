#include "MPU9255.hpp"
#include "../util/mpu_const.hpp"

namespace mpu9255
{

/**
 * @brief convert 2´s complement numbers into signed integer numbers.
 * 
 */
template<class uint_type,unsigned int N>
static inline int convert_complement(uint_type num){
    int t = num;
    if (num & (1 << (N-1)))
    {
        t = -(~(num - 1) & ((1 << N) - 1));
    }
    return t;
}

using namespace mpu;
MPU9255::MPU9255(mpu_bus_t* bus) : MPU(bus)
{
}

MPU9255::~MPU9255()
{
}

mpu_err_t MPU9255::initialize(){
    mpu_err_t ret = readByteBitfield(registers[WHO_AM_I], buffer_);
    if (buffer_[0] != 0x73) return MPU__FAIL_WRONG_DEVICE;

    //initialize PWR_MGMT_1
    ret = writeByteBitfield(registers[H_RESET],0U);
    if (ret != MPU__SUCCEEDED)return ret;

    ret = writeByteBitfield(registers[SLEEP], 0U);
    if (ret != MPU__SUCCEEDED)return ret;

    ret = writeByteBitfield(registers[CYCLE], 0U);
    if (ret != MPU__SUCCEEDED)return ret;

    ret = writeByteBitfield(registers[GYRO_STANDBY], 0U);
    if (ret != MPU__SUCCEEDED)return ret;

    ret = writeByteBitfield(registers[PD_PTAT], 0U);
    if (ret != MPU__SUCCEEDED)return ret;

    ret = writeByteBitfield(registers[CLKSEL], 0U);
    if (ret != MPU__SUCCEEDED)return ret;

    //initialize EXT_SYNC_SET
    ret = writeByteBitfield(registers[EXT_SYNC_SET], 0U);
    if (ret != MPU__SUCCEEDED)return ret;

    //initialize INT_PIN_CFG
    ret = writeByteBitfield(registers[BYPASS_EN], 1U);
    if (ret != MPU__SUCCEEDED)return ret;

    //initialize GYRO_FS_SEL
    ret = setGyroFullScaleSelect(GYRO_FS_SEL_1000DPS);
    if (ret != MPU__SUCCEEDED)return ret;

    ret = setAccelFullScaleSelect(ACCEL_FS_SEL_2G);
    if (ret != MPU__SUCCEEDED)return ret;
    return MPU__SUCCEEDED;
}

mpu_err_t MPU9255::setGyroFullScaleSelect(GYRO_FS gyro_fs_sel)
{
    mpu_err_t ret = writeByteBitfield(registers[GYRO_FS_SEL], gyro_fs_sel);
    if (ret != MPU__SUCCEEDED)return ret;
    m_gyro_fs_sel_ = gyro_fs_sel;
    return MPU__SUCCEEDED;
}

mpu_err_t MPU9255::setAccelFullScaleSelect(ACCEL_FS accel_fs_sel)
{
    mpu_err_t ret = writeByteBitfield(registers[ACCEL_FS_SEL], accel_fs_sel);
    if (ret != MPU__SUCCEEDED)return ret;
    m_accel_fs_sel_ = accel_fs_sel;
    return MPU__SUCCEEDED;
}

mpu_err_t MPU9255::measureGyro(float result[3])
{
    mpu_err_t ret = readBlock(registerBlocks[GYRO], buffer_);
    if (ret != MPU__SUCCEEDED)return ret;
    uint16_t g_raw[3] = {0};
    g_raw[0] = ((buffer_[0] << 8) | (buffer_[1]));
    g_raw[1] = ((buffer_[2] << 8) | (buffer_[3]));
    g_raw[2] = ((buffer_[4] << 8) | (buffer_[5]));

    result[0] = g_raw[0];
    result[1] = g_raw[1];
    result[2] = g_raw[2];
    return MPU__SUCCEEDED;
}

mpu_err_t MPU9255::measureAccel(float result[3])
{
    mpu_err_t ret = readBlock(registerBlocks[ACCEL], buffer_);
    if (ret != MPU__SUCCEEDED)return ret;
    uint16_t a_raw[3] = {0};
    a_raw[0] = ((buffer_[0] << 8) | (buffer_[1]));
    a_raw[1] = ((buffer_[2] << 8) | (buffer_[3]));
    a_raw[2] = ((buffer_[4] << 8) | (buffer_[5]));

    result[0] = ((float)(convert_complement<uint16_t, 16>(a_raw[0]))/(1 << 15)) * accel_full_scale[m_accel_fs_sel_];
    result[1] = ((float)(convert_complement<uint16_t, 16>(a_raw[1]))/(1 << 15)) * accel_full_scale[m_accel_fs_sel_];
    result[2] = ((float)(convert_complement<uint16_t, 16>(a_raw[2]))/(1 << 15)) * accel_full_scale[m_accel_fs_sel_];
    return MPU__SUCCEEDED;
}

} // namespace mpu9255
