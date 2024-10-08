#ifndef MUX_GPIO_HPP
#define MUX_GPIO_HPP

#include "GPIO/gpio.hpp"

enum enum_channel_gpio_t
{
    GPIO_CHANNEL_0,
    GPIO_CHANNEL_1,
    GPIO_CHANNEL_2,
    GPIO_CHANNEL_3,
    GPIO_CHANNEL_4,
    GPIO_CHANNEL_5,
    GPIO_CHANNEL_6,
    GPIO_CHANNEL_7,
    GPIO_CHANNEL_MAX
};

class Mux_GPIO
{
protected:
    Gpio &m_S0;
    Gpio &m_S1;
    Gpio &m_S2;
    Gpio &m_PIN;

    uint8_t m_id_mult = 0;

    bool m_has_init = false;

private:
    class channel_MUX_GPIO : public Gpio
    {
        private:
            uint8_t m_id;
            Mux_GPIO &m_mux;

        public:
            channel_MUX_GPIO(Mux_GPIO &mux);

            void init();

            void write(bool value);
            bool read();
            void toggle();
    };

    channel_MUX_GPIO m_channel[8] = {
        channel_MUX_GPIO(*this),
        channel_MUX_GPIO(*this),
        channel_MUX_GPIO(*this),
        channel_MUX_GPIO(*this),
        channel_MUX_GPIO(*this),
        channel_MUX_GPIO(*this),
        channel_MUX_GPIO(*this),
        channel_MUX_GPIO(*this)
    };

public:
    Mux_GPIO(Gpio &PIN, Gpio &S0, Gpio &S1, Gpio &S2);

    void init(gpio_mode_t mode = GPIO_MODE_INPUT_OUTPUT);

    void channel(Gpio &obj_channel, enum_channel_gpio_t num_channel);

    Gpio operator[](int valor)
    {
        return m_channel[valor];
    }
};

#endif