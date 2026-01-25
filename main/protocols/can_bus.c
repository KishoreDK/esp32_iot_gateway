#include "can_bus.h"
#include "esp_log.h"
#include "driver/twai.h"

static const char *TAG = "CAN_BUS";

/*
 * Initializes CAN (TWAI) bus scaffold.
 */
void can_bus_init(void)
{
    ESP_LOGI(TAG, "Initializing CAN bus (TWAI scaffold)");

    // No driver install yet
    ESP_LOGI(TAG, "CAN scaffold ready (no transceiver)");
}
