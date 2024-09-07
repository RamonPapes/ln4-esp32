
#include "servo.hpp"

float servo_mode[SERVO_QTY][4] = {{1, -1, 2.79, 0.214}, {90, -90, 2, 1}};

servo::servo(PWM &Pin) : m_Pin(Pin) {}

void servo::init(servo_mode_t mode)
{
    m_max_input = servo_mode[mode][0];
    m_min_input = servo_mode[mode][1];

    m_max_output = servo_mode[mode][2];
    m_min_output = servo_mode[mode][3];
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
    m_Pin.write(calculate_PWM(value*m_max_power));
}

float servo::read()
{
    return inv_calculate_PWM(m_Pin.getDuty())/m_max_power;
}

void servo::set_power(float value)
{
    if(value > m_max_input) value = m_max_input;
    if(value < m_min_input) value = m_min_input;
    
    m_power = value;
}

float servo::get_power()
{
    return m_power;
}

void servo::front()
{
    m_Pin.write(calculate_PWM(m_power*m_max_power));
}

void servo::back()
{
    m_Pin.write(calculate_PWM(-m_power*m_max_power));
}

void servo::stop()
{
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
