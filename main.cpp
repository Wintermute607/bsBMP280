#include "mbed.h"
#include "settings.h"
#include "lib/bsBMP280/bsBMP280.h"


int main()
{
    using namespace BMP280;

    I2C i2cInterface(SDA_PIN, SCL_PIN);
    i2cInterface.frequency(400000);

    bsBMP280 bmp280(i2cInterface, bsBMP280::i2cAddresses::PRIMARY_ADDRESS);

    DigitalOut led(LED1);

    bmp280 ? debug("BMP280 Sensor found.\n") : debug("BMP280 Sensor not found.\n");

    while (true)
    {
        debug("Setting HANDHELD_LOW_POWER mode...\n");
        bmp280.setRecommendedSetting(RecommendedSettings::HANDHELD_LOW_POWER[0], RecommendedSettings::HANDHELD_LOW_POWER[1]);
        led = !led;  // reverse the state of the led
        ThisThread::sleep_for(SLEEP_TIME);  // sleep for a given time

        debug("Setting HANDHELD_DYNAMIC mode...\n");
        bmp280.setRecommendedSetting(RecommendedSettings::HANDHELD_DYNAMIC[0], RecommendedSettings::HANDHELD_DYNAMIC[1]);
        led = !led;  // reverse the state of the led
        ThisThread::sleep_for(SLEEP_TIME);  // sleep for a given time

        debug("Setting WEATHER_MONITORING mode...\n");
        bmp280.setRecommendedSetting(RecommendedSettings::WEATHER_MONITORING[0], RecommendedSettings::WEATHER_MONITORING[1]);
        led = !led;  // reverse the state of the led
        ThisThread::sleep_for(SLEEP_TIME);  // sleep for a given time

        debug("Setting FLOOR_CHANGE_DETECTION mode...\n");
        bmp280.setRecommendedSetting(RecommendedSettings::FLOOR_CHANGE_DETECTION[0], RecommendedSettings::FLOOR_CHANGE_DETECTION[1]);
        led = !led;  // reverse the state of the led
        ThisThread::sleep_for(SLEEP_TIME);  // sleep for a given time

        debug("Setting DROP_DETECTION mode...\n");
        bmp280.setRecommendedSetting(RecommendedSettings::DROP_DETECTION[0], RecommendedSettings::DROP_DETECTION[1]);
        led = !led;  // reverse the state of the led
        ThisThread::sleep_for(SLEEP_TIME);  // sleep for a given time

        debug("Setting INDOOR_NAVIGATION mode...\n");
        bmp280.setRecommendedSetting(RecommendedSettings::INDOOR_NAVIGATION[0], RecommendedSettings::INDOOR_NAVIGATION[1]);
        led = !led;  // reverse the state of the led
        ThisThread::sleep_for(SLEEP_TIME);  // sleep for a given time

    }
}
