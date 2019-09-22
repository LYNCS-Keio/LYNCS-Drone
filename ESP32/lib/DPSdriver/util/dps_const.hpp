#pragma once
#include "dps_register.hpp"
namespace dps
{
///////////     common    ///////////
//sea level pressure
constexpr double DPS__SEA_LEVEL_PRESSURE = 1000.1;

// slave address same for 422 and 310 (to be proved for future sensors)
constexpr uint8_t DPS__RESULT_BLOCK_LENGTH = 3;

enum DPSMeasurementRate
{
    DPS__MEASUREMENT_RATE_1 = 0,
    DPS__MEASUREMENT_RATE_2,
    DPS__MEASUREMENT_RATE_4,
    DPS__MEASUREMENT_RATE_8,
    DPS__MEASUREMENT_RATE_16,
    DPS__MEASUREMENT_RATE_32,
    DPS__MEASUREMENT_RATE_64,
    DPS__MEASUREMENT_RATE_128
};

enum DPSOversamplingRate
{
    DPS__OVERSAMPLING_RATE_1 = 0,
    DPS__OVERSAMPLING_RATE_2,
    DPS__OVERSAMPLING_RATE_4,
    DPS__OVERSAMPLING_RATE_8,
    DPS__OVERSAMPLING_RATE_16,
    DPS__OVERSAMPLING_RATE_32,
    DPS__OVERSAMPLING_RATE_64,
    DPS__OVERSAMPLING_RATE_128
};
//we use 0.1 ms units for time calculations, so 10 units are one millisecond
constexpr uint8_t DPS__BUSYTIME_SCALING = 10U;

// status code
enum dps_err_t
{
    DPS__SUCCEEDED = 0,
    DPS__FAIL_UNKNOWN = -1,
    DPS__FAIL_INIT_FAILED = -2,
    DPS__FAIL_TOOBUSY = -3,
    DPS__FAIL_UNFINISHED = -4,
    DPS__FAIL_CANNOT_WRITE_REG = -5,
    DPS__FAIL_COMMUNICATION = -6
};

enum Mode
{
    IDLE = 0x00,
    CMD_PRS = 0x01,
    CMD_TEMP = 0x02,
    CMD_BOTH = 0x03, // only for DPS422
    CONT_PRS = 0x05,
    CONT_TMP = 0x06,
    CONT_BOTH = 0x07
};

enum RegisterBlocks_e
{
    PRS = 0, // pressure value
    TEMP,    // temperature value
};

const RegBlock_t registerBlocks[2] = {
    {0x00, 3},
    {0x03, 3},
};
/**
 * @brief registers for configuration and flags; these are the same for both 310 and 422, might need to be adapted for future sensors
 * 
 */
enum Config_Registers_e
{
    TEMP_MR = 0, // temperature measure rate
    TEMP_OSR,    // temperature measurement resolution
    PRS_MR,      // pressure measure rate
    PRS_OSR,     // pressure measurement resolution
    MSR_CTRL,    // measurement control
    FIFO_EN,

    TEMP_RDY,
    PRS_RDY,
    INT_FLAG_FIFO,
    INT_FLAG_TEMP,
    INT_FLAG_PRS,
};

const RegMask_t config_registers[] = {
    {0x07, 0x70, 4}, // TEMP_MR
    {0x07, 0x07, 0}, // TEMP_OSR
    {0x06, 0x70, 4}, // PRS_MR
    {0x06, 0x07, 0}, // PRS_OSR
    {0x08, 0x07, 0}, // MSR_CTRL
    {0x09, 0x02, 1}, // FIFO_EN
    {0x08, 0x20, 5}, // TEMP_RDY
    {0x08, 0x10, 4}, // PRS_RDY
    {0x0A, 0x04, 2}, // INT_FLAG_FIFO
    {0x0A, 0x02, 1}, // INT_FLAG_TEMP
    {0x0A, 0x01, 0}, // INT_FLAG_PRS
};
} // namespace dps
