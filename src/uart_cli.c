#include "uart_cli.h"
#include "pico/stdlib.h"
#include "crank_decoder.h"
#include "sensors_mcp3208.h"
#include <stdio.h>

void uart_cli_init(void){
    stdio_init_all();
}

void uart_cli_task(void){
    printf("RPM:%0.0f MAP:%0.1f TPS:%0.1f CLT:%0.1f IAT:%0.1f\n",crank_rpm(),sensor_map_kpa(),sensor_tps_pct(),sensor_clt_c(),sensor_iat_c());
}
