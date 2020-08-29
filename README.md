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

* [ErriezINA219AutoRange](https://github.com/Erriez/ErriezINA219/blob/master/examples/ErriezINA219AutoRange/ErriezINA219AutoRange.ino) Auto range example.
* [ErriezINA219GettingStarted](https://github.com/Erriez/ErriezINA219/blob/master/examples/ErriezINA219GettingStarted/ErriezINA219GettingStarted.ino) Getting started example.
* [ErriezINA219SerialPlotter](https://github.com/Erriez/ErriezINA219/blob/master/examples/ErriezINA219SerialPlotter/ErriezINA219SerialPlotter.ino) Serial Plotter example.


## Documentation

- [Doxygen online HTML](https://erriez.github.io/ErriezINA219) 
- [Doxygen PDF](https://github.com/Erriez/ErriezINA219/raw/master/ErriezINA219.pdf)
- [INA219 datasheet](https://github.com/Erriez/ErriezINA219/blob/master/extras/INA219.pdf)


## Library dependencies

* ```Wire.h```


## Getting started

```c++
#include <Arduino.h>
#include <Wire.h>

#include <ErriezINA219.h>

// Default I2C Address 0x40
#define INA219_I2C_ADDRESS      0x40

// 0.1 Ohm shunt resistor
#define INA219_SHUNT_RESISTOR   0.1

// Create INA219 sensor object
INA219 ina219 = INA219(INA219_I2C_ADDRESS, INA219_SHUNT_RESISTOR);


void setup()
{
    // Initialize serial port
    Serial.begin(115200);
    while (!Serial) {
        ;
    }
    Serial.println(F("\nErriez INA219 voltage, current and power sensor example\n"));

    // Initialize I2C
    Wire.begin();
    Wire.setClock(400000);

    // Initialize INA219
    while (!ina219.begin()) {
        Serial.println(F("Error: INA219 not detected"));
        delay(3000);
    }
}

void loop()
{
    // Read from sensor
    if (!ina219.read()) {
        Serial.println(F("Error: INA219 read failed"));
        return;
    }

    // Check valid conversion
    if (!ina219.available) {
        Serial.println(F("Error: INA219 not available"));
        return;
    }

    // Print result
    Serial.println(F("INA219:"));

    Serial.print(F("  Bus voltage:   "));
    Serial.print(ina219.busVoltage, 2);
    Serial.println(F(" V"));

    Serial.print(F("  Shunt voltage: "));
    Serial.print(ina219.shuntVoltage / 1000, 1);
    Serial.println(F(" V"));

    Serial.print(F("  Current:       "));
    Serial.print(ina219.current / 1000, 1);
    Serial.println(F(" A"));

    Serial.print(F("  Power:         "));
    Serial.print(ina219.power / 1000, 1);
    Serial.println(F(" W"));

    // Wait some time
    delay(1000);
}
```

## Library installation

Please refer to the [Wiki](https://github.com/Erriez/ErriezArduinoLibrariesAndSketches/wiki) page.


## Other Arduino Libraries and Sketches from Erriez

* [Erriez Libraries and Sketches](https://github.com/Erriez/ErriezArduinoLibrariesAndSketches)
