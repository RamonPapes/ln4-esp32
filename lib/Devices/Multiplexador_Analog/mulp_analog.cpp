#include "mult_analog.hpp"

mult_analog::mult_analog(Gpio *S0, Gpio *S1, Gpio *S2, Adc *PIN)
{
    m_S0 = S0;
    m_S1 = S1;
    m_S2 = S2;
    m_PIN = PIN;

    channel_0.hello_world();
}

Adc(adc1_channel_t channel, adc_bits_width_t width = ADC_WIDTH_BIT_12, adc_atten_t atten = ADC_ATTEN_DB_0);
void setAttenuation(adc_atten_t atten);
void setWidth(adc_bits_width_t width);
void init();
int getVoltage();
int get();