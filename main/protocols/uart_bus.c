#include "uart_bus.h"
#include "esp_log.h"
#include "driver/uart.h"

static const char *TAG = "UART_BUS";

/*
 * Initializes UART scaffold.
 */
void uart_bus_init(void)
{
    ESP_LOGI(TAG, "Initializing UART bus (scaffold)");
}
