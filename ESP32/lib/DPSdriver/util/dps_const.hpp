#pragma once

namespace dps
{
enum dps_err_t
{
    DPS__SUCCEEDED = 0,
    DPS__FAIL_UNKNOWN = -1,
    DPS__FAIL_INIT_FAILED = -2,
    DPS__FAIL_TOOBUSY = -3,
    DPS__FAIL_UNFINISHED = -4
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
} // namespace dps
