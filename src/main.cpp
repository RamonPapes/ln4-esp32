#include "PIT/pit.hpp"
#include "Servo/servo.hpp"
#include "Multiplexador_Analog/mult_analog.hpp"


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