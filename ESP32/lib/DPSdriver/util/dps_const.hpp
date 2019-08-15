#pragma once

namespace dps
{
    enum dps_err_t{
        DPS__SUCCEEDED = 0,
        DPS__FAIL_UNKNOWN = -1,
        DPS__FAIL_INIT_FAILED = -2,
        DPS__FAIL_TOOBUSY = -3,
        DPS__FAIL_UNFINISHED = -4
    };
} // namespace dps
