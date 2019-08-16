#include "DPS.hpp"
namespace dps
{
    DPS::~DPS()
    {
        bus_->removeDevice(addr_);
    }
    dps_err_t DPS::setOpMode(Mode opMode){
        if (DPS_ERR_CHECK(writeByteBitfield(config_registers[MSR_CTRL], opMode))){
            return DPS__FAIL_UNKNOWN;
        }
        m_opMode = (Mode)opMode;
	    return DPS__SUCCEEDED;
    }
} // namespace dps
