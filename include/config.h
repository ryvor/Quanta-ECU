#ifndef CONFIG_H
#define CONFIG_H
#include <stdint.h>

#define CYLINDERS 4
#define RPM_TABLE_SIZE 12
#define MAP_TABLE_SIZE 12

typedef struct {
    float tdc_offset_deg;     // degrees
    float injector_cc_min;    // cc/min
    float stoich_af;          // AFR
    float dwell_base_ms;      // base dwell at nominal voltage
    float batt_volt_nom;      // nominal battery voltage for dwell
} ecu_config_t;

extern ecu_config_t ecu_config;
void config_load_defaults(void);

#endif
