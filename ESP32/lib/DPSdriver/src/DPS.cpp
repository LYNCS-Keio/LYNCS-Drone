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
    esp_err_t DPS::disableFIFO(){
        if (DPS_ERR_CHECK(flushFIFO()))return err_;
        if (DPS_ERR_CHECK(writeByteBitfield(config_registers[FIFO_EN],0U)))return err_;
	    return err_;
    }
    dps_err_t DPS::standby(){
        //abort if initialization failed
	    if (m_initFail)
	    {
	    	return DPS__FAIL_INIT_FAILED;
	    }
	    //set device to idling mode
	    dps_err_t ret = setOpMode(IDLE);
	    if (ret != DPS__SUCCEEDED)
	    {
	    	return ret;
	    }
	    if (DPS_ERR_CHECK(disableFIFO()))return DPS__FAIL_CANNOT_WRITE_REG;
	    return DPS__SUCCEEDED;
    }
    dps_err_t DPS::configTemp(uint8_t tempMr, uint8_t tempOsr){
        tempMr &= 0x07;
	    tempOsr &= 0x07;
	    // two accesses to the same register; for readability
	    if (DPS_ERR_CHECK(writeByteBitfield(config_registers[TEMP_MR], tempMr)))return DPS__FAIL_UNKNOWN;
	    if (DPS_ERR_CHECK(writeByteBitfield(config_registers[TEMP_OSR], tempOsr)))return DPS__FAIL_UNKNOWN;
	    m_tempMr = tempMr;
	    m_tempOsr = tempOsr;
    }
} // namespace dps
