# cortex-m3-rtos-blinky-example

This is a classic blinky example for parent RTOS project: https://github.com/t4th/cortex-m3-rtos

This is on target project using ulink2 debugger and stm32f103ZE with 4 LED pins connected to GPIOF 6,7,8,9.

For each LED exist task that is blinking it. For human eye it should look like all 4 LEDs are blinking at the same time.

Gpio lib is a bit over-engineered, but I was just having fun with meta programming :P.

## How to use
Use `--recursive` flag when cloning this repository to load submodules or call `git submodule update --remote --init` after to update submodules, then open `keil/project-template.uvprojx` and press build.

## Requirements
Installed Keil Uvision 5 lite 529 (Monday, November 18, 2019) or up (needed for c++17)

## TODO
- [ ] add pictures