#include "rotor.hpp"

extern const std::vector<int> pins{PWM_1, PWM_2, PWM_3, PWM_4};
extern const mcpwm_config_t pwm_conf = {50,0,0,MCPWM_DUTY_MODE_0,MCPWM_UP_COUNTER};

const int ROTOR_MIN_PULSEWIDTH = 1100;    //Minimum pulse width in microsecond
const int ROTOR_MAX_PULSEWIDTH = 1800;    //Maximum pulse width in microsecond

const int PWM_1 = 15;
const int PWM_2 = 4;
const int PWM_3 = 16;
const int PWM_4 = 17;
    
int Rotor::rotorPinInit() {
    static int i = 0;

    if ((i + pins.size()) > 12) { return(-1); }
    
    for(i=0; i<pins.size(); i++){
        if(i<6){
            if (mcpwm_gpio_init(unit_array.at(0), signal_array.at(i), pins.at(i)) != ESP_OK) {
                return(-11);
            }
            pinconf[pins.at(i)] = {unit_array.at(0), timer_array.at(int(i/2)), opr_array.at(i%2)};
        }
        else {
            if (mcpwm_gpio_init(unit_array.at(1), signal_array.at(i-6), pins.at(i)) != ESP_OK) {
                return(-11);
            }
            pinconf[pins.at(i)] = {unit_array.at(1), timer_array.at(int((i-6)/2)), opr_array.at(i%2)};
        }
    }
    
    for(i=0; i<(pins.size()/2); i++){
        if(i<3){
            if (mcpwm_init(unit_array.at(0), timer_array.at(i%3), &pwm_conf) != ESP_OK) {
                return(-12);
            }
        }
        else{
            if (mcpwm_init(unit_array.at(1), timer_array.at(i%3), &pwm_conf) != ESP_OK) {
                return(-12);
            }
        }
    }
    return(0);
};

void Rotor::rotorCalib() {
    for (int pw = ROTOR_MIN_PULSEWIDTH; pw <= ROTOR_MAX_PULSEWIDTH; pw += 1) { // sweep from MIN to MAX
        Rotor::rotorAnyOutput(PWM_1, pw);
        Rotor::rotorAnyOutput(PWM_2, pw);
        Rotor::rotorAnyOutput(PWM_3, pw);
        Rotor::rotorAnyOutput(PWM_4, pw);
        vTaskDelay(5/portTICK_RATE_MS);
    }
    for (int pw = ROTOR_MAX_PULSEWIDTH; pw >= ROTOR_MIN_PULSEWIDTH; pw -= 1) { // sweep from MAX to MIN
        Rotor::rotorAnyOutput(PWM_1, pw);
        Rotor::rotorAnyOutput(PWM_2, pw);
        Rotor::rotorAnyOutput(PWM_3, pw);
        Rotor::rotorAnyOutput(PWM_4, pw);
        vTaskDelay(5/portTICK_RATE_MS);
    }
    vTaskDelay(7000/portTICK_RATE_MS);
};

int Rotor::rotorAnyOutput(int pin, int pulse_width) {
    if (mcpwm_set_duty_in_us(pinconf[pin].unit, pinconf[pin].timer, pinconf[pin].opr, pulse_width) != ESP_OK) {
        return(-1);
    }
    return(0);
};