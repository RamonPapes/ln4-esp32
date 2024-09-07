#ifndef MUX_GPIO_HPP
#define MUX_GPIO_HPP

#include "GPIO/gpio.hpp"

class Mux_GPIO
{
protected:
    Gpio &m_S0;
    Gpio &m_S1;
    Gpio &m_S2;
    Gpio &m_PIN;

    uint8_t m_id_mult = 0;

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

public:
    Mux_GPIO(Gpio &PIN, Gpio &S0, Gpio &S1, Gpio &S2);

    void init();

    channel_MUX_GPIO channel_0;
    channel_MUX_GPIO channel_1;
    channel_MUX_GPIO channel_2;
    channel_MUX_GPIO channel_3;
    channel_MUX_GPIO channel_4;
    channel_MUX_GPIO channel_5;
    channel_MUX_GPIO channel_6;
    channel_MUX_GPIO channel_7;
};

#endif