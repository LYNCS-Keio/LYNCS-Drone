#include "ESCdriver.hpp"
namespace esc
{

ESCdriver::ESCdriver(){}

int ESCdriver::initialize(std::vector<int>& pins, mcpwm_config_t& conf)
{
    static int i = 0;
    if ((i + pins.size()) > 12) { return(-1); }
    
    for(i=0; i<pins.size(); i++){
        if(i<6){
            if (mcpwm_gpio_init(unit_array.at(0), signal_array.at(i), pins.at(i)) != ESP_OK) {
                return(-11);
            }
            pinconf[pins.at(i)] = {unit_array.at(0), timer_array.at(int(i/2)), opr_array.at(i%2)};
       
        } else {
            if (mcpwm_gpio_init(unit_array.at(1), signal_array.at(i-6), pins.at(i)) != ESP_OK) {
                return(-11);
            }
            pinconf[pins.at(i)] = {unit_array.at(1), timer_array.at(int((i-6)/2)), opr_array.at(i%2)};
        
        }
    }
    
    for(i=0; i<(pins.size()/2); i++){
        if(i<3){
            if (mcpwm_init(unit_array.at(0), timer_array.at(i%3), &conf) != ESP_OK) {
                return(-12);
            }

        }else{
            if (mcpwm_init(unit_array.at(1), timer_array.at(i%3), &conf) != ESP_OK) {
                return(-12);
            }
        
        }
    }

    return(0);

}

int ESCdriver::setDuty(int pin, float duty)
{
    if (mcpwm_set_duty(pinconf[pin].unit, pinconf[pin].timer, pinconf[pin].opr, duty) != ESP_OK) {
        return(-1);
    }

    return(0);

}

int ESCdriver::setDuty_in_us(int pin, int width)
{
    if (mcpwm_set_duty_in_us(pinconf[pin].unit, pinconf[pin].timer, pinconf[pin].opr, width) != ESP_OK) {
        return(-1);
    }

    return(0);

}

} // namespace esc
