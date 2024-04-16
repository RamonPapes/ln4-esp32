#include <stdlib.h>
#include "gpio.hpp"
#include "driver/gpio.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/FreeRTOS.h"

bool init_itr = false;

gpio::gpio(gpio_num_t pin)
{
    m_pin = pin;
    m_pulldown = GPIO_PULLDOWN_DISABLE;
    m_pullup = GPIO_PULLUP_DISABLE;
}

gpio::gpio(gpio_num_t pin, gpio_pullup_t pullup, gpio_pulldown_t pulldown)
{
    m_pin = pin;
    m_pullup = pullup;
    m_pulldown = pulldown;
}

gpio *m_gpio[GPIO_NUM_MAX];

void gpio::init()
{
    gpio_config_t config = {
        .pin_bit_mask = 1 << m_pin,
        .mode = GPIO_MODE_INPUT_OUTPUT,
        .pull_up_en = m_pullup,
        .pull_down_en = m_pulldown,
    };

    gpio_config(&config);
}

void gpio::write(bool value)
{
    gpio_set_level(m_pin, value);
}
bool gpio::read()
{
    return gpio_get_level(m_pin);
}
void gpio::toggle()
{
    bool value = this->read();
    value = !value;
    gpio_set_level(m_pin, value);
}

static QueueHandle_t gpio_evt_queue = NULL;

static void IRAM_ATTR gpio_isr_handler(void *arg)
{
    uint32_t gpio_num = (uint32_t)arg;
    xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
}

static void gpio_task_interrupt(void *arg)
{
    uint32_t gpio_num;
    for (;;)
    {
        if (xQueueReceive(gpio_evt_queue, &gpio_num, portMAX_DELAY))
        {
            if (m_gpio[gpio_num]->m_func == nullptr)
                continue;
            m_gpio[gpio_num]->m_func(*m_gpio[gpio_num], m_gpio[gpio_num]->m_args);
        }
    }
}

void gpio::interrupt(gpio_int_type_t intr_type, void (*func)(gpio self, void *args), void *args)
{
    m_gpio[m_pin] = this;
    m_func = func;
    m_args = args;

    gpio_set_intr_type(m_pin, intr_type);

    if (!init_itr)
    {
        gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));

        xTaskCreate(gpio_task_interrupt, "gpio_task_interrupt", 2048, NULL, 10, NULL);

        gpio_install_isr_service(0);
    }

    init_itr = true;

    gpio_isr_handler_add(m_pin, gpio_isr_handler, (void *)m_pin);
}