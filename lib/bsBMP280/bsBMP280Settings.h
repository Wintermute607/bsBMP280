#ifndef BS_BMP280_SETTINGS_H
#define BS_BMP280_SETTINGS_H



#include "mbed.h"



namespace BMP280
{
    namespace Registers  /* BMP280 REGISTER ADDRESSES */
    {
        static constexpr auto CALIBRATION_COEFFICIENTS_ADDRESS     = uint8_t {0x88}; // offset address for the registers containing the calibration coefficients
        static constexpr auto CHIP_ID_REGISTER_ADDRESS             = uint8_t {0xD0}; // contains the chip identification number chip_id[7:0] (which is 0x58 in case of the bosch bmp280)
        static constexpr auto SOFT_RESET_REGISTER_ADDRESS          = uint8_t {0xE0}; // contains the soft reset word reset[7:0], the value 0xB6 will perform a reset
        static constexpr auto STATUS_REGISTER_ADDRESS              = uint8_t {0xF3}; // contains two bits which indicate the status of the device (bit 3: measuring[0], bit 0: im_update[0])
        static constexpr auto MEASUREMENT_CONTROL_REGISTER_ADDRESS = uint8_t {0xF4}; // sets the data acquisition options of the device (oversampling and mode)
        static constexpr auto CONFIGURATION_REGISTER_ADDRESS       = uint8_t {0xF5}; // sets the rate, filter and interface options of the device
        static constexpr auto PRESSURE_MSB_REGISTER_ADDRESS        = uint8_t {0xF7}; // contains the msb of the raw pressure measurement output data
        static constexpr auto PRESSURE_LSB_REGISTER_ADDRESS        = uint8_t {0xF8}; // contains the lsb of the raw pressure measurement output data
        static constexpr auto PRESSURE_XLSB_REGISTER_ADDRESS       = uint8_t {0xF9}; // contains the extended lsb of the raw pressure measurement output data
        static constexpr auto TEMPERATURE_MSB_REGISTER_ADDRESS     = uint8_t {0xFA}; // contains the msb of the raw temperature measurement output data
        static constexpr auto TEMPERATURE_LSB_REGISTER_ADDRESS     = uint8_t {0xFB}; // contains the lsb of the raw temperature measurement output data
        static constexpr auto TEMPERATURE_XLSB_REGISTER_ADDRESS    = uint8_t {0xFC}; // contains the extended lsb of the raw temperature measurement output data
    }
    
    namespace Modes  /* BMP280 - MODE - BITVECTOR IN THE MEASUREMENT CONTROL REGISTER */
    {
        static constexpr auto SLEEP_MODE  = uint8_t {0x00}; // in sleep mode no measurements are performed (set by default after power on reset)
        static constexpr auto FORCED_MODE = uint8_t {0x01}; // in forced mode a single measurement is performed according to selected measurement and filter options
        static constexpr auto NORMAL_MODE = uint8_t {0x03}; // normal mode continuosly cycles between an active measurement period and an inactive standby period
    };

    namespace Oversampling  /* BMP280 - OVERSAMPLING - BITVECTOR IN THE MEASUREMENT CONTROL REGISTER */
    {
        static constexpr auto OVERSAMPLING_OFF = uint8_t {0x00}; // pressure measurement skipped (output set to 0x80000)
        static constexpr auto OVERSAMPLING_X1  = uint8_t {0x01}; // oversampling ×1 (ultra low power, 16 bit, 2.62Pa / 0.0050°C)
        static constexpr auto OVERSAMPLING_X2  = uint8_t {0x02}; // oversampling ×2 (low power, 17 bit, 1.31Pa / 0.0025°C)
        static constexpr auto OVERSAMPLING_X4  = uint8_t {0x03}; // oversampling ×4 (standard resolution, 18 bit, 0.66Pa / 0.0012°C)
        static constexpr auto OVERSAMPLING_X8  = uint8_t {0x04}; // oversampling ×8 (high resolution, 19 bit, 0.33Pa / 0.0006°C)
        static constexpr auto OVERSAMPLING_X16 = uint8_t {0x05}; // oversampling ×16 (ultra high resolution, 20 bit, 0.16Pa / 0.0003°C)
    };
    
    namespace IIRFilter  /* BMP280 - INFINITE IMPULSE RESPONSE FILTER - BITVECTOR IN THE CONFIGURATION REGISTER */ 
    {
        static constexpr auto IIR_FILTER_OFF = uint8_t {0x00}; // Filter off (1 Sample to reach ≥75 % of step response)
        static constexpr auto IIR_FILTER_2   = uint8_t {0x01}; // Filter coefficient 2 (2 Samples to reach ≥75 % of step response)
        static constexpr auto IIR_FILTER_4   = uint8_t {0x02}; // Filter coefficient 4 (5 Samples to reach ≥75 % of step response)
        static constexpr auto IIR_FILTER_8   = uint8_t {0x03}; // Filter coefficient 8 (11 Samples to reach ≥75 % of step response)
        static constexpr auto IIR_FILTER_16  = uint8_t {0x04}; // Filter coefficient 16 (22 Samples to reach ≥75 % of step response)
    };

    namespace StandbyTime  /* BMP280 - STANDBY TIME - BITVECTOR IN THE CONFIGURATION REGISTER */ 
    {
        static constexpr auto STANDBY_TIME_05MS   = uint8_t {0x00}; // 0.5ms standby time between active measurement period and an inactive standby period
        static constexpr auto STANDBY_TIME_62MS   = uint8_t {0x01}; // 62.5ms standby time between active measurement period and an inactive standby period
        static constexpr auto STANDBY_TIME_125MS  = uint8_t {0x02}; // 125ms standby time between active measurement period and an inactive standby period
        static constexpr auto STANDBY_TIME_250MS  = uint8_t {0x03}; // 250ms standby time between active measurement period and an inactive standby period
        static constexpr auto STANDBY_TIME_500MS  = uint8_t {0x04}; // 500ms standby time between active measurement period and an inactive standby period
        static constexpr auto STANDBY_TIME_1000MS = uint8_t {0x05}; // 1000ms standby time between active measurement period and an inactive standby period
        static constexpr auto STANDBY_TIME_2000MS = uint8_t {0x06}; // 2000ms standby time between active measurement period and an inactive standby period
        static constexpr auto STANDBY_TIME_4000MS = uint8_t {0x07}; // 4000ms standby time between active measurement period and an inactive standby period
    };

}



#endif // BS_BMP280_SETTINGS_H