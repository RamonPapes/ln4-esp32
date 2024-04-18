#include "gpio.hpp"

bool init_itr = false;

Gpio::Gpio(gpio_num_t pin)
{
    m_pin = pin;
    m_pulldown = GPIO_PULLDOWN_DISABLE;
    m_pullup = GPIO_PULLUP_DISABLE;
}

Gpio::Gpio(gpio_num_t pin, gpio_pullup_t pullup, gpio_pulldown_t pulldown)
{
    m_pin = pin;
    m_pullup = pullup;
    m_pulldown = pulldown;
}

void Gpio::init()
{
    gpio_config_t config = {
        .pin_bit_mask = 1ULL << m_pin,
        .mode = GPIO_MODE_INPUT_OUTPUT,
        .pull_up_en = m_pullup,
        .pull_down_en = m_pulldown,
        .intr_type = GPIO_INTR_DISABLE,
    };

    gpio_config(&config);
}

void Gpio::write(bool value)
{
    gpio_set_level(m_pin, value);
}
bool Gpio::read()
{
    return gpio_get_level(m_pin);
}
void Gpio::toggle()
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
    Gpio *m_gpio = (Gpio *)arg;
    for (;;)
    {
        if (xQueueReceive(gpio_evt_queue, &gpio_num, portMAX_DELAY))
        {
            if (m_gpio->m_func == nullptr)
                continue;
            m_gpio->m_func(*m_gpio, m_gpio->m_args);
        }
    }
}

void Gpio::interrupt(gpio_int_type_t intr_type, void (*func)(Gpio self, void *args), void *args)
{
    m_func = func;
    m_args = args;

    gpio_set_intr_type(m_pin, intr_type);

    if (!init_itr)
    {
        gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));

        xTaskCreate(gpio_task_interrupt, "gpio_task_interrupt", 2048, this, 10, NULL);

        gpio_install_isr_service(0);
    }

    init_itr = true;

    gpio_isr_handler_add(m_pin, gpio_isr_handler, (void *)m_pin);
}