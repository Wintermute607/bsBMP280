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

            explicit operator bool() const;

            void foo();

            // set measurement control register members 
            void setMode(const uint8_t mode);
            void setPressureOversampling(const uint8_t oversampling);
            void setTemperatureOversampling(const uint8_t oversampling);

            // set config register members 
            void enable3WireSPI(const uint8_t enable); 
            void setFilter(const uint8_t filter);
            void setStandbyTime(const uint8_t time);

        private:

            I2C& i2cInterface;

            const int I2C_ADDRESS;
            const bool INITIALIZED; 

            uint8_t measurementControlRegister = 0b00000000; // copy of measurement control register
            uint8_t configurationRegister = 0b00000000; // copy of config register

            bool initialize() const;
            uint8_t getChipID() const;

            void setRegisterBits(uint8_t &reg, const uint8_t bitmask, const uint8_t offset, const uint8_t value); // set given register
    };
}


#endif // BS_BMP280_H