#pragma once

#include "SPIbus.hpp"

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
    protected:
        uint8_t buffer_[16];     /*!< Commom buffer for temporary data */
        esp_err_t err_;
    public:             
        MPU(mpu_bus_t& bus,mpu_addr_handle_t addr);
        ~MPU();
        virtual esp_err_t initialize() = 0;
        //! \name Read / Write
        //! Functions to perform direct read or write operation(s) to registers.
        //! \{
            esp_err_t readBit(uint8_t regAddr, uint8_t bitNum, uint8_t* data);
            esp_err_t readBits(uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t* data);
            esp_err_t readByte(uint8_t regAddr, uint8_t* data);
            esp_err_t readBytes(uint8_t regAddr, size_t length, uint8_t* data);
            esp_err_t writeBit(uint8_t regAddr, uint8_t bitNum, uint8_t data);
            esp_err_t writeBits(uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data);
            esp_err_t writeByte(uint8_t regAddr, uint8_t data);
            esp_err_t writeBytes(uint8_t regAddr, size_t length, const uint8_t* data);
    };

    /*! Read a single bit from a register*/
    inline esp_err_t MPU::readBit(uint8_t regAddr, uint8_t bitNum, uint8_t* data)
    {
        return err_ = bus_->readBit(addr_, regAddr, bitNum, data);
    }
    /*! Read a range of bits from a register */
    inline esp_err_t MPU::readBits(uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t* data)
    {
        return err_ = bus_->readBits(addr_, regAddr, bitStart, length, data);
    }
    /*! Read a single register */
    inline esp_err_t MPU::readByte(uint8_t regAddr, uint8_t* data)
    {
        return err_ = bus_->readByte(addr_, regAddr, data);
    }
    /*! Read data from sequence of registers */
    inline esp_err_t MPU::readBytes(uint8_t regAddr, size_t length, uint8_t* data)
    {
        return err_ = bus_->readBytes(addr_, regAddr, length, data);
    }
    /*! Write a single bit to a register */
    inline esp_err_t MPU::writeBit(uint8_t regAddr, uint8_t bitNum, uint8_t data)
    {
        return err_ = bus_->writeBit(addr_, regAddr, bitNum, data);
    }
    /*! Write a range of bits to a register */
    inline esp_err_t MPU::writeBits(uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data)
    {
        return err_ = bus_->writeBits(addr_, regAddr, bitStart, length, data);
    }
    /*! Write a value to a register */
    inline esp_err_t MPU::writeByte(uint8_t regAddr, uint8_t data)
    {
        return err_ = bus_->writeByte(addr_, regAddr, data);
    }
    /*! Write a sequence to data to a sequence of registers */
    inline esp_err_t MPU::writeBytes(uint8_t regAddr, size_t length, const uint8_t* data)
    {
        return err_ = bus_->writeBytes(addr_, regAddr, length, data);
    }
} // namespace mpu
