#include "MUX_ADC.hpp"

MUX_ADC::MUX_ADC(Adc &PIN, Gpio &S0, Gpio &S1, Gpio &S2)
    : m_S0(S0), m_S1(S1), m_S2(S2), m_PIN(PIN) {}

void MUX_ADC::init()
{
    if(m_has_init) return;

    m_PIN.init();
    m_S0.init(GPIO_MODE_OUTPUT);
    m_S1.init(GPIO_MODE_OUTPUT);
    m_S2.init(GPIO_MODE_OUTPUT);

    m_has_init = true;
}

void MUX_ADC::channel(Adc &obj_channel, enum_channel_adc_t num_channel)
{
    obj_channel = m_channel[num_channel];
}

MUX_ADC::channel_MUX_ADC::channel_MUX_ADC(MUX_ADC &mux)
    : Adc(), m_mux(mux)
{
    m_id = m_mux.m_id_mult++;
}

void MUX_ADC::channel_MUX_ADC::init() {}

int MUX_ADC::channel_MUX_ADC::readVolt()
{
    if(!m_mux.m_has_init) return 0;

    m_mux.m_S0.write(m_id & 0b001);
    m_mux.m_S1.write(m_id & 0b010);
    m_mux.m_S2.write(m_id & 0b100);

    return m_mux.m_PIN.readVolt();
}

int MUX_ADC::channel_MUX_ADC::read()
{
    if(!m_mux.m_has_init) return 0;

    m_mux.m_S0.write(m_id & 0b001);
    m_mux.m_S1.write(m_id & 0b010);
    m_mux.m_S2.write(m_id & 0b100);

    return m_mux.m_PIN.read();
}