#include "safety.h"
#include "pinmap.h"
#include "crank_decoder.h"
#include "pico/stdlib.h"

static ecu_state_t state = STATE_BOOT;

void safety_init(void){
    gpio_init(PIN_ENABLE);
    gpio_set_dir(PIN_ENABLE, GPIO_IN);
    gpio_pull_down(PIN_ENABLE);
    state = STATE_ARMED_IDLE;
}

bool safety_outputs_enabled(void){
    return state==STATE_CRANKING || state==STATE_RUNNING;
}

ecu_state_t safety_get_state(void){
    return state;
}

void safety_update(void){
    bool en = gpio_get(PIN_ENABLE);
    float rpm = crank_rpm();
    switch(state){
        case STATE_ARMED_IDLE:
            if(en && rpm>200) state=STATE_CRANKING;
            break;
        case STATE_CRANKING:
            if(!en) state=STATE_SHUTDOWN;
            else if(rpm>500) state=STATE_RUNNING;
            break;
        case STATE_RUNNING:
            if(!en || rpm<100) state=STATE_SHUTDOWN;
            break;
        case STATE_SHUTDOWN:
            if(!en) state=STATE_ARMED_IDLE;
            break;
        default: break;
    }
}
