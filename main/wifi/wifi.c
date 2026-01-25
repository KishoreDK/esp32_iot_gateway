#include "wifi.h"

// FreeRTOS and ESP-IDF core includes
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

// Tag used for logging
static const char *TAG = "WIFI";

// Event group to signal Wi-Fi connection status
static EventGroupHandle_t wifi_event_group;

// Bit used to indicate Wi-Fi connected
#define WIFI_CONNECTED_BIT BIT0

/*
 * Wi-Fi event handler
 * This function is called automatically by ESP-IDF
 * whenever a Wi-Fi related event occurs.
 */
static void wifi_event_handler(void *arg,
                               esp_event_base_t event_base,
                               int32_t event_id,
                               void *event_data)
{
    // Wi-Fi started
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        ESP_LOGI(TAG, "Wi-Fi started, attempting to connect...");
        esp_wifi_connect();
    }

    // Wi-Fi disconnected
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        ESP_LOGW(TAG, "Wi-Fi disconnected, retrying...");
        esp_wifi_connect();
    }

    // Got IP address (successful connection)
    else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ESP_LOGI(TAG, "Wi-Fi connected, IP address acquired");
        xEventGroupSetBits(wifi_event_group, WIFI_CONNECTED_BIT);
    }
}

/*
 * Initializes Wi-Fi in Station mode
 * This is real ESP-IDF Wi-Fi setup code
 */
void wifi_init(void)
{
    ESP_LOGI(TAG, "Initializing Wi-Fi (real ESP-IDF code)");

    // Initialize NVS (required for Wi-Fi)
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES ||
        ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        nvs_flash_erase();
        nvs_flash_init();
    }

    // Create event group
    wifi_event_group = xEventGroupCreate();

    // Initialize TCP/IP stack
    ESP_ERROR_CHECK(esp_netif_init());

    // Create default event loop
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    // Create default Wi-Fi STA interface
    esp_netif_create_default_wifi_sta();

    // Wi-Fi initialization with default config
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    // Register Wi-Fi event handler
    ESP_ERROR_CHECK(
        esp_event_handler_register(WIFI_EVENT,
                                   ESP_EVENT_ANY_ID,
                                   &wifi_event_handler,
                                   NULL));

    // Register IP event handler
    ESP_ERROR_CHECK(
        esp_event_handler_register(IP_EVENT,
                                   IP_EVENT_STA_GOT_IP,
                                   &wifi_event_handler,
                                   NULL));

    // Wi-Fi configuration (SSID & password are placeholders)
    wifi_config_t wifi_config = {
        .sta = {
            .ssid = "YOUR_WIFI_SSID",
            .password = "YOUR_WIFI_PASSWORD",
        },
    };

    // Set Wi-Fi mode to Station
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));

    // Apply Wi-Fi configuration
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));

    // Start Wi-Fi
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "Wi-Fi initialization complete");
}
