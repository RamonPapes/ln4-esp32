#include "ADC.hpp";

#define D_MAX 4085
Adc::Adc(adc1_channel_t channel, adc_bits_width_t width, adc_atten_t atten)
    : _channel(channel), _width(width), _atten(atten) {}

void Adc::init()
{
    ESP_ERROR_CHECK(adc1_config_width(_width));
    ESP_ERROR_CHECK(adc1_config_channel_atten(_channel, _atten));
}

int Adc::get()
{
    return  ESP_ERROR_CHECK(adc1_get_raw(_channel)); 
}

int Adc::getVoltage()
{
    int maxVoltage;
    if (_atten == ADC_ATTEN_DB_0)
    {
        maxVoltge = 950;
    }
    else if (_atten == ADC_ATTEN_DB_2_5)
    {
        maxVoltage = 1250;
    }
    else if (_atten == ADC_ATTEN_DB_6)
    {
        maxVoltage = 1750;
    }
    else if (atten == ADC_ATTEN_DB_11)
    {
        maxVoltage = 2450;
    }

    return this->get() * maxVoltage / D_MAX;
}

void ADC::setAttenuation(adc_atten_t atten)
{
    _atten = atten;
    ESP_ERROR_CHECK(adc1_config_channel_atten(_channel, _atten));
}

void ADC::setWidth(adc_bits_width_t width)
{
    _width = width;
    ESP_ERROR_CHECK(adc1_config_width(_width));
}