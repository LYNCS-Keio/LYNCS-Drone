#pragma once

#include "SPIbus.hpp"
#include "../util/mpu_const.hpp"
#include "../util/mpu_register.hpp"

#define MPU_ERR_CHECK(x) (x)

namespace mpu
{
    
    typedef SPI_t mpu_bus_t;
    typedef spi_device_handle_t mpu_addr_handle_t;

    class MPU
    {
    private:
    mpu_bus_t* bus_;         /*!< Communication bus pointer, I2C / SPI */
    mpu_addr_handle_t addr_;
    bool m_dev_init_;

    protected:

    /*!< Common buffer for temporary data */
    uint8_t buffer_[16];

    public:
    MPU(mpu_bus_t* bus);
    ~MPU();
    virtual mpu_err_t initialize() = 0;

    /**
     * @brief SPIbus initialization
     * 
     * @param spi_mode          [SPI mode (0 to 3)] 
     * @param clock_speed_hz    [Clock speed in Hz]
     * @param cs_io_num         [ChipSelect/SlaveSelect pin]
     * @return MPU_err_t        [error code]
     */
    mpu_err_t dev_init(uint8_t spi_mode, uint32_t clock_speed_hz, int cs_io_num)
    {
        if (m_dev_init_)
        {
            bus_->removeDevice(addr_);
        }
        
        if (MPU_ERR_CHECK(bus_->addDevice(spi_mode, clock_speed_hz, cs_io_num, &addr_)))return MPU__FAIL_COMMUNICATION;
        m_dev_init_ = true;
        return MPU__SUCCEEDED;
    }
    //! \name Read / Write
    //! Functions to perform direct read or write operation(s) to registers.
    //! \{
        mpu_err_t readBit(uint8_t regAddr, uint8_t bitNum, uint8_t* data);
        mpu_err_t readBits(uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t* data);
        mpu_err_t readByte(uint8_t regAddr, uint8_t* data);
        mpu_err_t readBytes(uint8_t regAddr, size_t length, uint8_t* data);
        mpu_err_t readByteBitfield(RegMask_t regMask, uint8_t* data);
        mpu_err_t readBlock(RegBlock_t regBlock, uint8_t* data);
        mpu_err_t writeBit(uint8_t regAddr, uint8_t bitNum, uint8_t data);
        mpu_err_t writeBits(uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data);
        mpu_err_t writeByte(uint8_t regAddr, uint8_t data);
        mpu_err_t writeBytes(uint8_t regAddr, size_t length, const uint8_t* data);
        mpu_err_t writeByteBitfield(uint8_t regAddr, uint8_t mask, uint8_t shift, uint8_t data);
        mpu_err_t writeByteBitfield(RegMask_t regMask, uint8_t data);
    ///! \}
    };


    /*! Read a single bit from a register*/
    inline mpu_err_t MPU::readBit(uint8_t regAddr, uint8_t bitNum, uint8_t* data)
    {
        if (MPU_ERR_CHECK(bus_->readBit(addr_, regAddr, bitNum, data)))return MPU__FAIL_COMMUNICATION;
        return MPU__SUCCEEDED;
    }
    /*! Read a range of bits from a register */
    inline mpu_err_t MPU::readBits(uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t* data)
    {
        if (MPU_ERR_CHECK(bus_->readBits(addr_, regAddr, bitStart, length, data)))return MPU__FAIL_COMMUNICATION;
        return MPU__SUCCEEDED;
    }
    /*! Read a single register */
    inline mpu_err_t MPU::readByte(uint8_t regAddr, uint8_t* data)
    {
        if (MPU_ERR_CHECK(bus_->readByte(addr_, regAddr, data)))return MPU__FAIL_COMMUNICATION;
        return MPU__SUCCEEDED;
    }
    /*! Read data from sequence of registers */
    inline mpu_err_t MPU::readBytes(uint8_t regAddr, size_t length, uint8_t* data)
    {
        if (MPU_ERR_CHECK(bus_->readBytes(addr_, regAddr, length, data)))return MPU__FAIL_COMMUNICATION;
        return MPU__SUCCEEDED;
    }
    inline mpu_err_t MPU::readByteBitfield(RegMask_t regMask, uint8_t* data)
    {
        mpu_err_t ret = readByte(regMask.regAddress,data);
        *data = ((*data) & regMask.mask) >> regMask.shift;
        return ret;
    }
    /*! Read data from sequence of registers */
    inline mpu_err_t MPU::readBlock(RegBlock_t regBlock, uint8_t* data){
        //mask regAddress
	    regBlock.regAddress &= ~(0x80); //register address is 7bit
        return readBytes(regBlock.regAddress,regBlock.length,data);
    }
    /*! Write a single bit to a register */
    inline mpu_err_t MPU::writeBit(uint8_t regAddr, uint8_t bitNum, uint8_t data)
    {
        if (MPU_ERR_CHECK(bus_->writeBit(addr_, regAddr, bitNum, data)))return MPU__FAIL_COMMUNICATION;
        return MPU__SUCCEEDED;
    }
    /*! Write a range of bits to a register */
    inline mpu_err_t MPU::writeBits(uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data)
    {
        if (MPU_ERR_CHECK(bus_->writeBits(addr_, regAddr, bitStart, length, data)))return MPU__FAIL_COMMUNICATION;
        return MPU__SUCCEEDED;
    }
    /*! Write a value to a register */
    inline mpu_err_t MPU::writeByte(uint8_t regAddr, uint8_t data)
    {
        if (MPU_ERR_CHECK(bus_->writeByte(addr_, regAddr, data)))return MPU__FAIL_COMMUNICATION;
        return MPU__SUCCEEDED;
    }
    /*! Write a sequence to data to a sequence of registers */
    inline mpu_err_t MPU::writeBytes(uint8_t regAddr, size_t length, const uint8_t* data)
    {
        if (MPU_ERR_CHECK(bus_->writeBytes(addr_, regAddr, length, data)))return MPU__FAIL_COMMUNICATION;
        return MPU__SUCCEEDED;
    }
    /*! Write a value to register using masks*/
    inline mpu_err_t MPU::writeByteBitfield(uint8_t regAddr, uint8_t mask, uint8_t shift, uint8_t data)
    {
        uint8_t old_data;
        mpu_err_t ret = readByte(regAddr,&old_data);
        if (ret != MPU__SUCCEEDED)return ret;
        return writeByte(regAddr, ((uint8_t)old_data & ~mask) | ((data << shift) & mask));
    }
    inline mpu_err_t MPU::writeByteBitfield(RegMask_t regMask, uint8_t data){
        return writeByteBitfield(regMask.regAddress, regMask.mask, regMask.shift, data);
    }

} // namespace mpu
