cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(QuantaECU C CXX ASM)

pico_sdk_init()

add_executable(quanta
    src/main.c
    src/config.c
    src/config_store.c
    src/tables.c
    src/sensors_mcp3208.c
    src/thermistors.c
    src/crank_decoder.c
    src/scheduler.c
    src/ignition.c
    src/fuel.c
    src/uart_cli.c
    src/safety.c
    src/crank_pio.c
)

target_include_directories(quanta PRIVATE include)

target_compile_definitions(quanta PRIVATE PICO_NO_BINARY_INFO=1)

pico_enable_stdio_uart(quanta 1)

pico_add_extra_outputs(quanta)
