#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gptimer.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct
    {
        uint64_t start_timer;   
        uint64_t countLimit;
    } driverPITParammeters_t;
    class Pit
    {

    public:
        void init();
        void start();
        void stop();
        void reset();
        void write();
        static void delay();
        bool read();
        uint64_t get();

    private:
        gptimer_handle_t gptimer = NULL;
        driverPITParammeters_t Timer;
    }

#ifdef __cplusplus
}
#endif