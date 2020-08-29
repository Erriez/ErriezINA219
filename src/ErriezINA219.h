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
 * \file ErriezINA219.h
 * \brief INA219 voltage and current sensor library for Arduino
 * \details
 *      Source:         https://github.com/Erriez/ErriezINA219
 *      Documentation:  https://erriez.github.io/ErriezINA219
 */

#ifndef ERRIEZ_INA219_H_
#define ERRIEZ_INA219_H_

#include <stdint.h>

// INA219 configuration
#define INA219_I2C_ADDRESS          0x40    //!< Default I2C address
#define INA219_SHUNT_RESISTOR       0.1     //!< Default shunt resistor in Ohm

// INA219 registers
#define INA219_REG_CONFIG           0x00    //!< Config register
#define INA219_REG_SHUNTVOLTAGE     0x01    //!< Shunt/voltage register
#define INA219_REG_BUSVOLTAGE       0x02    //!< Bus voltage register
#define INA219_REG_POWER            0x03    //!< Power register
#define INA219_REG_CURRENT          0x04    //!< Current register
#define INA219_REG_CALIBRATION      0x05    //!< Calibration register

// INA219 register bit defines
#define INA219_CONFIG_RST                   15          //!< Reset

#define INA219_CONFIG_BRNG                  13          //!< Bus voltage range
#define INA219_CONFIG_BRNG_16V              (0 << 13)   //!< Bus voltage range 16V
#define INA219_CONFIG_BRNG_32V              (1 << 13)   //!< Bus voltage range 32V

#define INA219_CONFIG_GAIN_MASK             (3 << 12)   //!< PGA Gain and Range
#define INA219_CONFIG_GAIN_1                (0 << 12)   //!< ±40 mV
#define INA219_CONFIG_GAIN_2                (1 << 12)   //!< ±80 mV
#define INA219_CONFIG_GAIN_4                (2 << 12)   //!< ±160 mV
#define INA219_CONFIG_GAIN_8                (3 << 12)   //!< ±320 mV

#define INA219_CONFIG_BADC_MASK             0x0780      //!< Bus ADC Resolution/Averaging
#define INA219_CONFIG_BADC(adc)             ((adc & INA219_CONFIG_BADC_MASK) << 7) //!< Bus ADC mask and shift

#define INA219_CONFIG_SADC_MASK             0x0078      //!< Shunt ADC Resolution/Averaging
#define INA219_CONFIG_SADC(adc)             ((adc & INA219_CONFIG_BADC_MASK) << 3) //!< Shunt ADC mask and shift

#define INA219_CONFIG_xADC_9B               0           //!< 9 bit
#define INA219_CONFIG_xADC_10B              1           //!< 10 bit
#define INA219_CONFIG_xADC_11B              2           //!< 11 bit
#define INA219_CONFIG_xADC_12B              3           //!< 12 bit
#define INA219_CONFIG_xADC_2S               9           //!< 2 samples
#define INA219_CONFIG_xADC_4S               10          //!< 4 samples
#define INA219_CONFIG_xADC_8S               11          //!< 8 samples
#define INA219_CONFIG_xADC_16S              12          //!< 16 samples
#define INA219_CONFIG_xADC_32S              13          //!< 32 samples
#define INA219_CONFIG_xADC_64S              14          //!< 64 samples
#define INA219_CONFIG_xADC_128S             15          //!< 128 samples

#define INA219_CONFIG_MODE_MASK             0x0007      //!< Operating Mode
#define INA219_CONFIG_MODE(mode)            ((mode & INA219_CONFIG_MODE_MASK) << 0) //!< Config mode mask and shift
#define INA219_CONFIG_MODE_POWER_DOWN       0           //!< Power-Down
#define INA219_CONFIG_MODE_SHUNT_TRG        1           //!< Shunt voltage, triggered
#define INA219_CONFIG_MODE_BUS_TRG          2           //!< Bus voltage, triggered
#define INA219_CONFIG_MODE_SHUNT_BUS_TRG    3           //!< Shunt and bus voltage, triggered
#define INA219_CONFIG_MODE_ADC_OFF          4           //!< ADC off (disabled)
#define INA219_CONFIG_MODE_SHUNT_CNT        5           //!< Shunt voltage, continuous
#define INA219_CONFIG_MODE_BUS_CNT          6           //!< Bus voltage, continuous
#define INA219_CONFIG_MODE_SHUNT_BUS_CNT    7           //!< Shunt and bus voltage, continuous

/*!
 * \brief Default config register value
 * \details
 *    Shunt and bus:
 *      BADC: +/-320 mV
 *      Continuous conversion
 *      532 us conversion time
 */
#define REG_CONFIG_VALUE            0x399F


/*!
 * \brief INA219 class
 */
class INA219
{
public:
    // Constructor
    INA219(uint8_t i2cAddress=INA219_I2C_ADDRESS, float shuntResistor=INA219_SHUNT_RESISTOR);

    // INA219 functions
    bool begin();
    bool powerDown();
    bool powerUp();
    bool read();

    // I2C register access
    void registerWrite(uint8_t reg, uint16_t val);
    uint16_t registerRead(uint8_t reg);
    uint8_t getI2CStatus();

    // Debug functions
    void dumpRegisters(Stream *serial);

    float busVoltage;       //!< Bus voltage in V
    float shuntVoltage;     //!< Shunt voltage in mV
    float current;          //!< Current in mA
    float power;            //!< Power in mW
    bool overflow;          //!< Overflow
    bool available;         //!< Successful conversion

private:
    void clear();

    uint8_t _i2cAddress;        //!< I2C address
    uint8_t _i2cStatus;
    float _shuntResistor;   //!< Shunt resistor in Ohm
    bool _powerDown;        //!< Power down state
};


#endif // ERRIEZ_INA219_H_
