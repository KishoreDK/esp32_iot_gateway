#include "spi_bus.h"
#include "esp_log.h"
#include "driver/spi_master.h"

static const char *TAG = "SPI_BUS";

/*
 * Initializes SPI bus.
 * Scaffold only – no device attached yet.
 */
void spi_bus_init(void)
{
    ESP_LOGI(TAG, "Initializing SPI bus (scaffold)");

    // SPI bus config placeholder
    spi_bus_config_t buscfg = {
        .mosi_io_num = -1,
        .miso_io_num = -1,
        .sclk_io_num = -1,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
    };

    ESP_LOGI(TAG, "SPI scaffold ready (pins not assigned)");
}
