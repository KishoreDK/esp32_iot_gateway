#include "i2c_bus.h"
#include "esp_log.h"
#include "driver/i2c.h"

static const char *TAG = "I2C_BUS";

/*
 * Initializes I2C master bus.
 * Safe to call even without hardware.
 */
void i2c_bus_init(void)
{
    ESP_LOGI(TAG, "Initializing I2C bus (scaffold)");

    // Placeholder configuration
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = -1,   // To be defined later
        .scl_io_num = -1,   // To be defined later
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 100000
    };

    // Do NOT install driver yet (no pins defined)
    ESP_LOGI(TAG, "I2C scaffold ready (no driver install yet)");
}
