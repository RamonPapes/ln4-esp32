#ifndef DRV8833_HPP
#define DRV8833_HPP

#include "PWM/pwm.hpp"

class DRV8833
{
private:
    PWM &m_In1;
    PWM &m_In2;

    float m_power = 1;
    float m_max_power = 1;

    bool m_has_init = false;

public:
    DRV8833(PWM &In1, PWM &In2);

    void init();

    void set_max_power(float value);
    float get_max_power();

    void write(float value);
    float read();

    void set_power(float value);
    float get_power();

    void front();
    void back();
    void stop();
};

#endif