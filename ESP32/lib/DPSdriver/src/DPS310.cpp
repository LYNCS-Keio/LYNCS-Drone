#include "DPS310.hpp"
#include "DPS310K.hpp"
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
namespace dps
{

    DPS310::DPS310(dps_bus_t *bus) : DPS(bus),
                                     tmp_ext_flag_(true),
                                     tmp_over_sampling_rate_(1),
                                     tmp_rate_(0),
                                     measure_tontrol_(0x07)
    {
    }

    esp_err_t DPS310::initiarize(){
        uint8_t TMP_CFG = 0x00;
        uint8_t MEAS_CTRL = 0xC0;
        uint8_t CFG_REG = 0x00;
        uint8_t TMP_COEF_SRCE = 0x00;

        TMP_CFG |= (tmp_ext_flag_ << 7);
        TMP_CFG |= (tmp_rate_ << 4);
        TMP_COEF_SRCE |= (tmp_ext_flag_ << 7);
        
        MEAS_CTRL |= measure_tontrol_;

        switch (tmp_over_sampling_rate_)
        {
        case 1:
            tmp_scale_factor_ = SCALE_FACTOR_1;
            TMP_CFG |= 0x00;
            break;
        case 2:
            tmp_scale_factor_ = SCALE_FACTOR_2;
            TMP_CFG |= 0x01;
            break;
        case 4:
            tmp_scale_factor_ = SCALE_FACTOR_4;
            TMP_CFG |= 0x02;
            break;
        case 8:
            tmp_scale_factor_ = SCALE_FACTOR_8;
            TMP_CFG |= 0x03;
            break;
        case 16:
            tmp_scale_factor_ = SCALE_FACTOR_16;
            TMP_CFG |= 0x04;
            CFG_REG |= 0x08;
            break;
        case 32:
            tmp_scale_factor_ = SCALE_FACTOR_32;
            TMP_CFG |= 0x05;
            CFG_REG |= 0x08;
            break;
        case 64:
            tmp_scale_factor_ = SCALE_FACTOR_64;
            TMP_CFG |= 0x06;
            CFG_REG |= 0x08;
            break;
        case 128:
            tmp_scale_factor_ = SCALE_FACTOR_128;
            TMP_CFG |= 0x07;
            CFG_REG |= 0x08;
            break;
        default:
            tmp_scale_factor_ = SCALE_FACTOR_1;
            TMP_CFG |= 0x00;
            break;
        }

        //acqire raw coefficient value
        if(DPS_ERR_CHECK(readBytes(REG_COEF,11,buffer_)))return err_;
        uint16_t calib0 = ((buffer_[0] << 4) & 0xFF0) | ((buffer_[1] >> 4) & 0x00F);
        uint16_t calib1 = ((buffer_[1] << 8) & 0xF00) | buffer_[2];
        c0_ = convert_complement<uint16_t,12>(calib0);
        c1_ = convert_complement<uint16_t,12>(calib1);

        //set configuration
		if(DPS_ERR_CHECK(writeByte(REG_TMP_CFG,TMP_CFG)))return err_;//TMP_CFG : temparature measurement configuration
		if(DPS_ERR_CHECK(writeByte(REG_MEAS_CFG,MEAS_CTRL)))return err_;//MEAS_CTRL  : temparature measurement configuration
		if(DPS_ERR_CHECK(writeByte(REG_CFG_REG,CFG_REG)))return err_;//CFG_REG;
        if(DPS_ERR_CHECK(writeByte(REG_TMP_COEF_SRCE,TMP_COEF_SRCE)))return err_;//TMP_COEF_SRCE 
		return err_;
	}

    esp_err_t DPS310::temperature(float &T_comp){

        //prepare
        if(DPS_ERR_CHECK(writeByte(REG_MEAS_CFG,0x02)))return err_;

        //acqire raw temperature value
        if(DPS_ERR_CHECK(readBytes(REG_TMP_B2,3,buffer_)))return err_;
        uint32_t temp = ((buffer_[0] << 16) & 0xFF0000) | ((buffer_[1] << 8) & 0x00FF00) | (buffer_[2]);

        float T_raw_sc = float(convert_complement<uint32_t,24>(temp))/tmp_scale_factor_;
        printf("T=%x\n",temp);
        printf("---------converted\n");
        printf("calib0=%d\n",c0_);
        printf("calib1=%d\n",c1_);
        printf("T=%f\n",T_raw_sc);
        T_comp = float(c0_)*0.5 + T_raw_sc*float(c1_);
        
        return err_;
    }
} // namespace dps

