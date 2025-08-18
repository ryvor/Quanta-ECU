#ifndef SENSORS_MCP3208_H
#define SENSORS_MCP3208_H
#include <stdint.h>

void sensors_init(void);
void sensors_sample(void);
float sensor_map_kpa(void);
float sensor_clt_c(void);
float sensor_iat_c(void);
float sensor_tps_pct(void);
float sensor_batt_v(void);

#endif
