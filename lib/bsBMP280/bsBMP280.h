#ifndef BS_BMP280_H
#define BS_BMP280_H


#include "mbed.h"
#include "bsBMP280Settings.h"
#include <cstdint>


namespace BMP280
{
    class bsBMP280
    {
        public:

            enum class i2cAddresses : int { PRIMARY_ADDRESS = 0x76, SECONDARY_ADDRESS = 0x77 };
      
            bsBMP280(I2C& i2c, i2cAddresses address = i2cAddresses::PRIMARY_ADDRESS);

            explicit inline operator bool() const;

            void foo();

        private:

            I2C& i2cInterface;

            const int I2C_ADDRESS;
            const bool INITIALIZED; 

            inline bool initialize() const;
            uint8_t getChipID() const;

            

  
    };
}


#endif // BS_BMP280_H