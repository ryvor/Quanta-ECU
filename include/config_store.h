#ifndef CONFIG_STORE_H
#define CONFIG_STORE_H
#include "config.h"
#include <stdbool.h>

bool config_store_load(void);
bool config_store_save(void);

#endif
