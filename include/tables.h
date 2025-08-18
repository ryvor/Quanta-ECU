#ifndef TABLES_H
#define TABLES_H
#include "config.h"

extern const float ignition_table[RPM_TABLE_SIZE][MAP_TABLE_SIZE];
extern const float ve_table[RPM_TABLE_SIZE][MAP_TABLE_SIZE];

float table_lookup(const float table[RPM_TABLE_SIZE][MAP_TABLE_SIZE], float rpm, float kpa);

#endif
