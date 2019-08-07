#include "DPS.hpp"
namespace dps
{
    DPS::~DPS()
    {
        bus_->removeDevice(addr_);
    }
} // namespace dps
