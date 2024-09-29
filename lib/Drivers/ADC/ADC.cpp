#include "ADC.hpp";

#define D_MAX 4085
#define MAX_VOLTS 2450

Adc::Adc(adc1_channel_t channel)
    : _channel(channel) {}

void Adc::init()
{
    ESP_ERROR_CHECK(adc1_config_width(_width));
    ESP_ERROR_CHECK(adc1_config_channel_atten(_channel, _atten));
}

int Adc::get()
{
    return  adc1_get_raw(_channel); 
}

int Adc::getVoltage()
{
    return this->get() * MAX_VOLTS / D_MAX;
}