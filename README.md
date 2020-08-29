# Erriez INA219 I2C/SMB Voltage/Current/Power Monitor library for Arduino

[![Build Status](https://travis-ci.org/Erriez/ErriezINA219.svg?branch=master)](https://travis-ci.org/Erriez/ErriezINA219)

This is an INA219 I2C/SMB Voltage/Current/Power Monitor library for Arduino.

![INA219](https://raw.githubusercontent.com/Erriez/ErriezINA219/master/extras/INA219.png)


## Library features

* High Accuracy: max 0.5%
* Measure Voltage 0..26V DC
* Measure Current 0..2000mA DC (with default 0.1 Ohm shunt)
* Measure Power in Watt (Software Voltage * Current calculation)
* Configurable shunt resistor value
* Configurable I2C address for multiple sensors
* Power-down / power-up control
* Low-level register access


## Hardware

Any Arduino hardware with a TWI interface and ```Wire.h``` support.

| Pins board - INA219            | VCC  | GND  |    SDA     |    SCL     |
| ------------------------------ | :--: | :--: | :--------: | :--------: | 
| Arduino UNO (ATMega328 boards) |  5V  | GND  |     A4     |     A5     |
| Arduino Mega2560               |  5V  | GND  |    D20     |    D21     |
| Arduino Leonardo               |  5V  | GND  |     D2     |     D3     |
| Arduino DUE (ATSAM3X8E)        | 3V3  | GND  |     20     |     21     |
| ESP8266                        | 3V3  | GND  | GPIO4 (D2) | GPIO5 (D1) |
| ESP32                          | 3V3  | GND  |   GPIO21   |   GPIO22   |


## Examples

* [ErriezINA219](https://github.com/Erriez/ErriezINA219/blob/master/examples/ErriezINA219/ErriezINA219.ino) Getting started.
* [ErriezINA219SerialPlotter](https://github.com/Erriez/ErriezINA219/blob/master/examples/ErriezINA219SerialPlotter/ErriezINA219SerialPlotter.ino) Serial Plotter Example.


## Documentation

- [Doxygen online HTML](https://erriez.github.io/ErriezINA219) 
- [Doxygen PDF](https://github.com/Erriez/ErriezINA219/raw/master/ErriezINA219.pdf)
- [INA219 datasheet](https://github.com/Erriez/ErriezINA219/blob/master/extras/INA219.pdf)


## Library dependencies

* ```Wire.h```


## Library installation

Please refer to the [Wiki](https://github.com/Erriez/ErriezArduinoLibrariesAndSketches/wiki) page.


## Other Arduino Libraries and Sketches from Erriez

* [Erriez Libraries and Sketches](https://github.com/Erriez/ErriezArduinoLibrariesAndSketches)
