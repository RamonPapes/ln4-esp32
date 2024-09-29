#ifndef ADC_HPP
#define ADC_HPP

#include "freertos/FreeRTOS.h"
#include "driver/adc.h"

class Adc
{
protected:
    Adc();
public:
    Adc(adc1_channel_t channel);
    void init();
    int getVoltage();
    int get();

private:
    adc1_channel_t _channel;
    adc_atten_t _atten = ADC_ATTEN_DB_11;      // Atenuação
    adc_bits_width_t _width = ADC_WIDTH_BIT_12; // Largura de bit
};

#endif