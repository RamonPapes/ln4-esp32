#ifndef PWM_HPP
#define PWM_HPP

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "math.h"

class PWM
{
private:
    /* data */
    ledc_timer_bit_t m_resolution;
    ledc_mode_t m_mode;
    ledc_timer_t m_timer;
    uint32_t m_freq_hz;
    gpio_num_t m_pin;
    ledc_channel_t m_channel;
public:
    PWM(gpio_num_t pin, ledc_timer_bit_t resolution);
    ~PWM();

    void init();
    void write(uint32_t duty);
    uint32_t getDuty();
};

#endif