class gpio
{
public:
    gpio(gpio_num_t pin);
    
    void init();
    void write(bool value);
    bool read();
    void toggle();
    void interrupt(void *func, void *args);

private:
    /* data */
};