#ifndef SERVO_HPP
#define SERVO_HPP

#include "PWM/pwm.hpp"

class servo
{
    public:
        servo(gpio_num_t pin, ledc_timer_bit_t resolution = LEDC_TIMER_16_BIT, uint32_t freq_hz = 50, uint32_t duty_max = 9150, uint32_t duty_min = 700);

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

    private:

        PWM *m_pwm;

        gpio_num_t m_pin;
        ledc_timer_bit_t m_resolution;
        uint32_t m_freq_hz;
        uint32_t m_duty_max;
        uint32_t m_duty_min;
        uint32_t m_duty_stop;

        float m_power = 1;
        float m_max_power = 1;
};


#endif