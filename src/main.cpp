#include "PIT/pit.hpp"
#include "Servo/servo.hpp"
#include "Multiplexador/MUX_ADC.hpp"


extern "C" void app_main() 
{
    PWM pwm_servo(GPIO_NUM_2, LEDC_TIMER_16_BIT, 50);
    servo motor_1(pwm_servo);

    pwm_servo.init(20, 0);
    motor_1.init(SERVO_CONTINUO);

    while (1)
    {
        motor_1.front();
        Pit::delay(1000);
        motor_1.stop();
        Pit::delay(1000);
        motor_1.back();
        Pit::delay(1000);
        motor_1.stop();
        Pit::delay(1000);
    }
}