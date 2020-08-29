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
 *      Open Arduino IDE | Tools | Serial Plotter and reset the board
 *
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
    // Print labels
    Serial.println(F("\nVoltage, Current"));

    // Initialize I2C
    Wire.begin();
    Wire.setClock(400000);

    // Initialize INA219
    while (!ina219.begin()) {
        delay(3000);
    }
}

void loop()
{
    if (!ina219.read()) {
        return;
    }

    if (!ina219.available) {
        return;
    }

    Serial.print(ina219.busVoltage, 2);
    Serial.print(F("\t"));
    Serial.println(ina219.current / 1000, 1);

    delay(200);
}