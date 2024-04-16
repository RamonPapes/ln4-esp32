class gpio
{
public:
    void (*m_func)(gpio self, void *args);
    void *m_args;
    gpio(gpio_num_t pin);
    gpio(gpio_num_t pin, gpio_pullup_t pullup, gpio_pulldown_t pulldown);

    void init();
    void write(bool value);
    bool read();
    void toggle();
    void interrupt(gpio_int_type_t intr_type, void (*func)(gpio self, void *args) = nullptr, void *args);

private:
    /* data */
    gpio_num_t m_pin;
    gpio_pullup_t m_pullup;
    gpio_pulldown_t m_pulldown;
};