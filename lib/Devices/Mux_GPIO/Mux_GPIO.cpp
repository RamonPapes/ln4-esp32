#include "Mux_GPIO.hpp"

Mux_GPIO::Mux_GPIO(Gpio &PIN, Gpio &S0, Gpio &S1, Gpio &S2)
    : m_S0(S0), m_S1(S1), m_S2(S2), m_PIN(PIN),
        channel_0(*this),
        channel_1(*this),
        channel_2(*this),
        channel_3(*this),
        channel_4(*this),
        channel_5(*this),
        channel_6(*this),
        channel_7(*this) {}

void Mux_GPIO::init() {}

Mux_GPIO::channel_MUX_GPIO::channel_MUX_GPIO(Mux_GPIO &mux) 
    : Gpio(), m_mux(mux)
{
    m_id = m_mux.m_id_mult++;
}

void Mux_GPIO::channel_MUX_GPIO::init()
{}

void Mux_GPIO::channel_MUX_GPIO::write(bool value)
{
    m_mux.m_S0.write(m_id & 0b001);
    m_mux.m_S1.write(m_id & 0b010);
    m_mux.m_S2.write(m_id & 0b100);

    m_mux.m_PIN.write(value);
}

bool Mux_GPIO::channel_MUX_GPIO::read()
{
    m_mux.m_S0.write(m_id & 0b001);
    m_mux.m_S1.write(m_id & 0b010);
    m_mux.m_S2.write(m_id & 0b100);

    return m_mux.m_PIN.read();
}

void Mux_GPIO::channel_MUX_GPIO::toggle()
{
    m_mux.m_S0.write(m_id & 0b001);
    m_mux.m_S1.write(m_id & 0b010);
    m_mux.m_S2.write(m_id & 0b100);

    m_mux.m_PIN.toggle();
}