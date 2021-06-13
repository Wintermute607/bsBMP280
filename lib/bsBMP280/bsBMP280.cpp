#include "bsBMP280.h"
#include "bsBMP280Settings.h"
#include <cstdint>


namespace BMP280
{
    /* CONSTRUCTOR */

    bsBMP280::bsBMP280(I2C& i2cInterface, i2cAddresses address) : i2cInterface(i2cInterface), I2C_ADDRESS(static_cast<int>(address) << 1), INITIALIZED(initialize())
    {

    }



    /* PUBLIC METHODS */


    bsBMP280::operator bool() const
    {
        return INITIALIZED;
    }


    void bsBMP280::foo()
    {
        debug("\nFoo message.\n");
    }


    void bsBMP280::setMode(const uint8_t mode)
    {
        using namespace Modes;
        setRegisterBits(measurementControlRegister,MODE_BITMASK, MODE_OFFSET, mode);
        writeByte(Registers::MEASUREMENT_CONTROL_REGISTER_ADDRESS, measurementControlRegister);
    }


    void bsBMP280::setPressureOversampling(const uint8_t oversampling)
    {
        using namespace Oversampling;
        setRegisterBits(measurementControlRegister, PRESSURE_OVERSAMPLING_BITMASK, PRESSURE_OVERSAMPLING_OFFSET, oversampling);
        writeByte(Registers::MEASUREMENT_CONTROL_REGISTER_ADDRESS, measurementControlRegister);
    }


    void bsBMP280::setTemperatureOversampling(const uint8_t oversampling)
    {
        using namespace Oversampling;
        setRegisterBits(measurementControlRegister, TEMPERATURE_OVERSAMPLING_BITMASK, TEMPERATURE_OVERSAMPLING_OFFSET, oversampling);
        writeByte(Registers::MEASUREMENT_CONTROL_REGISTER_ADDRESS, measurementControlRegister);
    }


    void bsBMP280::enable3WireSPI(const uint8_t enable)
    {
        using namespace SPIInterface;
        setRegisterBits(configurationRegister, SPI_INTERFACE_BITMASK, SPI_INTERFACE_OFFSET, enable);
        writeByte(Registers::CONFIGURATION_REGISTER_ADDRESS, configurationRegister);
    }


    void bsBMP280::setFilter(const uint8_t filter)
    {
        using namespace IIRFilter;
        setRegisterBits(configurationRegister, IIR_FILTER_BITMASK, IIR_FILTER_OFFSET, filter);
        writeByte(Registers::CONFIGURATION_REGISTER_ADDRESS, configurationRegister);
    }


    void bsBMP280::setStandbyTime(const uint8_t time)
    {
        using namespace StandbyTime;
        setRegisterBits(configurationRegister, STANDBY_TIME_BITMASK, STANDBY_TIME_OFFSET, time);
        writeByte(Registers::CONFIGURATION_REGISTER_ADDRESS, configurationRegister);
    }


    void bsBMP280::setRecommendedSetting(const uint8_t crtl_meas, const uint8_t config)
    {
        writeByte(Registers::MEASUREMENT_CONTROL_REGISTER_ADDRESS, crtl_meas);
        writeByte(Registers::CONFIGURATION_REGISTER_ADDRESS, config);
    }

    void bsBMP280::setRecommendedConfig(const uint8_t *config)
    {
        writeByte(Registers::MEASUREMENT_CONTROL_REGISTER_ADDRESS, config[0]);
        writeByte(Registers::CONFIGURATION_REGISTER_ADDRESS, config[1]);
    }



    /* PRIVATE METHODS */


    bool bsBMP280::initialize() const
    {
    	if (getChipID() == 0x58)
        {
            debug("Initializing sensor...\n");
            // init sequence...
            return true;
        }
        else
        {
            debug("Initialization stopped.\n");
            return false;
        }
    }


    uint8_t bsBMP280::getChipID() const
    {
        uint8_t chipID;
        i2cInterface.write(I2C_ADDRESS, reinterpret_cast<const char*>(&Registers::CHIP_ID_REGISTER_ADDRESS), sizeof(Registers::CHIP_ID_REGISTER_ADDRESS), true);
        i2cInterface.read(I2C_ADDRESS, reinterpret_cast<char*>(&chipID), sizeof(chipID), false);
        return chipID;
    }


    void bsBMP280::setRegisterBits(uint8_t &reg, const uint8_t bitmask, const uint8_t offset, const uint8_t value)
    {
        reg &= ~(bitmask);
        reg |= ((value) << offset) & bitmask;
    }

    int bsBMP280::writeByte(const int address, const uint8_t payload)
    {
        i2cInterface.write(I2C_ADDRESS, reinterpret_cast<const char*>(address), sizeof(address), true);
        return i2cInterface.write(I2C_ADDRESS, reinterpret_cast<const char*>(payload), sizeof(payload), false);
    }
}