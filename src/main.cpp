#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "GPIO/gpio.hpp"
#include "PIT/pit.hpp"
#include "PWM/pwm.hpp"
#include "Servo/servo.hpp"


extern "C" void app_main() 
{
    servo motor1(GPIO_NUM_2);

    motor1.init();

    while (1)
    {
        motor1.front();
        Pit::delay(1000);
        motor1.stop();
        Pit::delay(1000);
        motor1.back();
        Pit::delay(1000);
        motor1.stop();
        Pit::delay(1000);
    }
}