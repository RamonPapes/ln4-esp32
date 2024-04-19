#include "GPIO/gpio.hpp"

Gpio pin2(GPIO_NUM_2);

void portela(Gpio my_pin, void * args){
    printf("Hello World!!\n");
}

extern "C" void app_main() 
{
    pin2.init();
    pin2.interrupt(GPIO_INTR_NEGEDGE, portela);

    while(1) vTaskDelay(1);
}