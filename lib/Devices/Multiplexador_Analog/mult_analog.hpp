#ifndef MULT_ANALOG_HPP
#define MULT_ANALOG_HPP

#include "ADC/ADC.hpp"
#include "GPIO/gpio.hpp"

class mult_analog
{
    private:

        class channel_mult_analog : Adc
        {
            public:
            
            Adc(adc1_channel_t channel, adc_bits_width_t width = ADC_WIDTH_BIT_12, adc_atten_t atten = ADC_ATTEN_DB_0);
            
            void setAttenuation(adc_atten_t atten);
            void setWidth(adc_bits_width_t width);
            void init();
            int getVoltage();
            int get();
        };

        Gpio *m_S0;
        Gpio *m_S1;
        Gpio *m_S2;
        Gpio *m_PIN;
        
    public:
        mult_analog(Gpio *S0, Gpio *S1, Gpio *S2, Adc *PIN);

        void init();

        channel_mult_analog channel_0;
        channel_mult_analog channel_1;
        channel_mult_analog channel_2;
        channel_mult_analog channel_3;
        channel_mult_analog channel_4;
        channel_mult_analog channel_5;
        channel_mult_analog channel_6;
        channel_mult_analog channel_7;
};




#endif