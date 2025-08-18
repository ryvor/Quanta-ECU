#include "fuel.h"
#include "sensors_mcp3208.h"
#include "crank_decoder.h"
#include "scheduler.h"
#include "tables.h"
#include "config.h"

static float req_fuel = 5.0f; // ms base
static bool injA=false, injB=false;

void fuel_init(void){injA=injB=false;}

void fuel_update(void){
    if(!crank_has_sync()) return;
    float rpm=crank_rpm();
    float kpa=sensor_map_kpa();
    float ve = table_lookup(ve_table, rpm, kpa);
    float pw = req_fuel * (ve/100.0f);
    float angle = crank_angle_deg();
    if(angle<10.0f){injA=injB=false;}
    if(!injA && angle>=ecu_config.tdc_offset_deg){
        scheduler_set_injection(true, ecu_config.tdc_offset_deg, pw);
        injA=true;
    }
    if(!injB && angle>=180.0f+ecu_config.tdc_offset_deg){
        scheduler_set_injection(false, 180.0f+ecu_config.tdc_offset_deg, pw);
        injB=true;
    }
}
