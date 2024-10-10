#include "devices.hpp"
#include "drivers.hpp"
#include "util.hpp"

Adc sensor[8] = {
    Adc(ADC1_CHANNEL_0),
    Adc(ADC1_CHANNEL_3),
    Adc(ADC1_CHANNEL_6),
    Adc(ADC1_CHANNEL_7),
    Adc(ADC1_CHANNEL_4),
    Adc(ADC1_CHANNEL_5),
    Adc(ADC2_CHANNEL_8),
    Adc(ADC2_CHANNEL_9)
};

PWM AIN1(GPIO_NUM_23, LEDC_TIMER_12_BIT);
PWM AIN2(GPIO_NUM_22, LEDC_TIMER_12_BIT);
PWM BIN1(GPIO_NUM_21, LEDC_TIMER_12_BIT);
PWM BIN2(GPIO_NUM_19, LEDC_TIMER_12_BIT);

DRV8833 motor1(AIN1, AIN2);
DRV8833 motor2(BIN1, BIN2);

Driver_Drv8833 driver(motor1, motor2);


extern "C" void app_main() 
{
    sensor[0].init(-0.375, -0.5, 2040, 3770);
    sensor[1].init(-0.25, -0.375, 2200, 3620);
    sensor[2].init(-0.125, -0.25, 2390, 3630);
    sensor[3].init(0, -0.125, 2340, 3430);
    sensor[4].init(0, 0.125, 2040, 3120);
    sensor[5].init(0.125, 0.25, 1980, 3160);
    sensor[6].init(0.25, 0.375, 1990, 3790);
    sensor[7].init(0.375, 0.5, 1980, 3590);

    driver.init();

    driver.set_max_power(0.5);

    float direction;

    while (1)
    {
        direction = 0;
        for (size_t i = 0; i < 8; i++) direction += sensor[i].read();
        driver.arcade_driver(0.25+abs(direction)*0.75, direction);
        printlnf("diferencial: %f", direction);
        vTaskDelay(1);
    }
}