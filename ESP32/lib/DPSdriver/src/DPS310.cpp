#include "DPS310.hpp"
#include "../util/dps_const.hpp"
#include "../util/dps310_config.hpp"

constexpr uint8_t DPS310__OSR_SE = 3U;

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
namespace dps310
{

    DPS310::DPS310(dps_bus_t *bus) : DPS(bus),
    tmp_over_sampling_rate_(1),
    prs_over_sampling_rate_(1)
    {
        
    }
    dps_err_t DPS310::flushFIFO(){
        return writeByteBitfield(registers[FIFO_FL],1U);
    }
    dps_err_t DPS310::initiarize(){
        dps_err_t ret = readByteBitfield(registers[PROD_ID], &m_productID_);
        if (ret != DPS__SUCCEEDED)
        {
            m_initFail_ = 1U;
            return ret;
        }
        ret = readByteBitfield(registers[REV_ID], &m_revisionID_);
        if (ret != DPS__SUCCEEDED)
        {
            m_initFail_ = 1U;
            return ret;
        }
        //find out which temperature sensor is calibrated with coefficients...
        ret = readByteBitfield(registers[TEMP_SENSORREC], &m_tempSensor_);
	    if (ret != DPS__SUCCEEDED)
        {
            m_initFail_ = 1U;
            return ret;
        }

        //...and use this sensor for temperature measurement
        ret = writeByteBitfield(registers[TEMP_SENSOR],m_tempSensor_);
        if (ret != DPS__SUCCEEDED)
        {
		    m_initFail_ = 1U;
            return ret;
        }

        //read coefficients
        ret = readcoeffs();
	    if (ret != DPS__SUCCEEDED)
	    {
	    	m_initFail_ = 1U;
            return ret;
	    }
        //set to standby for further configuration
	    standby();
	    //set measurement precision and rate to standard values;
        if (configTemp(DPS__MEASUREMENT_RATE_4, tmp_over_sampling_rate_) != DPS__SUCCEEDED)
        {
	    	m_initFail_ = 1U;
            return DPS__FAIL_INIT_FAILED;
        }
        if (configPressure(DPS__MEASUREMENT_RATE_4, prs_over_sampling_rate_) != DPS__SUCCEEDED)
        {
	    	m_initFail_ = 1U;
            return DPS__FAIL_INIT_FAILED;
        }
        
        //perform a first temperature measurement
	    //the most recent temperature will be saved internally
	    //and used for compensation when calculating pressure
	    float trash;
        measureTempOnce(trash);

	    //make sure the DPS310 is in standby after initialization
	    standby();
        // Fix IC with a fuse bit problem, which lead to a wrong temperature
	    // Should not affect ICs without this problem
	    correctTemp();
        m_initFail_ = 0U;
        return DPS__SUCCEEDED;
	}
    dps_err_t DPS310::configTemp(uint8_t tempMr, uint8_t tempOsr)
    {
        dps_err_t ret = DPS::configTemp(tempMr, tempOsr);
        if (ret != DPS__SUCCEEDED)return ret;
        
        ret = writeByteBitfield(registers[TEMP_SENSOR], m_tempSensor_);
        if (ret != DPS__SUCCEEDED)return ret;
        //set TEMP SHIFT ENABLE if oversampling rate higher than eight(2^3)
        if (tempOsr > DPS310__OSR_SE)
        {
            ret = writeByteBitfield(registers[TEMP_SE], 1U);
		    if (ret != DPS__SUCCEEDED)return ret;
        }
    	else
	    {
            ret = writeByteBitfield(registers[TEMP_SE], 0U);
            if (ret != DPS__SUCCEEDED)return ret;
	    }
	    return ret;
}
    dps_err_t DPS310::configPressure(uint8_t prsMr, uint8_t prsOsr)
    {
        dps_err_t ret = DPS::configPressure(prsMr, prsOsr);
        if (ret != DPS__SUCCEEDED)return ret;
        //set PM SHIFT ENABLE if oversampling rate higher than eight(2^3)
    	if (prsOsr > DPS310__OSR_SE)
    	{
            ret = writeByteBitfield(registers[PRS_SE], 1U);
            if (ret != DPS__SUCCEEDED)return ret;
    	}
    	else
    	{
            ret = writeByteBitfield(registers[PRS_SE], 0U);
            if (ret != DPS__SUCCEEDED)return ret;
    	}
    	return ret;
    }
    dps_err_t DPS310::readcoeffs()
    {
        //acqire raw coefficient value
        dps_err_t ret = readBlock(coeffBlock, buffer_);
        if(ret != DPS__SUCCEEDED)return ret;
        
        uint32_t calib0 = (((uint32_t)(buffer_[0]) << 4)) | (((uint32_t)(buffer_[1]) >> 4) & 0x0F);
        m_c0Half_ = convert_complement<uint32_t,12>(calib0)/2U;
        
        uint32_t calib1 = (((uint32_t)buffer_[1] & 0x0F) << 8) | (uint32_t)(buffer_[2]);
        m_c1_ = convert_complement<uint32_t,12>(calib1);

        uint32_t calib00 = (((uint32_t)buffer_[3]) << 12) | ((uint32_t)(buffer_[4]) << 4) | (((uint32_t)(buffer_[5]) >> 4) & 0x0F);
        m_c00_ = convert_complement<uint32_t,20>(calib00);
        uint32_t calib10 = (((uint32_t)buffer_[5] & 0x0F) << 16) | ((uint32_t)(buffer_[6]) << 8) | (uint32_t)(buffer_[7]);
        m_c10_ = convert_complement<uint32_t,20>(calib10);
        
        uint32_t calib01 = ((uint32_t)(buffer_[8]) << 8) | (uint32_t)(buffer_[9]);
        m_c01_ = convert_complement<uint32_t,16>(calib01);
        
        uint32_t calib11 = ((uint32_t)(buffer_[10]) << 8) | (uint32_t)(buffer_[11]);
        m_c11_ = convert_complement<uint32_t,16>(calib11);
        uint32_t calib20 = ((uint32_t)(buffer_[12]) << 8) | (uint32_t)(buffer_[13]);
        m_c20_ = convert_complement<uint32_t,16>(calib20);
        uint32_t calib21 = ((uint32_t)(buffer_[14]) << 8) | (uint32_t)(buffer_[15]);
        m_c21_ = convert_complement<uint32_t,16>(calib21);
        uint32_t calib30 = ((uint32_t)(buffer_[16]) << 8) | (uint32_t)(buffer_[17]);
        m_c30_ = convert_complement<uint32_t,16>(calib30);
        return ret;
    }
    float DPS310::calcTemp(int32_t raw)
    {
        float temp = raw;

	    //scale temperature according to scaling table and oversampling
	    temp /= scaling_facts[m_tempOsr_];

	    //update last measured temperature
	    //it will be used for pressure compensation
	    m_lastTempScal_ = temp;

	    //Calculate compensated temperature
	    temp = m_c0Half_ + m_c1_ * temp;

	    return temp;
    }

	float DPS310::calcPressure(int32_t raw)
    {
        float prs = raw;

	    //scale pressure according to scaling table and oversampling
	    prs /= scaling_facts[m_prsOsr_];

	    //Calculate compensated pressure
	    prs = m_c00_ + prs * (m_c10_ + prs * (m_c20_ + prs * m_c30_)) + m_lastTempScal_ * (m_c01_ + prs * (m_c11_ + prs * m_c21_));

	    //return pressure
	    return prs;
    }
} // namespace dps

