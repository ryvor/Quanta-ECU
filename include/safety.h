#ifndef SAFETY_H
#define SAFETY_H
#include <stdbool.h>

typedef enum {
    STATE_BOOT,
    STATE_ARMED_IDLE,
    STATE_CRANKING,
    STATE_RUNNING,
    STATE_SHUTDOWN
} ecu_state_t;

void safety_init(void);
void safety_update(void);
bool safety_outputs_enabled(void);
ecu_state_t safety_get_state(void);

#endif
