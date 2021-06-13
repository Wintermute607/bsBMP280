#include "bsBMP280.h"
#include "bsBMP280Settings.h"


namespace BMP280
{
    /* CONSTRUCTOR */

    bsBMP280::bsBMP280(I2C& i2cInterface, i2cAddresses address) : i2cInterface(i2cInterface), I2C_ADDRESS(static_cast<int>(address) << 1), INITIALIZED(initialize())
    {

    }


    /* PUBLIC METHODS */

    bsBMP280::operator bool() const { return INITIALIZED; }

    void bsBMP280::foo()
    {
        debug("\nFoo message.\n");
    }

    void bsBMP280::setMode(const uint8_t mode)
    {
        using namespace Modes;
        setRegisterBits(measurementControlRegister,MODE_BITMASK, MODE_OFFSET, mode);
        debug("Current measurement control register: 0x%#X\r\n", measurementControlRegister);
        return;
    }

    void bsBMP280::setPressureOversampling(const uint8_t oversampling)
    {
        using namespace Oversampling;
        setRegisterBits(measurementControlRegister, PRESSURE_OVERSAMPLING_BITMASK, PRESSURE_OVERSAMPLING_OFFSET, oversampling);
        debug("Current measurement control register: 0x%#X\r\n", measurementControlRegister);
        // ...
    }

    void bsBMP280::setTemperatureOversampling(const uint8_t oversampling)
    {
        using namespace Oversampling;
        setRegisterBits(measurementControlRegister, TEMPERATURE_OVERSAMPLING_BITMASK, TEMPERATURE_OVERSAMPLING_OFFSET, oversampling);
        debug("Current measurement control register: 0x%#X\r\n", measurementControlRegister);
        // ...
    }

    void bsBMP280::enable3WireSPI(const uint8_t enable)
    {
        using namespace SPIInterface;
        setRegisterBits(configurationRegister, SPI_INTERFACE_BITMASK, SPI_INTERFACE_OFFSET, enable);
        debug("Current configuration register: 0x%#X\r\n", configurationRegister);
        // ...
    }

    void bsBMP280::setFilter(const uint8_t filter)
    {
        using namespace IIRFilter;
        setRegisterBits(configurationRegister, IIR_FILTER_BITMASK, IIR_FILTER_OFFSET, filter);
        debug("Current configuration register: 0x%#X\r\n", configurationRegister);
        // ...
    }

    void bsBMP280::setStandbyTime(const uint8_t time)
    {
        using namespace StandbyTime;
        setRegisterBits(configurationRegister, STANDBY_TIME_BITMASK, STANDBY_TIME_OFFSET, time);
        debug("Current configuration register: 0x%#X\r\n", configurationRegister);
        // ...
    }

    
    /* PRIVATE METHODS */

    bool bsBMP280::initialize() const
    {
    	if (getChipID() == 0x58)
        {
            debug("Bosch Sensortech BMP280 digital pressure sensor with chip ID 0x%#X found at I2C address 0x%#X\n", getChipID(), I2C_ADDRESS >> 1);
            debug("Initializing sensor...\n");
            // init sequence...
            return true;
        }
        else
        {
            debug("No Bosch Sensortech BMP280 digital pressure sensor present at at I2C address 0x%#X\n", I2C_ADDRESS);
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

    void setRegisterBits(uint8_t &reg, const uint8_t bitmask, const uint8_t offset, const uint8_t value)
    {
        reg &= ~(bitmask);
        reg |= ((value) << offset) & bitmask;
    }

}