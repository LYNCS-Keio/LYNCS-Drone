/**
 * @file DPS.hpp
 * @brief Driver of DPS, a series of pressure sensor
 * 
 * "Dps310" represents Infineon's high-sensetive pressure and temperature sensor. 
 * It measures in ranges of 300 - 1200 hPa and -40 and 85 °C. 
 * The sensor can be connected via SPI or I2C. 
 * It is able to perform single measurements
 * or to perform continuous measurements of temperature and pressure at the same time, 
 * and stores the results in a FIFO to reduce bus communication. 
 * 
 * @version 0.1
 * @date 2019-09-20
 * 
 */
#pragma once

#include "SPIbus.hpp"
#include "../util/dps_register.hpp"
#include "../util/dps_const.hpp"

#define DPS_ERR_CHECK(x) (x)
/**
 * @brief dps name space
 * 
 */
namespace dps
{

typedef SPI_t dps_bus_t;
typedef spi_device_handle_t dps_addr_handle_t;
/**
 * @brief DPS class
 * This abstract class provides fundamental functions like read/write functions.
 */
class DPS
{
    private:
    /** Communication bus pointer, I2C / SPI */
    dps_bus_t* bus_;
    dps_addr_handle_t addr_;
    Mode m_opMode;

    protected:
    static const int32_t scaling_facts[];
    /** Common buffer for temporary data */
    uint8_t buffer_[18];
    dps_err_t setOpMode(Mode opMode);
    dps_err_t disableFIFO();
    dps_err_t standby();
    /** Temperature measurement rate*/
    uint8_t m_tempMr;
    /** Temperature oversampling rate*/
    uint8_t m_tempOsr;
    /** Pressure measurement rate*/
    uint8_t m_prsMr;
    /** Pressure oversampling rate*/
    uint8_t m_prsOsr;
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
    virtual dps_err_t flushFIFO() = 0;
    virtual dps_err_t readcoeffs() = 0;
    virtual dps_err_t configTemp(uint8_t tempMr, uint8_t tempOsr);
    virtual dps_err_t configPressure(uint8_t prs_mr, uint8_t prs_osr);
    //flags
	uint8_t m_initFail;
	uint8_t m_productID;
	uint8_t m_revisionID;
    DPS(){}

    public:
    DPS(dps_bus_t *bus) : bus_{bus}, m_dev_init_(false), buffer_{0}
    {}

    ~DPS()
    {
        bus_->removeDevice(addr_);
    }

    /**
     * @brief SPIbus initialization
     * 
     * @param spi_mode          [SPI mode (0 to 3)] 
     * @param clock_speed_hz    [Clock speed in Hz]
     * @param cs_io_num         [ChipSelect/SlaveSelect pin]
     * @return dps_err_t        [error code]
     */
    dps_err_t dev_init(uint8_t spi_mode, uint32_t clock_speed_hz, int cs_io_num);
    
    //! \name Read / Write
    //! Functions to perform direct read or write operation(s) to registers.
    //! \{
        dps_err_t readBit(uint8_t regAddr, uint8_t bitNum, uint8_t* data);
        dps_err_t readBits(uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t* data);
        dps_err_t readByte(uint8_t regAddr, uint8_t* data);
        dps_err_t readBytes(uint8_t regAddr, size_t length, uint8_t* data);
        dps_err_t readByteBitfield(RegMask_t regMask, uint8_t* data);
        dps_err_t readBlock(RegBlock_t regBlock, uint8_t* data);
        dps_err_t writeBit(uint8_t regAddr, uint8_t bitNum, uint8_t data);
        dps_err_t writeBits(uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data);
        dps_err_t writeByte(uint8_t regAddr, uint8_t data);
        dps_err_t writeBytes(uint8_t regAddr, size_t length, const uint8_t* data);
        dps_err_t writeByteBitfield(uint8_t regAddr, uint8_t mask, uint8_t shift, uint8_t data);
        dps_err_t writeByteBitfield(RegMask_t regMask, uint8_t data);
    ///! \}

