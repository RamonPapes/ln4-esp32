#include "DRIVER_DRV8833/driver_drv8833.hpp"

#define diferencial(x, k) (1-2*pow(abs((float)x), (float)k))

Driver_Drv8833::Driver_Drv8833(DRV8833 &left, DRV8833 &right) : m_left(left), m_right(right)
{}

void Driver_Drv8833::init()
{
    m_left.init();
    m_right.init();
}

void Driver_Drv8833::limit_power(motor_t motor, float min, float max)
{
    if(motor == MOTOR_LEFT)
    {
        m_min_left = min;
        m_max_left = max;
    }else
    {
        m_min_right = min;
        m_max_right = max;
    }
}

void Driver_Drv8833::set_max_power(float max_power)
{
    m_left.set_max_power(max_power);
    m_right.set_max_power(max_power);
}

float Driver_Drv8833::get_max_power()
{
    return m_left.get_max_power();
}

void Driver_Drv8833::motor_driver(float motor_left, float motor_right)
{
    if(motor_left > 1) motor_left = 1;
    else if(motor_left < -1) motor_left = -1;

    if(motor_right > 1) motor_right = 1;
    else if(motor_right < -1) motor_right = -1;

    m_left.write(convert_power(motor_left, m_min_left, m_max_left));
    m_right.write(convert_power(motor_right, m_min_right, m_max_right));
}

void Driver_Drv8833::arcade_driver(float power, float direction, float k)
{
    if(power > 1) power = 1;
    else if(power < 0) power = 0;

    if(direction > 1) direction = 1;
    else if(direction < -1) direction = -1;

    m_power = power;
    m_direction = direction;

    if(direction >= 0)
    {
        m_left.write(convert_power(power, m_min_left, m_max_left));
        m_right.write(convert_power(diferencial(direction, k)*power, m_min_right, m_max_right));
    }else
    {
        m_left.write(convert_power(diferencial(direction, k)*power, m_min_right, m_max_right));
        m_right.write(convert_power(power, m_min_left, m_max_left));
    }
}

float Driver_Drv8833::get_left_power()
{
    return m_left.read();
}

float Driver_Drv8833::get_right_power()
{
    return m_right.read();
}

float Driver_Drv8833::get_power()
{
    return m_power;
}

float Driver_Drv8833::get_direction()
{
    return m_direction;
}

void Driver_Drv8833::set_power_move(float power_move)
{
    m_left.set_power(power_move);
    m_right.set_power(power_move);
}

float Driver_Drv8833::get_power_move()
{
    return m_left.get_power();
}

void Driver_Drv8833::front()
{
    m_left.front();
    m_right.front();
}
void Driver_Drv8833::back()
{
    m_left.back();
    m_right.back();
}
void Driver_Drv8833::left()
{
    m_left.back();
    m_right.front();
}
void Driver_Drv8833::right()
{
    m_left.front();
    m_right.back();
}
void Driver_Drv8833::stop()
{
    m_left.stop();
    m_right.stop();
}

float Driver_Drv8833::convert_power(float value, float min, float max)
{
    float coeficiente_angular = (max-min)/2;
    return (value+1)*coeficiente_angular+min;
}