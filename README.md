# Erriez INA219 I2C Voltage/Current/Power Monitor library for Arduino

[![Build Status](https://travis-ci.org/Erriez/ErriezINA219.svg?branch=master)](https://travis-ci.org/Erriez/ErriezINA219)

This is an INA219 I2C Voltage/Current/Power Monitor library for Arduino.

![INA219](https://raw.githubusercontent.com/Erriez/ErriezINA219/master/extras/INA219.png)

## Library features

* TODO

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

## Library dependencies

* ```Wire.h```


## Library installation

Please refer to the [Wiki](https://github.com/Erriez/ErriezArduinoLibrariesAndSketches/wiki) page.


## Other Arduino Libraries and Sketches from Erriez

* [Erriez Libraries and Sketches](https://github.com/Erriez/ErriezArduinoLibrariesAndSketches)
