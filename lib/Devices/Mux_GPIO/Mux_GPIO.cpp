#include "Mux_GPIO.hpp"

Mux_GPIO::Mux_GPIO(Gpio &PIN, Gpio &S0, Gpio &S1, Gpio &S2)
    : m_S0(S0), m_S1(S1), m_S2(S2), m_PIN(PIN) {}

void Mux_GPIO::init(gpio_mode_t mode)
{
    if(m_has_init) return;

    m_PIN.init(mode);
    m_S0.init(GPIO_MODE_OUTPUT);
    m_S1.init(GPIO_MODE_OUTPUT);
    m_S2.init(GPIO_MODE_OUTPUT);

    m_has_init = true;
}

void Mux_GPIO::channel(Gpio &obj_channel, enum_channel_t num_channel)
{
    obj_channel = m_channel[num_channel];
}

Mux_GPIO::channel_MUX_GPIO::channel_MUX_GPIO(Mux_GPIO &mux) 
    : Gpio(), m_mux(mux)
{
    m_id = m_mux.m_id_mult++;
}

void Mux_GPIO::channel_MUX_GPIO::init()
{}

void Mux_GPIO::channel_MUX_GPIO::write(bool value)
{
    if(!m_mux.m_has_init) return;

    m_mux.m_S0.write(m_id & 0b001);
    m_mux.m_S1.write(m_id & 0b010);
    m_mux.m_S2.write(m_id & 0b100);

    m_mux.m_PIN.write(value);
}

bool Mux_GPIO::channel_MUX_GPIO::read()
{
    if(!m_mux.m_has_init) return false;

    m_mux.m_S0.write(m_id & 0b001);
    m_mux.m_S1.write(m_id & 0b010);
    m_mux.m_S2.write(m_id & 0b100);

    return m_mux.m_PIN.read();
}

void Mux_GPIO::channel_MUX_GPIO::toggle()
{
    if(!m_mux.m_has_init) return;

    m_mux.m_S0.write(m_id & 0b001);
    m_mux.m_S1.write(m_id & 0b010);
    m_mux.m_S2.write(m_id & 0b100);

    m_mux.m_PIN.toggle();
}