#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "driver/ledc.h"

class pwm
{
private:
    /* data */
public:
    pwm(gpio_num_t pin, ledc_timer_bit_t resolution);
    ~pwm();

    void init();
    void write(uint32_t duty);
    uint32_t read();
};
