#include "config_store.h"
#include "pico/stdlib.h"
#include <string.h>

// Simple placeholder implementation storing config in RAM
static ecu_config_t stored_config;

bool config_store_load(void) {
    if (stored_config.injector_cc_min == 0) {
        config_load_defaults();
        return false;
    }
    ecu_config = stored_config;
    return true;
}

bool config_store_save(void) {
    stored_config = ecu_config;
    return true;
}
