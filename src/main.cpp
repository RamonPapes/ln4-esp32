#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "GPIO/gpio.hpp"
#include "PIT/pit.hpp"
#include "PWM/pwm.hpp"


extern "C" void app_main() 
{
    PWM pin(GPIO_NUM_2, LEDC_TIMER_16_BIT, 50);

    pin.init();

    while (1)
    {
        //frente
        pin.write(6553);
        Pit::delay(1000);
        //parar
        pin.write(4915);
        Pit::delay(1000);
        //trás
        pin.write(3276);
        Pit::delay(1000);
        //parar
        pin.write(4915);
        Pit::delay(1000);
    }
    
}