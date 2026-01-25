#include "sensors.h"

/*
 * Mock implementation of sensor readings.
 *
 * WHY mock?
 * - No hardware available now
 * - Code still builds and runs
 * - Same interface will be used later with real drivers
 */
sensor_data_t sensors_read_all(void)
{
    sensor_data_t data = {0};

    // -------- Digital sensors --------
    data.temperature = 26;   // °C (DHT)
    data.humidity = 58;      // % (DHT)
    data.motion = 0;         // PIR: no motion
    data.flame = 0;          // No flame
    data.rain = 0;           // No rain
    data.door = 1;           // Door closed

    // -------- Analog sensors --------
    data.soil_moisture = 420;
    data.light = 700;
    data.gas = 120;
    data.sound = 30;
    data.potentiometer = 512;

    // -------- Bus status (future placeholders) --------
    data.i2c_status = 1;     // OK
    data.spi_status = 1;     // OK
    data.can_status = 0;     // Not connected yet

    return data;
}
