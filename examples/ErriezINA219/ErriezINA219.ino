/*
 * MIT License
 *
 * Copyright (c) 2020 Erriez
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*!
 * \brief Erriez INA219 I2C voltage, current and power sensor example for Arduino
 * \details
 *      Source:         https://github.com/Erriez/ErriezINA219
 *      Documentation:  https://erriez.github.io/ErriezINA219
 */

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
    Serial.println(F("\nINA219 voltage, current and power sensor example\n"));

    // Initialize I2C
    Wire.begin();
    Wire.setClock(400000);

    // Initialize INA219
    while (!ina219.begin()) {
        Serial.println(F("Error: INA219 not detected"));
        delay(3000);
    }

    // Dump INA219 registers
    ina219.dumpRegisters(&Serial);
}

void loop()
{
    if (!ina219.read()) {
        Serial.println(F("Error: INA219 read failed"));
        return;
    }

    if (!ina219.available) {
        Serial.println(F("Error: INA219 not available"));
        return;
    }

    Serial.println(F("INA219:"));

    Serial.print(F("  Bus voltage:   "));
    Serial.print(ina219.busVoltage, 2);
    Serial.println(F(" V"));

    Serial.print(F("  Shunt voltage: "));
    if (ina219.shuntVoltage > 1000) {
        Serial.print(ina219.shuntVoltage / 1000, 1);
        Serial.println(F(" V"));
    } else {
        Serial.print(ina219.shuntVoltage, 1);
        Serial.println(F(" mV"));
    }

    Serial.print(F("  Current:       "));
    if (ina219.current > 1000) {
        Serial.print(ina219.current / 1000, 1);
        Serial.println(F(" A"));
    } else {
        Serial.print(ina219.current, 1);
        Serial.println(F(" mA"));
    }

    Serial.print(F("  Power:         "));
    if (ina219.power >= 1000) {
        Serial.print(ina219.power / 1000, 1);
        Serial.println(F(" W"));
    } else {
        Serial.print(ina219.power, 1);
        Serial.println(F(" mW"));
    }

    delay(1000);
}