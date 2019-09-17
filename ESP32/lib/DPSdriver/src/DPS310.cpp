#include "DPS310.hpp"
#include "DPS310K.hpp"
#include "../util/dps_const.hpp"
#include "../util/dps310_config.hpp"
#include <stdio.h>

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

    DPS310::DPS310(dps_bus_t *bus, int cs_pin_num) : DPS(bus),
    tmp_over_sampling_rate_(1),
    prs_over_sampling_rate_(1)
    {
        
    }
    esp_err_t DPS310::flushFIFO(){
        writeByteBitfield(registers[FIFO_EN],1U);
        return err_;
    }
    dps_err_t DPS310::initiarize(){
        
        if (DPS_ERR_CHECK(readByteBitfield(registers[PROD_ID], &m_productID)))
        {
            m_initFail = 1U;
            return DPS__FAIL_INIT_FAILED;
        }
        if (DPS_ERR_CHECK(readByteBitfield(registers[REV_ID], &m_revisionID)))
        {
            m_initFail = 1U;
            return DPS__FAIL_INIT_FAILED;
        }
        //find out which temperature sensor is calibrated with coefficients...
	    if (DPS_ERR_CHECK(readByteBitfield(registers[TEMP_SENSORREC], &m_tempSensor_)))
        {
            m_initFail = 1U;
            return DPS__FAIL_INIT_FAILED;
        }

        //...and use this sensor for temperature measurement
        if (DPS_ERR_CHECK(writeByteBitfield(registers[TEMP_SENSOR],m_tempSensor_)))
        {
		    m_initFail = 1U;
            return DPS__FAIL_INIT_FAILED;
        }

        //read coefficients
	    if (DPS_ERR_CHECK(readcoeffs()))
	    {
	    	m_initFail = 1U;
            return DPS__FAIL_INIT_FAILED;
	    }
        //set to standby for further configuration
	    standby();
	    //set measurement precision and rate to standard values;
	    configTemp(DPS__MEASUREMENT_RATE_4, tmp_over_sampling_rate_);
	    configPressure(DPS__MEASUREMENT_RATE_4, prs_over_sampling_rate_);
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
        return DPS__SUCCEEDED;
	}

    esp_err_t DPS310::readcoeffs()
    {
        //acqire raw coefficient value
        if(DPS_ERR_CHECK(readBlock(coeffBlock, buffer_)))return err_;
        
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
        return err_;
    }
    float DPS310::calcTemp(int32_t raw)
    {
        float temp = raw;

	    //scale temperature according to scaling table and oversampling
	    temp /= scaling_facts[m_tempOsr];

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
	    prs /= scaling_facts[m_prsOsr];

	    //Calculate compensated pressure
	    prs = m_c00_ + prs * (m_c10_ + prs * (m_c20_ + prs * m_c30_)) + m_lastTempScal_ * (m_c01_ + prs * (m_c11_ + prs * m_c21_));

	    //return pressure
	    return prs;
    }
} // namespace dps

