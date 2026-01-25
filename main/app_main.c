#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "wifi.h"
#include "mqtt.h"
#include "sensors.h"
#include "payload.h"
#include "actuators.h"

#include "i2c_bus.h"
#include "spi_bus.h"
#include "can_bus.h"
#include "uart_bus.h"


static const char *TAG = "APP_MAIN";

void app_main(void)
{
    ESP_LOGI(TAG, "ESP32 IoT Gateway starting (code-only mode)");

    // Initialize system modules
    wifi_init();
    mqtt_init();

    #ifdef CONFIG_ENABLE_I2C
        i2c_bus_init();
    #endif

    #ifdef CONFIG_ENABLE_SPI
        spi_bus_init();
    #endif

    #ifdef CONFIG_ENABLE_CAN
        can_bus_init();
    #endif

    #ifdef CONFIG_ENABLE_UART
        uart_bus_init();
    #endif

    while (1) {
        // Read all sensors
        sensor_data_t data = sensors_read_all();

        // Build JSON payload
        char *json_payload = payload_build(&data);

        // Publish to MQTT
        if (json_payload != NULL)
        {
            mqtt_publish(json_payload);
            free(json_payload);   //  VERY IMPORTANT, to ensure there is no Memory leaks
            json_payload = NULL;
        }
        else
        {
            ESP_LOGE(TAG, "Failed to build JSON payload");
        }

        ESP_LOGI(TAG, "Cycle complete, waiting...");

        // Delay (1 second)
        vTaskDelay(pdMS_TO_TICKS(CONFIG_PUBLISH_INTERVAL_MS));
    }
}
