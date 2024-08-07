#include "pwm.hpp"

static ledc_timer_bit_t timer_resolution[LEDC_TIMER_MAX];
static uint8_t timer_lock[LEDC_TIMER_MAX];
static uint8_t channel_lock[LEDC_SPEED_MODE_MAX][LEDC_CHANNEL_MAX];


PWM::PWM(gpio_num_t pin, ledc_timer_bit_t resolution)
{
    m_pin = pin;
    m_resolution = resolution;
}

void PWM::init()
{
    //definindo frequencia
    m_freq_hz = 65536000/pow(2,(uint8_t)m_resolution);
    
    //definindo timer
    for (uint8_t i = 0; i < LEDC_TIMER_MAX; i++)
    {
        if (timer_resolution[i] == 0)
        {
            timer_resolution[i] = m_resolution;
            m_timer = (ledc_timer_t)i;
            break;
        }
        else if (timer_resolution[i] == m_resolution)
        {
            m_timer = (ledc_timer_t)i;
            break;
        }
    }

    //definindo modo e canal
    for(uint8_t mode = 0; mode < LEDC_SPEED_MODE_MAX; mode++)
    {
        for (uint8_t i = 0; i < LEDC_CHANNEL_MAX; i++)
        {
            if (channel_lock[mode][i] != 1)
            {
                channel_lock[mode][i] = 1;
                m_mode = (ledc_mode_t)mode;
                m_channel = (ledc_channel_t)i;
                break;
            }
        }
    }

    //construindo o timer
    if (timer_lock[m_timer] != 1)
    {
        timer_lock[m_timer] = 1;

        ledc_timer_config_t ledc_timer = {
            .speed_mode = m_mode,
            .duty_resolution = m_resolution,
            .timer_num = m_timer,
            .freq_hz = m_freq_hz,
            .clk_cfg = LEDC_USE_APB_CLK
        };
        ledc_timer_config(&ledc_timer);
    }

    //construindo o channel
    ledc_channel_config_t ledc_channel = {
        .gpio_num = m_pin,
        .speed_mode = m_mode,
        .channel = m_channel,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = m_timer,
        .duty = 0,
        .hpoint = 0
    };
    ledc_channel_config(&ledc_channel);
}

void PWM::write(uint32_t duty)
{
    ledc_set_duty(m_mode, m_channel, duty);
    ledc_update_duty(m_mode, m_channel);
}

uint32_t PWM::getDuty()
{
    return ledc_get_duty(m_mode, m_channel);
}