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

    float m_max_input;
    float m_min_input;
    float m_input_1;
    float m_input_2;
    float m_output_1;
    float m_output_2;

    uint32_t calculate_duty(float duty);
    float inv_calculate_duty(uint32_t duty);
public:
    PWM(gpio_num_t pin, ledc_timer_bit_t resolution, uint32_t freq_hz = 0);

    void init(float max_input = 0, float min_input = 0, float input_1 = 0, float input_2 = 0, float output_1 = 0, float output_2 = 0);
    void write(float duty);
    float getDuty();
};

#endif