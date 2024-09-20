#ifndef MUX_ADC_HPP
#define MUX_ADC_HPP

#include "ADC/ADC.hpp"
#include "GPIO/gpio.hpp"

class MUX_ADC
{
    protected:
        Gpio &m_S0;
        Gpio &m_S1;
        Gpio &m_S2;
        Adc &m_PIN;

        uint8_t m_id_mult = 0; 

        bool m_has_init = false;
        
    private:
        class channel_MUX_ADC : public Adc
        {
            private:
                uint8_t m_id;
                MUX_ADC &m_mux;
            public:

            channel_MUX_ADC(MUX_ADC &mux);
            
            void setAttenuation(adc_atten_t atten);
            void setWidth(adc_bits_width_t width);
            void init();
            int getVoltage();
            int get();
        };

    public:
        MUX_ADC(Adc &PIN, Gpio &S0, Gpio &S1, Gpio &S2);

        void init();

        channel_MUX_ADC channel_0;
        channel_MUX_ADC channel_1;
        channel_MUX_ADC channel_2;
        channel_MUX_ADC channel_3;
        channel_MUX_ADC channel_4;
        channel_MUX_ADC channel_5;
        channel_MUX_ADC channel_6;
        channel_MUX_ADC channel_7;
};




#endif