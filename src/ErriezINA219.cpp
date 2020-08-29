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
 * \file ErriezINA219.cpp
 * \brief INA219 voltage and current sensor library for Arduino
 * \details
 *      Source:         https://github.com/Erriez/ErriezINA219
 *      Documentation:  https://erriez.github.io/ErriezINA219
 */

#include <Arduino.h>
#include <Wire.h>

#include "ErriezINA219.h"


/*!
 * \brief INA219 constructor
 * \param i2cAddress
 *      I2C address
 * \param shuntResistor
 *      Shunt register in ohm, default: INA219_SHUNT_RESISTOR = 0.1 Ohm
 */
INA219::INA219(uint8_t i2cAddress, float shuntResistor) :
        _i2cAddress(i2cAddress), _shuntResistor(shuntResistor)
{

}

/*!
 * \brief Initialize INA219
 * \retval true
 *      INA219 detected
 * \retval false
 *      INA219 not detected
 */
bool INA219::begin()
{
    return powerUp();
}

/*!
 * \brief Set INA219 in power-down mode
 * \retval true
 *      Success
 * \retval false
 *      Error: I2C write register failed
 */
bool INA219::powerDown()
{
    // Keep last conversion

    _powerDown = true;

    // Initialize config register with default configuration
    registerWrite(INA219_REG_CONFIG, 0x3998);

    return _i2cStatus;
}

/*!
 * \brief Power-up INA219
 * \retval true
 *      Success
 * \retval false
 *      Error: I2C write register failed
 */
bool INA219::powerUp()
{
    // Clear values before start
    clear();

    _powerDown = false;

    // Initialize config register
    registerWrite(INA219_REG_CONFIG, REG_CONFIG_VALUE);

    return _i2cStatus;
}

/*!
 * \brief Read voltage and current from INA219
 * \details
 *      Variables
 * \retval true
 *      Conversion completed
 * \retval false
 *      Error: I2C read failed, or INA219 is in power-down
 */
bool INA219::read()
{
    uint16_t shuntVoltageReg;
    uint16_t busVoltageReg;

    // Check power state
    if (_powerDown) {
        return false;
    }

    // Clear measurement variables before read
    clear();

    // Read shunt voltage
    shuntVoltageReg = registerRead(INA219_REG_SHUNTVOLTAGE);
    if (_i2cStatus != 0) { return false; }

    // Read bus voltage
    busVoltageReg = registerRead(INA219_REG_BUSVOLTAGE);
    if (_i2cStatus != 0) { return false; }

    // Calculate shunt voltage in mV
    if (shuntVoltageReg & 0x8000) {
        // Two's complete on 16-bit unsigned register value
        shuntVoltage = (int16_t)((~shuntVoltageReg) + 1) * -1;
    } else {
        shuntVoltage = shuntVoltageReg;
    }
    shuntVoltage /= 100;

    // Calculate bus voltage in mV
    if (busVoltageReg & 0x01) {
        // OVF (Overflow) bit is set
        busVoltage = 0xFFFF;
        overflow = true;
    } else {
        // Return bus voltage bits 3..15 where LSB = 4 mV
        busVoltage = (busVoltageReg >> 3) * 4;
        overflow = false;
    }
    busVoltage /= 1000;

    // Calculate current in mA: I = U / Rshunt
    current = shuntVoltage / _shuntResistor;

    // Calculate power in mW: P = U * I
    power = busVoltage * current;
    if (power < 0) {
        // Make power absolute
        power *= -1;
    }

    // Conversion completed
    available = true;

    return available;
}

/*!
 * \brief Clear measurement variables
 */
void INA219::clear()
{
    busVoltage = 0;
    shuntVoltage = 0;
    current = 0;
    power = 0;
    available = false;
}

/*!
 * \brief Read from INA219 register
 * \param reg
 *      INA219 register 0..5
 * \retval true
 *      Register read success
 * \retval false
 *      Error: I2C read failed
 */
uint16_t INA219::registerRead(uint8_t reg)
{
    Wire.beginTransmission(_i2cAddress);
    Wire.write(&reg, 1);
    _i2cStatus = Wire.endTransmission(false);
    (void)Wire.requestFrom(_i2cAddress, (uint8_t)2);
    return (Wire.read() << 8) | Wire.read();
}

/*!
 * \brief Write to INA219 register
 * \param reg
 *      INA219 register 0..5
 * \param val
 *      16-bit INA219 register value
 * \return
 *      Result of Wire endTransmission()
 */
void INA219::registerWrite(uint8_t reg, uint16_t val)
{
    const uint8_t buffer[3] = { reg, (uint8_t)(val >> 8), (uint8_t)(val & 0xff) };

    Wire.beginTransmission(_i2cAddress);
    Wire.write(buffer, sizeof(buffer));
    _i2cStatus = (Wire.endTransmission() == 0) ? true : false;
}

/*!
 * \brief Return status of the last I2C write, returned by Wire endTransfer()
 * \retval 0: Success
 * \retval 1: Data too long to fit in transmit buffer
 * \retval 2: Received NACK on transmit of address
 * \retval 3: Received NACK on transmit of data
 * \retval 4: Other error
 */
uint8_t INA219::getI2CStatus()
{
    /* Status of the endTransmission */
    return _i2cStatus;
}

/*!
 * \brief Print I2C registers on serial port
 * \details
 *     This function is optimized away by the compiler when not used
 * \param serial
 *     Serial port
 */
void INA219::dumpRegisters(Stream *serial)
{
    serial->println(F("INA219 registers:"));

    serial->print(F("  00 CONFIG:       0x"));
    serial->println(registerRead(INA219_REG_CONFIG), HEX);
    serial->print(F("  01 SHUNTVOLTAGE: 0x"));
    serial->println(registerRead(INA219_REG_SHUNTVOLTAGE), HEX);
    serial->print(F("  02 BUSVOLTAGE:   0x"));
    serial->println(registerRead(INA219_REG_BUSVOLTAGE), HEX);
    serial->print(F("  03 POWER:        0x"));
    serial->println(registerRead(INA219_REG_POWER), HEX);
    serial->print(F("  04 CURRENT:      0x"));
    serial->println(registerRead(INA219_REG_CURRENT), HEX);
    serial->print(F("  05 CALIBRATION:  0x"));
    serial->println(registerRead(INA219_REG_CALIBRATION), HEX);
}
