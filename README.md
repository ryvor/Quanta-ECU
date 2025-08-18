# Quanta ECU

Minimal standalone engine control firmware for Raspberry Pi Pico.

## Wiring
```
Pico Pin  | Function
--------- | ---------------------------
GP2       | Crank input (60-2)
GP3       | Cam input (future)
GP10      | Ignition Coil A
GP11      | Ignition Coil B
GP12      | Injector Bank A
GP13      | Injector Bank B
GP6       | Enable input (active high)
GP0/GP1   | UART0 TX/RX 115200
GP16      | SPI0 MISO (MCP3208)
GP17      | SPI0 CS
GP18      | SPI0 SCK
GP19      | SPI0 MOSI
```

## Build
```
mkdir build && cd build
cmake ..
make
```
Requires the [Pico SDK](https://github.com/raspberrypi/pico-sdk) and `PICO_SDK_PATH` set.

## Simulation
Build with `-DSIM_TEETH=ON` to synthesize crank teeth for bench testing.

## Acceptance Checklist
- Boot and wait for enable.
- Sync on 60-2 wheel.
- Fixed timing test around 10° BTDC using timing light.
- Injector pulse width reacts to MAP and temps.
- Outputs cut when sync lost or enable low.

## Calibration
Use a timing light on cylinder #1. Adjust `tdc_offset_deg` in configuration until commanded advance matches observed.
