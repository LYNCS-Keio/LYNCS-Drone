#pragma once

#include <vector>
#include <array>
#include <unordered_map>
#include <esp_err.h>
#include <driver/mcpwm.h>

namespace esc
{


constexpr std::array<mcpwm_unit_t, 2> unit_array{MCPWM_UNIT_0, MCPWM_UNIT_1};
constexpr std::array<mcpwm_io_signals_t, 6> signal_array{MCPWM0A, MCPWM0B, MCPWM1A, MCPWM1B, MCPWM2A, MCPWM2B};
constexpr std::array<mcpwm_timer_t, 3> timer_array{MCPWM_TIMER_0, MCPWM_TIMER_1, MCPWM_TIMER_2};
constexpr std::array<mcpwm_operator_t, 2> opr_array{MCPWM_OPR_A, MCPWM_OPR_B};


struct pinInfo
{
    mcpwm_unit_t unit;
    mcpwm_timer_t timer;
    mcpwm_operator_t opr;
    
};


class ESCdriver
{
    public:
    ESCdriver();
    int initialize(std::vector<int>&, mcpwm_config_t&);
    int setDuty(int, float);
    int setDuty_in_us(int, int);

    private:
    std::unordered_map<int, pinInfo> pinconf;
    
};

} // namespace esc