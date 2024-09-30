#include "devices.hpp"
#include "drivers.hpp"
#include "util.hpp"

Gpio pin16(GPIO_NUM_16);
Gpio pin17(GPIO_NUM_17);
Gpio pin15(GPIO_NUM_15);
Gpio pin2(GPIO_NUM_2);
Gpio pin4(GPIO_NUM_4);

Mux_GPIO sensorEsquerda(pin16, pin15, pin2, pin4);
Mux_GPIO sensorDireita(pin17, pin15, pin2, pin4);

extern "C" void app_main() 
{
    sensorEsquerda.init();
    sensorDireita.init();

    while (1)
    {
        bool valor = sensorEsquerda[0].read();
        printlnf("VALOR: %d", valor);
        Pit::delay(100);
    }
}