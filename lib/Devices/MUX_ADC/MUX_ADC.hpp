#ifndef MUX_ADC_HPP
#define MUX_ADC_HPP

#include "ADC/ADC.hpp"
#include "GPIO/gpio.hpp"

enum enum_channel_adc_t
{
    P_ADC_CHANNEL_0,
    P_ADC_CHANNEL_1,
    P_ADC_CHANNEL_2,
    P_ADC_CHANNEL_3,
    P_ADC_CHANNEL_4,
    P_ADC_CHANNEL_5,
    P_ADC_CHANNEL_6,
    P_ADC_CHANNEL_7,
    P_ADC_CHANNEL_MAX
};

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
        
        void init();
        int readVolt();
        int read();
    };

    channel_MUX_ADC m_channel[8] = {
        channel_MUX_ADC(*this),
        channel_MUX_ADC(*this),
        channel_MUX_ADC(*this),
        channel_MUX_ADC(*this),
        channel_MUX_ADC(*this),
        channel_MUX_ADC(*this),
        channel_MUX_ADC(*this),
        channel_MUX_ADC(*this)
    };

public:
    MUX_ADC(Adc &PIN, Gpio &S0, Gpio &S1, Gpio &S2);

    void init();

    void channel(Adc &obj_channel, enum_channel_adc_t num_channel);

    Adc operator[](int valor)
    {
        return m_channel[valor];
    }
};




#endif