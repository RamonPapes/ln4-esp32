#include "ADC.hpp";

#define D_MAX 4085
Adc::Adc(adc1_channel_t channel, adc_bits_width_t width, adc_atten_t atten)
    : _channel(channel), _width(width), _atten(atten) {}

void Adc::init()
{
    adc1_config_width(_width);
    adc1_config_channel_atten(_channel, _atten);
}

int Adc::get()
{
    return adc1_get_raw(_channel);
}

int Adc::getVoltage()
{
    int maxVoltage;
    if (_atten == ADC_ATTEN_DB_0)
    {
        maxVoltge = 950 / 1000; // Convertendo de mV para V -> conferir isso com Portela.
    }
    else if (_atten == ADC_ATTEN_DB_2_5)
    {
        maxVoltage = 1250 / 1000;
    }
    else if (_atten == ADC_ATTEN_DB_6)
    {
        maxVoltage = 1750 / 1000;
    }
    else if (atten == ADC_ATTEN_DB_11)
    {
        maxVoltage = 2450 / 1000;
    }

    return adc1_get_raw() * maxVoltage / D_MAX;
}

void ADC::setAttenuation(adc_atten_t atten)
{
    _atten = atten;
    adc1_config_channel_atten(_channel, _atten);
}

void ADC::setWidth(adc_bits_width_t width)
{
    _width = width;
    adc1_config_width(_width);
}
