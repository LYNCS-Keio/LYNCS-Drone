#include "MPU9255.hpp"
#include "../util/mpu_const.hpp"
namespace mpu9255
{
using namespace mpu;
MPU9255::MPU9255(mpu_bus_t* bus) : MPU(bus)
{
}

MPU9255::~MPU9255()
{
}

mpu_err_t MPU9255::initialize(){
    //initialize PWR_MGMT_1
    mpu_err_t ret = writeByteBitfield(registers[H_RESET],0U);
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

    //initialize INT_PIN_CFG
    ret = writeByteBitfield(registers[BYPASS_EN], 1U);
    if (ret != MPU__SUCCEEDED)return ret;

    return MPU__SUCCEEDED;
}


} // namespace mpu9255
