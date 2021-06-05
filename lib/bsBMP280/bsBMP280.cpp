#include "bsBMP280.h"
#include "bsBMP280Settings.h"
#include <cstdint>


namespace BMP280
{
    /************** CONSTRUCTOR ***************/

    bsBMP280::bsBMP280(I2C& i2cInterface, i2cAddresses address) : i2cInterface(i2cInterface), I2C_ADDRESS(static_cast<int>(address) << 1, INITIALIZED(initialize()))
    {
        // ...
    }


    /************* PUBLIC METHODS *************/

    bsBMP280::operator bool() const
    {
        return INITIALIZED;
    }

    void bsBMP280::foo()
    {
        debug("\nFoo message.\n");
        debug("ChipID: 0x%#X \n", getChipID());
    }

    
    /************ PRIVATE METHODS *************/

    bool bsBMP280::initialize() const
    {
    	if (getChipID() == 0x58)
            return true;
        else
            return false;
    }

    uint8_t bsBMP280::getChipID() const
    {
        uint8_t chipID;
        i2cInterface.write(I2C_ADDRESS, reinterpret_cast<const char*>(&Registers::CHIP_ID_REGISTER_ADDRESS), sizeof(Registers::CHIP_ID_REGISTER_ADDRESS), true);
        i2cInterface.read(I2C_ADDRESS, reinterpret_cast<char*>(&chipID), sizeof(chipID), false);
        return chipID;
    }

}