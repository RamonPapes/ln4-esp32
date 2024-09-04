#include "MUX_ADC.hpp"

MUX_ADC::MUX_ADC(Gpio &S0, Gpio &S1, Gpio &S2, Adc &PIN)
    : m_S0(S0), m_S1(S1), m_S2(S2), m_PIN(PIN),
        channel_0(*this),
        channel_1(*this),
        channel_2(*this),
        channel_3(*this),
        channel_4(*this),
        channel_5(*this),
        channel_6(*this),
        channel_7(*this) {}

void MUX_ADC::init() {}

MUX_ADC::channel_MUX_ADC::channel_MUX_ADC(MUX_ADC &mux)
    : Adc(), m_mux(mux)
{
    m_id = m_mux.m_id_mult++;
}

void MUX_ADC::channel_MUX_ADC::setAttenuation(adc_atten_t atten) 
{
    m_mux.m_S0.write(m_id & 0b001);
    m_mux.m_S1.write(m_id & 0b010);
    m_mux.m_S2.write(m_id & 0b100);

    m_mux.m_PIN.setAttenuation(atten);
}

void MUX_ADC::channel_MUX_ADC::setWidth(adc_bits_width_t width) 
{
    m_mux.m_S0.write(m_id & 0b001);
    m_mux.m_S1.write(m_id & 0b010);
    m_mux.m_S2.write(m_id & 0b100);

    m_mux.m_PIN.setWidth(width);
}

void MUX_ADC::channel_MUX_ADC::init() {}

int MUX_ADC::channel_MUX_ADC::getVoltage()
{
    m_mux.m_S0.write(m_id & 0b001);
    m_mux.m_S1.write(m_id & 0b010);
    m_mux.m_S2.write(m_id & 0b100);

    return m_mux.m_PIN.getVoltage();
}

int MUX_ADC::channel_MUX_ADC::get()
{
    m_mux.m_S0.write(m_id & 0b001);
    m_mux.m_S1.write(m_id & 0b010);
    m_mux.m_S2.write(m_id & 0b100);

    return m_mux.m_PIN.get();
}