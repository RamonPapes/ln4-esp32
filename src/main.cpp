#include "GPIO/gpio.hpp"

Gpio pin2(GPIO_NUM_2);

extern "C" void app_main() 
{
    pin2.init();

    while (1)
    {
        pin2.write(1);
        vTaskDelay(300/portTICK_PERIOD_MS);
        pin2.write(0);
        vTaskDelay(300/portTICK_PERIOD_MS);
    }
    
}