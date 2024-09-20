
#include "servo.hpp"

float servo_mode[4] = {-1, 1, 0.214, 2.79};

servo::servo(PWM &Pin) : m_Pin(Pin) {}

void servo::init()
{
    if(m_has_init) return;
    
    m_Pin.init(0, 20);

    m_max_input = servo_mode[0];
    m_min_input = servo_mode[1];

    m_max_output = servo_mode[2];
    m_min_output = servo_mode[3];

    m_has_init = true;
}

void servo::set_max_power(float value)
{
    if(!m_has_init) return;

    if(value > 1) value = 1;
    else if(value < -1) value = -1;

    m_max_power = value;
}

float servo::get_max_power()
{
    if(!m_has_init) return 0;

    return m_max_power;
}

void servo::write(float value)
{
    if(!m_has_init) return;

    m_Pin.write(calculate_PWM(value*m_max_power));
}

float servo::read()
{
    if(!m_has_init) return 0;

    return inv_calculate_PWM(m_Pin.getDuty())/m_max_power;
}

void servo::set_power(float value)
{
    if(!m_has_init) return;

    if(value > m_max_input) value = m_max_input;
    if(value < m_min_input) value = m_min_input;
    
    m_power = value;
}

float servo::get_power()
{
    if(!m_has_init) return 0;

    return m_power;
}

void servo::front()
{
    if(!m_has_init) return;

    m_Pin.write(calculate_PWM(m_power*m_max_power));
}

void servo::back()
{
    if(!m_has_init) return;

    m_Pin.write(calculate_PWM(-m_power*m_max_power));
}

void servo::stop()
{
    if(!m_has_init) return;

    m_Pin.write(calculate_PWM(0));
}


float servo::calculate_PWM(float data)
{
    if(data > m_max_input) data = m_max_input;
    if(data < m_min_input) data = m_min_input;

    float coeficiente_angular = (m_max_output - m_min_output)/(m_max_input - m_min_input);
    return (data - m_min_input)*coeficiente_angular + m_min_output;
}

float servo::inv_calculate_PWM(float data)
{
    float coeficiente_angular = (m_max_output - m_min_output)/(m_max_input - m_min_input);
    return (data - m_min_output)/coeficiente_angular + m_min_input;
}
