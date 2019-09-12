#include "MPU.hpp"

namespace mpu
{
    MPU::MPU(mpu_bus_t& bus, mpu_addr_handle_t addr) : bus_{&bus}, addr_{addr}, buffer_{0}, err_{ESP_OK} {}

    MPU::~MPU()
    {
    }
} // namespace mpu
