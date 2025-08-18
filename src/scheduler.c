#include "scheduler.h"
#include "pinmap.h"
#include "crank_decoder.h"
#include "pico/stdlib.h"

typedef struct {
    bool active;
    float fire_angle;
    float dwell_ms;
    bool dwell_on;
    uint32_t dwell_start;
    uint gpio;
} ign_event_t;

static ign_event_t ign[2];

typedef struct {
    bool active;
    float angle;
    float pw_ms;
    uint32_t start_ts;
    bool on;
    uint gpio;
} inj_event_t;

static inj_event_t inj[2];

void scheduler_init(void){
    gpio_init(PIN_IGN_A); gpio_set_dir(PIN_IGN_A, GPIO_OUT); gpio_put(PIN_IGN_A,0);
    gpio_init(PIN_IGN_B); gpio_set_dir(PIN_IGN_B, GPIO_OUT); gpio_put(PIN_IGN_B,0);
    gpio_init(PIN_INJ_A); gpio_set_dir(PIN_INJ_A, GPIO_OUT); gpio_put(PIN_INJ_A,0);
    gpio_init(PIN_INJ_B); gpio_set_dir(PIN_INJ_B, GPIO_OUT); gpio_put(PIN_INJ_B,0);
    ign[0].gpio=PIN_IGN_A; ign[1].gpio=PIN_IGN_B;
    inj[0].gpio=PIN_INJ_A; inj[1].gpio=PIN_INJ_B;
}

void scheduler_set_ignition(bool coil_a, float angle_deg, float dwell_ms){
    int i=coil_a?0:1;
    ign[i].active=true; ign[i].fire_angle=angle_deg; ign[i].dwell_ms=dwell_ms; ign[i].dwell_on=false;
}

void scheduler_set_injection(bool bank_a, float angle_deg, float pw_ms){
    int i=bank_a?0:1;
    inj[i].active=true; inj[i].angle=angle_deg; inj[i].pw_ms=pw_ms; inj[i].on=false;
}

void scheduler_update(void){
    float angle=crank_angle_deg();
    uint32_t now=to_us_since_boot(get_absolute_time());
    for(int i=0;i<2;i++){
        if(ign[i].active){
            float start_angle = ign[i].fire_angle - ign[i].dwell_ms * crank_rpm()/6000.0f; // approximate deg
            if(!ign[i].dwell_on && angle >= start_angle){
                gpio_put(ign[i].gpio,1); ign[i].dwell_on=true; ign[i].dwell_start=now;
            }
            if(ign[i].dwell_on && now - ign[i].dwell_start >= (uint32_t)(ign[i].dwell_ms*1000)){ 
                gpio_put(ign[i].gpio,0); ign[i].active=false; ign[i].dwell_on=false; }
        }
        if(inj[i].active){
            if(!inj[i].on && angle >= inj[i].angle){
                gpio_put(inj[i].gpio,1); inj[i].on=true; inj[i].start_ts=now;
            }
            if(inj[i].on && now - inj[i].start_ts >= (uint32_t)(inj[i].pw_ms*1000)){
                gpio_put(inj[i].gpio,0); inj[i].on=false; inj[i].active=false;
            }
        }
    }
}
