#ifndef CRANK_DECODER_H
#define CRANK_DECODER_H
#include <stdbool.h>
#include <stdint.h>

void crank_decoder_init(void);
void crank_decoder_on_edge(uint32_t timestamp_us);
bool crank_has_sync(void);
float crank_rpm(void);
float crank_angle_deg(void);

#endif