    //! \name Measurement
    //! Functions to perform measurement of pressure or temperature.
    //! \{
        dps_err_t measureTempOnce(float &result, uint8_t oversamplingRate);
        dps_err_t measureTempOnce(float &result);
        dps_err_t measurePressureOnce(float &result, uint8_t oversamplingRate);
        dps_err_t measurePressureOnce(float &result);
        dps_err_t measureHeightOnce(float &result, uint8_t oversamplingRate);
    ///! \}
};

/*! Read a single bit from a register*/
inline dps_err_t DPS::readBit(uint8_t regAddr, uint8_t bitNum, uint8_t* data)
{
    if (DPS_ERR_CHECK(bus_->readBit(addr_, regAddr, bitNum, data)))return DPS__FAIL_COMMUNICATION;
    return DPS__SUCCEEDED;
}
/*! Read a range of bits from a register */
inline dps_err_t DPS::readBits(uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t* data)
{
    if (DPS_ERR_CHECK(bus_->readBits(addr_, regAddr, bitStart, length, data)))return DPS__FAIL_COMMUNICATION;
    return DPS__SUCCEEDED;
}
/*! Read a single register */
inline dps_err_t DPS::readByte(uint8_t regAddr, uint8_t* data)
{
    if (DPS_ERR_CHECK(bus_->readByte(addr_, regAddr, data)))return DPS__FAIL_COMMUNICATION;
    return DPS__SUCCEEDED;
}
/*! Read data from sequence of registers */
inline dps_err_t DPS::readBytes(uint8_t regAddr, size_t length, uint8_t* data)
{
    if (DPS_ERR_CHECK(bus_->readBytes(addr_, regAddr, length, data)))return DPS__FAIL_COMMUNICATION;
    return DPS__SUCCEEDED;
}
inline dps_err_t DPS::readByteBitfield(RegMask_t regMask, uint8_t* data)
{
    dps_err_t ret = readByte(regMask.regAddress,data);
    *data = ((*data) & regMask.mask) >> regMask.shift;
    return ret;
}
/*! Read data from sequence of registers */
inline dps_err_t DPS::readBlock(RegBlock_t regBlock, uint8_t* data){
    //mask regAddress
    regBlock.regAddress &= ~(0x80); //register address is 7bit
    return readBytes(regBlock.regAddress,regBlock.length,data);
}
/*! Write a single bit to a register */
inline dps_err_t DPS::writeBit(uint8_t regAddr, uint8_t bitNum, uint8_t data)
{
    if (DPS_ERR_CHECK(bus_->writeBit(addr_, regAddr, bitNum, data)))return DPS__FAIL_COMMUNICATION;
    return DPS__SUCCEEDED;
}
/*! Write a range of bits to a register */
inline dps_err_t DPS::writeBits(uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data)
{
    if (DPS_ERR_CHECK(bus_->writeBits(addr_, regAddr, bitStart, length, data)))return DPS__FAIL_COMMUNICATION;
    return DPS__SUCCEEDED;
}
/*! Write a value to a register */
inline dps_err_t DPS::writeByte(uint8_t regAddr, uint8_t data)
{
    if (DPS_ERR_CHECK(bus_->writeByte(addr_, regAddr, data)))return DPS__FAIL_COMMUNICATION;
    return DPS__SUCCEEDED;
}
/*! Write a sequence to data to a sequence of registers */
inline dps_err_t DPS::writeBytes(uint8_t regAddr, size_t length, const uint8_t* data)
{
    if (DPS_ERR_CHECK(bus_->writeBytes(addr_, regAddr, length, data)))return DPS__FAIL_COMMUNICATION;
    return DPS__SUCCEEDED;
}
/*! Write a value to register using masks*/
inline dps_err_t DPS::writeByteBitfield(uint8_t regAddr, uint8_t mask, uint8_t shift, uint8_t data)
{
    uint8_t old_data;
    dps_err_t ret = readByte(regAddr,&old_data);
    if (ret != DPS__SUCCEEDED)return ret;
    return writeByte(regAddr, ((uint8_t)old_data & ~mask) | ((data << shift) & mask));
}
inline dps_err_t DPS::writeByteBitfield(RegMask_t regMask, uint8_t data){
    return writeByteBitfield(regMask.regAddress, regMask.mask, regMask.shift, data);
}

} // namespace dps
