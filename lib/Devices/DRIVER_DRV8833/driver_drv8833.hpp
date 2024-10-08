#ifndef DRIVER_DRV8833_HPP
#define DRIVER_DRV8833_HPP

#include "DRV8833/DRV8833.hpp"
#include "util.hpp"

typedef enum
{
    MOTOR_LEFT,
    MOTOR_RIGHT
}motor_t;

class Driver_Drv8833
{
private:
    DRV8833 m_left;
    DRV8833 m_right;

    float m_min_left = 0;
    float m_max_left = 1;
    float m_min_right = 0;
    float m_max_right = 1;

    float m_max_power = 1;
    float m_power_move = 1;

    float m_motor_left = 0;
    float m_motor_right = 0;

    float m_power = 0;
    float m_direction = 0;

    float convert_power(float value, float min, float max);
public:
    Driver_Drv8833(DRV8833 &left, DRV8833 &right);

    void init();

    void limit_power(motor_t motor, float min, float max);

    void set_max_power(float max_power);
    float get_max_power();

    void motor_driver(float motor_left, float motor_right);
    void arcade_driver(float power, float direction, float k = 3);

    float get_left_power();
    float get_right_power();

    float get_power();
    float get_direction();

    void set_power_move(float power_move);
    float get_power_move();

    void front();
    void back();
    void left();
    void right();
    void stop();
};

#endif