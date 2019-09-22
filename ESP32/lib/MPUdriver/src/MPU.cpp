#include "MPU.hpp"

namespace mpu
{
    MPU::MPU(mpu_bus_t& bus) : bus_{&bus}, buffer_{0} {}

    MPU::~MPU()
    {
    }
} // namespace mpu
