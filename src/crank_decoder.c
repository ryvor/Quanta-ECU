#include "crank_decoder.h"
#include "config.h"
#include <stdio.h>

#define TEETH 60
#define MISSING 2

static uint32_t last_ts;
static uint32_t last_dt;
static bool synced=false;
static int tooth=0;
static float rpm_val=0;

void crank_decoder_init(void){
    last_ts=0; last_dt=0; synced=false; tooth=0; rpm_val=0;
}

void crank_decoder_on_edge(uint32_t ts){
    if(last_ts==0){last_ts=ts;return;}
    uint32_t dt=ts-last_ts; last_ts=ts;
    if(dt>last_dt*3/2){ // missing tooth
        synced=true; tooth=0;
    }else{
        if(synced){
            tooth=(tooth+1)% (TEETH-MISSING);
        }
    }
    last_dt=dt;
    if(dt>0){
        rpm_val=60e6f/(dt*(TEETH-MISSING));
    }
}

bool crank_has_sync(void){return synced;}

float crank_rpm(void){return rpm_val;}

float crank_angle_deg(void){
    return tooth*(360.0f/(TEETH-MISSING));
}
