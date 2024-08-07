#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "GPIO/gpio.hpp"
#include "PWM/pwm.hpp"


extern "C" void app_main() 
{
    PWM pin(GPIO_NUM_2, LEDC_TIMER_8_BIT);

    pin.init();

    while (1)
    {
        for (uint8_t i = 0; i < 255; i = i<<1 | 1)
        {
            pin.write(i);
            vTaskDelay(100/portTICK_PERIOD_MS);
        }
        for (uint8_t i = 255; i > 0; i = i>>1)
        {
            pin.write(i);
            vTaskDelay(100/portTICK_PERIOD_MS);
        }
        
    }
    
}