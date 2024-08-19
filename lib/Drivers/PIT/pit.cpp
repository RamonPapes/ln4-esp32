#include "pit.hpp"

void Pit::init()
{
    #pragma GCC diagnostic ignored "-Wmissing-field-initializers"
    gptimer_config_t gptimer_config = {
        .clk_src = GPTIMER_CLK_SRC_DEFAULT,
        .direction = GPTIMER_COUNT_UP,
        .resolution_hz = 1000000,
    };
    #pragma GCC diagnostic pop
    ESP_ERROR_CHECK(gptimer_new_timer(&gptimer_config, &gptimer));
    ESP_ERROR_CHECK(gptimer_enable(gptimer));
}

void Pit::start()
{
    ESP_ERROR_CHECK(gptimer_start(gptimer));
}

void Pit::stop()
{
    ESP_ERROR_CHECK(gptimer_stop(gptimer));
}

void Pit::write(uint64_t countsToPerform)
{
    uint64_t currentPitCount = get();

    Timer.countLimit = currentPitCount + countsToPerform;

    Timer.start_timer = currentPitCount;
}

void Pit::delay(uint64_t value)
{
    vTaskDelay(value / portTICK_PERIOD_MS);
}

void Pit::reset(){
    ESP_ERROR_CHECK(gptimer_set_raw_count(gptimer, 0));
}

bool Pit::read()
{
    uint64_t currentPitCount;

    currentPitCount = get();
    if (currentPitCount >= Timer.countLimit)
    {
        return true;
    }
    else
    {
        return false;
    }
}

uint64_t Pit::get()
{
    uint64_t currentPitCount;
    ESP_ERROR_CHECK(gptimer_get_raw_count(gptimer, &currentPitCount));

    return currentPitCount / 1000;
}