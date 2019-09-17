#pragma once

#include "SPIbus.hpp"
#include "../util/dps_register.hpp"
#include "../util/dps_const.hpp"
#include <math.h>

static float calc_height_sub(float P)
{
    float P_hP = P/100.0;
    const float k_const = 1.0/5.257;
    if (P_hP != 0)
    {
        float H_raw = pow(DPS__SEA_LEVEL_PRESSURE/P_hP,k_const);
        return H_raw;
    }
    return 0;
}

#define DPS_ERR_CHECK(x) (x)
namespace dps
{

    typedef SPI_t dps_bus_t;
    typedef spi_device_handle_t dps_addr_handle_t;
    
    class DPS
    {
    private:
        dps_bus_t* bus_;         /*!< Communication bus pointer, I2C / SPI */
        dps_addr_handle_t addr_;
        Mode m_opMode;
    protected:
        static const int32_t scaling_facts[DPS__NUM_OF_SCAL_FACTS];
        uint8_t buffer_[18];     /*!< Commom buffer for temporary data */
        esp_err_t err_;
        virtual esp_err_t flushFIFO() = 0;
        virtual esp_err_t readcoeffs() = 0;
        dps_err_t setOpMode(Mode opMode);
        esp_err_t disableFIFO();
        dps_err_t standby();
        uint8_t m_tempMr;       //Temperature measurement rate
        uint8_t m_tempOsr;      //Temperature oversampling rate
        uint8_t m_prsMr;        //Pressure measurement rate
        uint8_t m_prsOsr;         //Pressure oversampling rate
        dps_err_t startMeasureTempOnce(uint8_t oversamplingRate);
        dps_err_t startMeasureTempOnce();
        dps_err_t startMeasurePressureOnce(uint8_t oversamplingRate);
        dps_err_t startMeasurePressureOnce();
        dps_err_t getRawResult(int32_t *raw, RegBlock_t reg);
        dps_err_t getSingleResult(float &result);
        dps_err_t correctTemp();
        uint16_t calcBusyTime(uint16_t mr, uint16_t osr);
        //virtual functions
        virtual float calcTemp(int32_t raw) = 0;
        virtual float calcPressure(int32_t raw) = 0;
        virtual dps_err_t configTemp(uint8_t tempMr, uint8_t tempOsr);
        virtual dps_err_t configPressure(uint8_t prs_mr, uint8_t prs_osr);
        	//flags
	    uint8_t m_initFail;

	    uint8_t m_productID;
	    uint8_t m_revisionID;

        DPS(){}
    public:
        DPS(dps_bus_t *bus) : bus_{bus}, buffer_{0}, err_{ESP_OK}
        {}
        ~DPS();
        virtual esp_err_t dev_init(uint8_t spi_mode, uint32_t clock_speed_hz, int cs_io_num){return bus_->addDevice(spi_mode, clock_speed_hz, cs_io_num, &addr_);}
        //! \name Read / Write
        //! Functions to perform direct read or write operation(s) to registers.
        //! \{
            esp_err_t readBit(uint8_t regAddr, uint8_t bitNum, uint8_t* data);
            esp_err_t readBits(uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t* data);
            esp_err_t readByte(uint8_t regAddr, uint8_t* data);
            esp_err_t readBytes(uint8_t regAddr, size_t length, uint8_t* data);
            esp_err_t readByteBitfield(RegMask_t regMask, uint8_t* data);
            esp_err_t readBlock(RegBlock_t regBlock, uint8_t* data);
            esp_err_t writeBit(uint8_t regAddr, uint8_t bitNum, uint8_t data);
            esp_err_t writeBits(uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data);
            esp_err_t writeByte(uint8_t regAddr, uint8_t data);
            esp_err_t writeBytes(uint8_t regAddr, size_t length, const uint8_t* data);
            esp_err_t writeByteBitfield(uint8_t regAddr, uint8_t mask, uint8_t shift, uint8_t data);
            esp_err_t writeByteBitfield(RegMask_t regMask, uint8_t data);
        //! \}
        dps_err_t measureTempOnce(float &result, uint8_t oversamplingRate);
        dps_err_t measureTempOnce(float &result);
        dps_err_t measurePressureOnce(float &result, uint8_t oversamplingRate);
        dps_err_t measurePressureOnce(float &result);
    };
    
    

    /*! Read a single bit from a register*/
    inline esp_err_t DPS::readBit(uint8_t regAddr, uint8_t bitNum, uint8_t* data)
    {
        return err_ = bus_->readBit(addr_, regAddr, bitNum, data);
    }
    /*! Read a range of bits from a register */
    inline esp_err_t DPS::readBits(uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t* data)
    {
        return err_ = bus_->readBits(addr_, regAddr, bitStart, length, data);
    }
    /*! Read a single register */
    inline esp_err_t DPS::readByte(uint8_t regAddr, uint8_t* data)
    {
        return err_ = bus_->readByte(addr_, regAddr, data);
    }
    /*! Read data from sequence of registers */
    inline esp_err_t DPS::readBytes(uint8_t regAddr, size_t length, uint8_t* data)
    {
        return err_ = bus_->readBytes(addr_, regAddr, length, data);
    }
    inline esp_err_t DPS::readByteBitfield(RegMask_t regMask, uint8_t* data)
    {
        readByte(regMask.regAddress,data);
        *data = ((*data) & regMask.mask) >> regMask.shift;
        return err_;
    }
    /*! Read data from sequence of registers */
    inline esp_err_t DPS::readBlock(RegBlock_t regBlock, uint8_t* data){
        //mask regAddress
	    regBlock.regAddress &= ~(0x80); //register address is 7bit
        readBytes(regBlock.regAddress,regBlock.length,data);
        return err_;
    }
    /*! Write a single bit to a register */
    inline esp_err_t DPS::writeBit(uint8_t regAddr, uint8_t bitNum, uint8_t data)
    {
        return err_ = bus_->writeBit(addr_, regAddr, bitNum, data);
    }
    /*! Write a range of bits to a register */
    inline esp_err_t DPS::writeBits(uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data)
    {
        return err_ = bus_->writeBits(addr_, regAddr, bitStart, length, data);
    }
    /*! Write a value to a register */
    inline esp_err_t DPS::writeByte(uint8_t regAddr, uint8_t data)
    {
        return err_ = bus_->writeByte(addr_, regAddr, data);
    }
    /*! Write a sequence to data to a sequence of registers */
    inline esp_err_t DPS::writeBytes(uint8_t regAddr, size_t length, const uint8_t* data)
    {
        return err_ = bus_->writeBytes(addr_, regAddr, length, data);
    }
    /*! Write a value to register using masks*/
    inline esp_err_t DPS::writeByteBitfield(uint8_t regAddr, uint8_t mask, uint8_t shift, uint8_t data)
    {
        uint8_t old_data;
        readByte(regAddr,&old_data);
        return err_ = writeByte(regAddr, ((uint8_t)old_data & ~mask) | ((data << shift) & mask));
    }
    inline esp_err_t DPS::writeByteBitfield(RegMask_t regMask, uint8_t data){
        return writeByteBitfield(regMask.regAddress, regMask.mask, regMask.shift, data);
    }

} // namespace dps
