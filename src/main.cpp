#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "GPIO/gpio.hpp"

extern "C" void app_main() 
{
    Gpio pin(GPIO_NUM_2);
    pin.init();

    while (1)
    {
        uint8_t val = pin.read();
        printf("\n\tLeitura:\t%d\n", val);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
    
}