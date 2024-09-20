#include "DRV8833.hpp"

DRV8833::DRV8833(PWM &In1, PWM &In2) : m_In1(In1), m_In2(In2)
{}

void DRV8833::init()
{
    if(m_has_init) return;

    m_In1.init(0, 1);
    m_In2.init(0, 1);

    m_has_init = true;
}

void DRV8833::set_max_power(float value)
{
    if(!m_has_init) return;

    if(value > 1) value = 1;
    if(value < 0) value = 0;

    m_max_power = value;
}

float DRV8833::get_max_power()
{
    if(!m_has_init) return 0;

    return m_max_power;
}

void DRV8833::write(float value)
{
    if(!m_has_init) return;

    if(value > 1) value = 1;
    else if(value < -1) value = -1;

    if(value > 0)
    {
        m_In1.write(value*m_max_power);
        m_In2.write(0);
    }
    else if(value == 0)
    {
        m_In1.write(0);
        m_In2.write(0);
    }
    else
    {
        m_In1.write(0);
        m_In2.write(-value*m_max_power);
    }
}

float DRV8833::read()
{
    if(!m_has_init) return 0;

    float value;

    value = m_In1.getDuty()/m_max_power;
    if(value > 0) return value;

    value = m_In2.getDuty()/m_max_power;
    if(value > 0) return -value;

    return 0;

}

void DRV8833::set_power(float value)
{
    if(!m_has_init) return;

    if(value > 1) value = 1;
    if(value < -1) value = -1;
    
    m_power = value;
}

float DRV8833::get_power()
{
    if(!m_has_init) return 0;

    return m_power;
}

void DRV8833::front()
{
    if(!m_has_init) return;

    write(m_power);
}

void DRV8833::back()
{
    if(!m_has_init) return;

    write(-m_power);
}

void DRV8833::stop()
{
    if(!m_has_init) return;

    write(0);
}
