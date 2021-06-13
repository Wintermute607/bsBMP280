#include "mbed.h"
#include "settings.h"
#include "lib/bsBMP280/bsBMP280.h"


int main()
{
    using namespace BMP280;

    I2C i2cInterface(SDA_PIN, SCL_PIN);                                      // initialise the i2c interface

    bsBMP280 bmp280(i2cInterface, bsBMP280::i2cAddresses::PRIMARY_ADDRESS);  // initialise the bmp280 sensor

    DigitalOut led(LED1);                                                    // initialise the digital pin led1 as an output

    while (true)
    {
        // bmp280 ? debug("BMP280 Sensor found.\n") : debug("BMP280 Sensor not found.\n");
        led = !led;  // reverse the state of the led
        bmp280.setFilter(IIRFilter::IIR_FILTER_X16);
        ThisThread::sleep_for(SLEEP_TIME);  // sleep for a given time
    }
}
