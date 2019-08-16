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
                                     tmp_ext_flag_(true),
                                     tmp_over_sampling_rate_(1),
                                     tmp_rate_(0),
                                     measure_tontrol_(0x07)
    {
        
    }
    esp_err_t DPS310::flushFIFO(){
        writeByteBitfield(registers[FIFO_EN],1U);
        return err_;
    }
    void DPS310::initiarize(){
        
        if (DPS_ERR_CHECK(readByteBitfield(registers[PROD_ID], &m_productID)))
        {
            m_initFail = 1U;
            return;
        }
        if (DPS_ERR_CHECK(readByteBitfield(registers[REV_ID], &m_revisionID)))
        {
            m_initFail = 1U;
            return;
        }
        //find out which temperature sensor is calibrated with coefficients...
	    if (DPS_ERR_CHECK(readByteBitfield(registers[TEMP_SENSORREC], &m_tempSensor)))
        {
            m_initFail = 1U;
            return;
        }
        //...and use this sensor for temperature measurement
        if (DPS_ERR_CHECK(writeByteBitfield(registers[TEMP_SENSOR],m_tempSensor)))
        {
		    m_initFail = 1U;
		    return;
        }
        //read coefficients
	    if (DPS_ERR_CHECK(readcoeffs()))
	    {
	    	m_initFail = 1U;
	    	return;
	    }
        //set to standby for further configuration
	    standby();

	    //set measurement precision and rate to standard values;
	    configTemp(DPS__MEASUREMENT_RATE_4, tmp_over_sampling_rate_);
	    configPressure(DPS__MEASUREMENT_RATE_4, tmp_over_sampling_rate_);

        switch (tmp_over_sampling_rate_)
        {
        case 1:
            tmp_scale_factor_ = SCALE_FACTOR_1;
            break;
        case 2:
            tmp_scale_factor_ = SCALE_FACTOR_2;
            break;
        case 3:
            tmp_scale_factor_ = SCALE_FACTOR_4;
            break;
        case 4:
            tmp_scale_factor_ = SCALE_FACTOR_8;
            break;
        case 5:
            tmp_scale_factor_ = SCALE_FACTOR_16;
            break;
        case 6:
            tmp_scale_factor_ = SCALE_FACTOR_32;
            break;
        case 7:
            tmp_scale_factor_ = SCALE_FACTOR_64;
            break;
        case 8:
            tmp_scale_factor_ = SCALE_FACTOR_128;
            break;
        default:
            tmp_scale_factor_ = SCALE_FACTOR_1;
            break;
        }

	}

    esp_err_t DPS310::readcoeffs()
    {
        //acqire raw coefficient value
        if(DPS_ERR_CHECK(readBytes(REG_COEF,11,buffer_)))return err_;
        uint32_t calib0 = (((uint32_t)(buffer_[0]) << 4)) | (((uint32_t)(buffer_[1]) >> 4) & 0x0F);
        m_c0Half_ = convert_complement<uint32_t,12>(calib0)/2U;
        uint32_t calib1 = (((uint32_t)buffer_[1] & 0x0F) << 8) | buffer_[2];
        m_c1_ = convert_complement<uint32_t,12>(calib1);
        return err_;
    }

    esp_err_t DPS310::temperature(float &T_comp)
    {

        //prepare
        if(DPS_ERR_CHECK(writeByte(REG_MEAS_CFG,0x02)))return err_;

        

        //acqire raw temperature value
        if(DPS_ERR_CHECK(readBytes(REG_TMP_B2,3,buffer_)))return err_;
        uint32_t temp = ((buffer_[0] << 16) & 0xFF0000) | ((buffer_[1] << 8) & 0x00FF00) | (buffer_[2]);

        float T_raw_sc = float(convert_complement<uint32_t,24>(temp))/tmp_scale_factor_;
        printf("T=%x\n",temp);
        printf("---------converted\n");
        printf("calib0/2=%d\n",m_c0Half_);
        printf("calib1=%d\n",m_c1_);
        printf("T=%f\n",T_raw_sc);
        T_comp = (float(m_c0Half_)) + T_raw_sc*float(m_c1_);
        
        return err_;
    }
} // namespace dps

