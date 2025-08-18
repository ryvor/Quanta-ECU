#include "config.h"

ecu_config_t ecu_config;

void config_load_defaults(void) {
    ecu_config.tdc_offset_deg = 0.0f;
    ecu_config.injector_cc_min = 250.0f;
    ecu_config.stoich_af = 14.7f;
    ecu_config.dwell_base_ms = 3.0f;
    ecu_config.batt_volt_nom = 14.0f;
}
