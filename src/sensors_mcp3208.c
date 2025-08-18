#include "sensors_mcp3208.h"
#include "pinmap.h"
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include <stdio.h>

static uint16_t raw[8];

void sensors_init(void) {
    spi_init(spi0, 1*1000*1000);
    gpio_set_function(PIN_SPI0_SCK, GPIO_FUNC_SPI);
    gpio_set_function(PIN_SPI0_MOSI, GPIO_FUNC_SPI);
    gpio_set_function(PIN_SPI0_MISO, GPIO_FUNC_SPI);
    gpio_init(PIN_SPI0_CS);
    gpio_set_dir(PIN_SPI0_CS, GPIO_OUT);
    gpio_put(PIN_SPI0_CS, 1);
}

static uint16_t mcp3208_read(uint8_t ch) {
    uint8_t tx[3];
    tx[0] = 0x06 | ((ch & 0x04)>>2); // start + single ended
    tx[1] = (ch & 0x03) << 6;
    tx[2] = 0;
    uint8_t rx[3];
    gpio_put(PIN_SPI0_CS, 0);
    spi_write_read_blocking(spi0, tx, rx, 3);
    gpio_put(PIN_SPI0_CS, 1);
    return ((rx[1] & 0x0F) << 8) | rx[2];
}

void sensors_sample(void) {
    for (int i=0;i<5;i++) raw[i]=mcp3208_read(i); // read first 5 channels
}

float sensor_map_kpa(void) {
    return 10.0f + (raw[0]/4095.0f)*95.0f;
}
float sensor_clt_c(void) {
    return 20.0f + (raw[1]/4095.0f)*80.0f;
}
float sensor_iat_c(void) {
    return 20.0f + (raw[2]/4095.0f)*80.0f;
}
float sensor_tps_pct(void) {
    return (raw[3]/4095.0f)*100.0f;
}
float sensor_batt_v(void) {
    return (raw[4]/4095.0f)*16.0f;
}
