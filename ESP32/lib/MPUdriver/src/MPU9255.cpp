#include "MPU9255.hpp"
#include "../util/mpu_const.hpp"
namespace mpu9255
{

MPU9255::MPU9255(mpu_bus_t* bus) : MPU(bus)
{
}

MPU9255::~MPU9255()
{
}


} // namespace mpu9255
