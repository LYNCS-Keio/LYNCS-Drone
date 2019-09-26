#include "DPS.hpp"
#include <cmath>

constexpr uint8_t DPS310__BUSYTIME_FAILSAFE = 10U;

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

namespace dps
{

const int32_t DPS::scaling_facts[] = {524288, 1572864, 3670016, 7864320, 253952, 516096, 1040384, 2088960};

dps_err_t DPS::dev_init(uint8_t spi_mode, uint32_t clock_speed_hz, int cs_io_num)
{
    if (m_dev_init_)
    {
    bus_->removeDevice(addr_);
}    
    if (DPS_ERR_CHECK(bus_->addDevice(spi_mode, clock_speed_hz, cs_io_num, &addr_)))return DPS__FAIL_COMMUNICATION;
    m_dev_init_ = true;
    return DPS__SUCCEEDED;
}

dps_err_t DPS::setOpMode(Mode opMode)
{
    if (DPS_ERR_CHECK(writeByteBitfield(config_registers[MSR_CTRL], opMode))){
        return DPS__FAIL_UNKNOWN;
    }
    m_opMode = (Mode)opMode;
    return DPS__SUCCEEDED;
}

dps_err_t DPS::disableFIFO()
{
	dps_err_t ret = flushFIFO();
    if (ret != DPS__SUCCEEDED)return ret;
	
    ret = writeByteBitfield(config_registers[FIFO_EN],0U);
	if (ret != DPS__SUCCEEDED)return ret;
    return ret;
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
    m_tempMr = tempMr;
    if (DPS_ERR_CHECK(writeByteBitfield(config_registers[TEMP_OSR], tempOsr)))return DPS__FAIL_UNKNOWN;
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
    	return DPS__FAIL_TOO_BUSY;
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

dps_err_t DPS::startMeasurePressureOnce(uint8_t oversamplingRate)
{
	//abort if initialization failed
	if (m_initFail)
	{
		return DPS__FAIL_INIT_FAILED;
	}
	//abort if device is not in idling mode
	if (m_opMode != IDLE)
	{
		return DPS__FAIL_TOO_BUSY;
	}
	//configuration of oversampling rate, lowest measure rate to avoid conflicts
	if (oversamplingRate != m_prsOsr)
	{
		if (configPressure(0U, oversamplingRate))
		{
			return DPS__FAIL_UNKNOWN;
		}
	}
	//set device to pressure measuring mode
	return setOpMode(CMD_PRS);
}

dps_err_t DPS::startMeasurePressureOnce()
{
	return startMeasurePressureOnce(m_prsOsr);
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
    	return DPS__FAIL_TOO_BUSY;
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
	dps_err_t ret = readBlock(reg, buffer_);
    if (ret != DPS__SUCCEEDED)return ret;

    *raw = (uint32_t)buffer_[0] << 16 | (uint32_t)buffer_[1] << 8 | (uint32_t)buffer_[2];
    *raw = convert_complement<int32_t,24>(*raw);
    return DPS__SUCCEEDED;
}

uint16_t DPS::calcBusyTime(uint16_t mr, uint16_t osr)
{
	//formula from datasheet (optimized)
	return ((uint32_t)20U << mr) + ((uint32_t)16U << (osr + mr));
}

dps_err_t DPS::measureTempOnce(float &result, uint8_t oversamplingRate)
{
	//Start measurement
	dps_err_t ret = startMeasureTempOnce(oversamplingRate);
	if (ret != DPS__SUCCEEDED)
	{
		if (ret == DPS__FAIL_TOO_BUSY)
		{
			standby();
		}
		return ret;
	}
	//wait until measurement is finished
	ets_delay_us(1000*calcBusyTime(0U, m_tempOsr) / DPS__BUSYTIME_SCALING);
	//sampling interval must be over 10ms when using DPS310
	ets_delay_us(1000*DPS310__BUSYTIME_FAILSAFE);

	ret = getSingleResult(result);
	if (ret != DPS__SUCCEEDED)
	{
		standby();
	}
	return ret;
}

dps_err_t DPS::measureTempOnce(float &result)
{
	return measureTempOnce(result, m_tempOsr);
}

dps_err_t DPS::correctTemp()
{
	if (m_initFail)
	{
		return DPS__FAIL_INIT_FAILED;
	}
	writeByte(0x0E, 0xA5);
	writeByte(0x0F, 0x96);
	writeByte(0x62, 0x02);
	writeByte(0x0E, 0x00);
	writeByte(0x0F, 0x00);
	//perform a first temperature measurement (again)
	//the most recent temperature will be saved internally
	//and used for compensation when calculating pressure
	float trash;
	measureTempOnce(trash);

	return DPS__SUCCEEDED;
}

dps_err_t DPS::measurePressureOnce(float &result, uint8_t oversamplingRate)
{
	//start the measurement
	dps_err_t ret = startMeasurePressureOnce(oversamplingRate);
	if (ret != DPS__SUCCEEDED)
	{
		if (ret == DPS__FAIL_TOO_BUSY)
		{
			standby();
		}
		return ret;
	}
	//wait until measurement is finished
	ets_delay_us(1000*calcBusyTime(0U, m_tempOsr) / DPS__BUSYTIME_SCALING);
	//sampling interval must be over 10ms when using DPS310
	ets_delay_us(1000*DPS310__BUSYTIME_FAILSAFE);

	ret = getSingleResult(result);
	if (ret != DPS__SUCCEEDED)
	{
		standby();
	}
	return ret;
}

dps_err_t DPS::measurePressureOnce(float &result)
{
	return measurePressureOnce(result, m_prsOsr);
}

dps_err_t DPS::measureHeightOnce(float &result, uint8_t oversamplingrRate)
{
	float T = 0,P = 0;
	dps_err_t ret = measureTempOnce(T, oversamplingrRate);
	if (ret != DPS__SUCCEEDED)return ret;

	ret = measurePressureOnce(P, oversamplingrRate);
	if (ret != DPS__SUCCEEDED)return ret;

	result = (std::pow(DPS__SEA_LEVEL_PRESSURE/(P/100.0),(1.0/5.257)) - 1)*(T + 273.15)/0.0065;
	return DPS__SUCCEEDED;
}

} // namespace dps
