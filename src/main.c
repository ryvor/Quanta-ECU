#include "pico/stdlib.h"
#include "pinmap.h"
#include "crank_decoder.h"
#include "scheduler.h"
#include "ignition.h"
#include "fuel.h"
#include "sensors_mcp3208.h"
#include "uart_cli.h"
#include "safety.h"
#include "config_store.h"

#ifdef SIM_TEETH
static bool sim_cb(repeating_timer_t *rt){
    static uint32_t ts=0;
    ts += 2000; // 500Hz tooth ~ 1000rpm
    crank_decoder_on_edge(ts);
    return true;
}
#endif

int main(){
    stdio_init_all();
    config_load_defaults();
    config_store_load();
    crank_decoder_init();
    scheduler_init();
    ignition_init();
    fuel_init();
    sensors_init();
    uart_cli_init();
    safety_init();
#ifdef SIM_TEETH
    static repeating_timer_t timer;
    add_repeating_timer_us(-2000, sim_cb, NULL, &timer);
#endif
    while(true){
        sensors_sample();
        safety_update();
        ignition_update();
        fuel_update();
        scheduler_update();
        uart_cli_task();
        sleep_ms(10);
    }
    return 0;
}
