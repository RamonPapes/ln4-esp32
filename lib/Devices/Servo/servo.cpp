
#include "servo.hpp"

servo::servo(gpio_num_t pin, ledc_timer_bit_t resolution, uint32_t freq_hz, uint32_t duty_max, uint32_t duty_min)
{
    m_pin = pin;
    m_resolution = resolution;
    m_freq_hz = freq_hz;
    m_duty_max = duty_max;
    m_duty_min = duty_min;
}


void servo::init()
{
    m_pwm = new PWM(m_pin, m_resolution, m_freq_hz);

    m_pwm->init();

}

void servo::set_max_power(float value)
{
    if(value > 1) value = 1;
    else if(value < -1) value = -1;

    m_max_power = value;
}

float servo::get_max_power()
{
    return m_max_power;
}

void servo::write(float value)
{
    if(value > 1) value = 1;
    else if(value < -1) value = -1;

    uint32_t buf = (m_duty_max - m_duty_min)*((m_max_power*value + 1)/2) + m_duty_min;

    m_pwm->write(buf);
}

float servo::read()
{
    float buf = ((((float)m_pwm->getDuty() - m_duty_min)/(m_duty_max - m_duty_min))*2 - 1)/m_max_power;

    return buf;
}

void servo::set_power(float value)
{
    if(value > 1) value = 1;
    else if(value < -1) value = -1;
    
    m_power = value;
}

float servo::get_power()
{
    return m_power;
}

void servo::front()
{
    uint32_t buf = (((m_duty_max - m_duty_min)*(m_max_power*m_power + 1)/2) + m_duty_min);

    m_pwm->write(buf);
}

void servo::back()
{
    uint32_t buf = ((m_duty_max - m_duty_min)*((1 - m_max_power*m_power)/2) + m_duty_min);

    m_pwm->write(buf);
}

void servo::stop()
{
    uint32_t buf = (m_duty_max + m_duty_min)/2;

    m_pwm->write(buf);
}

