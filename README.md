# cortex-m3-rtos-blinky-example

This is classic blinky example for parent RTOS project: https://github.com/t4th/cortex-m3-rtos

This is on target project using ulink2 debugger and stm32f103ZE with 4 LED pins connected to GPIOF 6,7,8,9.

For each LED exist task that is blinking it. For human eye it should look like all 4 LEDs are blinking at the same time.

Gpio lib is a bit over-engineered for the purpose, but I was just having fun with meta programming :P.

## TODO
- [ ] add pictures