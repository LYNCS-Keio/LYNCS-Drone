#include "DPS.hpp"

//convert 2´s complement numbers into signed integer numbers.
template<class uint_type,unsigned int N>
static inline int convert_complement(uint_type num){
    int t = num;
    if (num & (1 << (N-1)))
    {
        t = -(~(num - 1) & ((1 << N) - 1));
    }
    return t;
}

namespace dps
{
    const int32_t DPS::scaling_facts[DPS__NUM_OF_SCAL_FACTS] = {524288, 1572864, 3670016, 7864320, 253952, 516096, 1040384, 2088960};

    DPS::~DPS()
    {
        bus_->removeDevice(addr_);
    }
    

    dps_err_t DPS::setOpMode(Mode opMode)
    {
        if (DPS_ERR_CHECK(writeByteBitfield(config_registers[MSR_CTRL], opMode))){
            return DPS__FAIL_UNKNOWN;
        }
        m_opMode = (Mode)opMode;
	    return DPS__SUCCEEDED;
    }
    esp_err_t DPS::disableFIFO()
    {
        if (DPS_ERR_CHECK(flushFIFO()))return err_;
        if (DPS_ERR_CHECK(writeByteBitfield(config_registers[FIFO_EN],0U)))return err_;
	    return err_;
    }
    dps_err_t DPS::standby()
    {
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
    dps_err_t DPS::configTemp(uint8_t tempMr, uint8_t tempOsr)
    {
        tempMr &= 0x07;
	    tempOsr &= 0x07;
	    // two accesses to the same register; for readability
	    if (DPS_ERR_CHECK(writeByteBitfield(config_registers[TEMP_MR], tempMr)))return DPS__FAIL_UNKNOWN;
	    if (DPS_ERR_CHECK(writeByteBitfield(config_registers[TEMP_OSR], tempOsr)))return DPS__FAIL_UNKNOWN;
	    m_tempMr = tempMr;
	    m_tempOsr = tempOsr;
        return DPS__SUCCEEDED;
    }
    dps_err_t DPS::configPressure(uint8_t prsMr, uint8_t prsOsr)
    {
        prsMr &= 0x07;
	    prsOsr &= 0x07;
        //abort immediately on fail
        if (DPS_ERR_CHECK(writeByteBitfield(config_registers[PRS_MR], prsMr)))return DPS__FAIL_UNKNOWN;
	    if (DPS_ERR_CHECK(writeByteBitfield(config_registers[PRS_OSR], prsOsr)))return DPS__FAIL_UNKNOWN;
	    m_prsMr = prsMr;
	    m_prsOsr = prsOsr;
        return DPS__SUCCEEDED;
    }
    dps_err_t DPS::startMeasureTempOnce(uint8_t oversamplingRate)
    {
        //abort if initialization failed
	    if (m_initFail)
	    {
	    	return DPS__FAIL_INIT_FAILED;
	    }
	    //abort if device is not in idling mode
	    if (m_opMode != IDLE)
	    {
	    	return DPS__FAIL_TOOBUSY;
	    }
	    if (oversamplingRate != m_tempOsr)
	    {
	    	//configuration of oversampling rate
	    	if (configTemp(0U, oversamplingRate) != DPS__SUCCEEDED)
	    	{
	    		return DPS__FAIL_UNKNOWN;
	    	}
	    }
	    //set device to temperature measuring mode
	    return setOpMode(CMD_TEMP);
    }
    dps_err_t DPS::startMeasureTempOnce()
    {
    	return startMeasureTempOnce(m_tempOsr);
    }

    dps_err_t DPS::getSingleResult(float &result)
    {
        //abort if initialization failed
	    if (m_initFail)
	    {
	    	return DPS__FAIL_INIT_FAILED;
	    }

	    //read finished bit for current opMode
	    uint8_t rdy;
	    switch (m_opMode)
	    {
	    case CMD_TEMP: //temperature
	    	readByteBitfield(config_registers[TEMP_RDY],&rdy);
	    	break;
	    case CMD_PRS: //pressure
	    	readByteBitfield(config_registers[PRS_RDY],&rdy);
	    	break;
	    default: //DPS310 not in command mode
	    	return DPS__FAIL_TOOBUSY;
	    }
        
	    //read new measurement result
	    switch (rdy)
	    {
	    case 0: //ready flag not set, measurement still in progress
	    	return DPS__FAIL_UNFINISHED;
	    case 1: //measurement ready, expected case
	    	Mode oldMode = m_opMode;
	    	m_opMode = IDLE; //opcode was automatically reseted by DPS310
	    	int32_t raw_val;
	    	switch (oldMode)
	    	{
	    	case CMD_TEMP: //temperature
	    		getRawResult(&raw_val, registerBlocks[TEMP]);
	    		result = calcTemp(raw_val);
	    		return DPS__SUCCEEDED; // TODO
	    	case CMD_PRS:			   //pressure
	    		getRawResult(&raw_val, registerBlocks[PRS]);
	    		result = calcPressure(raw_val);
	    		return DPS__SUCCEEDED; // TODO
	    	default:
	    		return DPS__FAIL_UNKNOWN; //should already be filtered above
	    	}
	    }
    return DPS__FAIL_UNKNOWN;
    }
    dps_err_t DPS::getRawResult(int32_t *raw, RegBlock_t reg)
    {
	    uint8_t buffer[DPS__RESULT_BLOCK_LENGTH] = {0};
	    if (DPS_ERR_CHECK(readBlock(reg, buffer)))return DPS__FAIL_UNKNOWN;

	    *raw = (uint32_t)buffer[0] << 16 | (uint32_t)buffer[1] << 8 | (uint32_t)buffer[2];
	    *raw = convert_complement<int32_t,24>(*raw);
	    return DPS__SUCCEEDED;
    }
} // namespace dps
