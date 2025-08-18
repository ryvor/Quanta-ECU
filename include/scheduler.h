#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <stdbool.h>

void scheduler_init(void);
void scheduler_update(void);
void scheduler_set_ignition(bool coil_a, float angle_deg, float dwell_ms);
void scheduler_set_injection(bool bank_a, float angle_deg, float pw_ms);

#endif
