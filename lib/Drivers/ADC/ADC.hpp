#include "freertos/FreeRTOS.h";
#include "driver/adc.h";

#ifdef __cplusplus
extern "C"
{
#endif

    class Adc
    {
    public:
        Adc(adc1_channel_t channel, adc_bits_width_t width = ADC_WIDTH_BIT_12, adc_atten_t atten = ADC_ATTEN_DB_0);
        void setAttenuation(adc_atten_t atten);
        void setWidth(adc_bits_width_t width);
        void init();
        int getVoltage();
        int get();

    private:
        adc1_channel_t _channel;
        adc_atten_t _atten;      // Atenuação
        adc_bits_width_t _width; // Largura de bit
    }

#ifdef __cplusplus
}
#endif