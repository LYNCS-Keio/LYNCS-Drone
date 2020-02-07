#ifndef DRONE_LIB_ROTOR_
#define DRONE_LIB_ROTOR_

#include <array>
#include <vector>
#include <unordered_map>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_attr.h"

#include "driver/mcpwm.h"
#include "soc/mcpwm_reg.h"
#include "soc/mcpwm_struct.h"
 
extern const int ROTOR_MIN_PULSEWIDTH;    //Minimum pulse width in microsecond
extern const int ROTOR_MAX_PULSEWIDTH;    //Maximum pulse width in microsecond

extern const int PWM_1;
extern const int PWM_2;
extern const int PWM_3;
extern const int PWM_4;

extern const std::vector<int> pins;
extern const mcpwm_config_t pwm_conf;

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

class Rotor {
public:
    int rotorPinInit();    //allocate PWM to GPIO pins
    int rotorAnyOutput(int pin, int pulse_width);   //control rotors by pin number & pulse_width
    void rotorCalib();    //calibrate rotors

private:
    std::unordered_map<int, pinInfo> pinconf;
};
#endif