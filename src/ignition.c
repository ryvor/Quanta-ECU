#include "ignition.h"
#include "sensors_mcp3208.h"
#include "crank_decoder.h"
#include "scheduler.h"
#include "tables.h"
#include "config.h"

static bool fired_a=false, fired_b=false;

void ignition_init(void){
    fired_a=fired_b=false;
}

void ignition_update(void){
    if(!crank_has_sync()) return;
    float rpm = crank_rpm();
    float kpa = sensor_map_kpa();
    float batt = sensor_batt_v();
    float adv = table_lookup(ignition_table, rpm, kpa);
    float dwell = ecu_config.dwell_base_ms * (ecu_config.batt_volt_nom / (batt>1?batt:ecu_config.batt_volt_nom));
    float angle = crank_angle_deg();
    if(angle < 10.0f){fired_a=false; fired_b=false;} // new revolution
    if(!fired_a && angle >= ecu_config.tdc_offset_deg){
        scheduler_set_ignition(true, adv + ecu_config.tdc_offset_deg, dwell);
        fired_a=true;
    }
    if(!fired_b && angle >= 180.0f + ecu_config.tdc_offset_deg){
        scheduler_set_ignition(false, adv + 180.0f + ecu_config.tdc_offset_deg, dwell);
        fired_b=true;
    }
}
