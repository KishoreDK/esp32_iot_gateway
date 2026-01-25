#pragma once

/*
 * This structure represents ALL sensor data
 * collected in one sampling cycle.
 *
 * It is intentionally generic so that:
 * - New sensors can be added later
 * - JSON payload logic does not change
 */
typedef struct {

    // -------- Digital sensors --------
    int temperature;    // DHT11 / DHT22
    int humidity;       // DHT11 / DHT22
    int motion;         // PIR
    int flame;          // Flame sensor
    int rain;           // Rain sensor
    int door;           // Reed switch

    // -------- Analog sensors (via ADC / MCP3008) --------
    int soil_moisture;
    int light;          // LDR
    int gas;
    int sound;
    int potentiometer;

    // -------- Bus-based sensors (future) --------
    int i2c_status;
    int spi_status;
    int can_status;

} sensor_data_t;

/*
 * Reads ALL sensors and returns a populated structure.
 * In this step, values are MOCKED (no hardware).
 */
sensor_data_t sensors_read_all(void);
