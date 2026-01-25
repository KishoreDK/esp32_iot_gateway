#include "mqtt.h"

#include "esp_log.h"
#include "mqtt_client.h"
#include "string.h"

#include "actuators.h"   // To handle commands from Pi

static const char *TAG = "MQTT";

// MQTT client handle (global for reuse)
static esp_mqtt_client_handle_t mqtt_client = NULL;

/*
 * MQTT event handler
 * Called automatically by ESP-IDF when MQTT events occur
 */
static void mqtt_event_handler(void *handler_args,
                               esp_event_base_t base,
                               int32_t event_id,
                               void *event_data)
{
    esp_mqtt_event_handle_t event = event_data;

    switch (event->event_id) {

        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(TAG, "MQTT connected");

            // Subscribe to command topic (Pi → ESP32)
            esp_mqtt_client_subscribe(mqtt_client,
                                      CONFIG_MQTT_SUB_TOPIC,
                                      0);
            ESP_LOGI(TAG, "Subscribed to iot/esp32/cmd");
            break;

        case MQTT_EVENT_DATA:
            ESP_LOGI(TAG, "MQTT data received");

            // Copy payload safely (not null-terminated)
            char cmd[128] = {0};
            memcpy(cmd, event->data, event->data_len);

            ESP_LOGI(TAG, "Command received: %s", cmd);

            // Forward command to actuators module
            actuators_handle_command(cmd);
            break;

        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGW(TAG, "MQTT disconnected");
            break;

        default:
            break;
    }
}

/*
 * Initialize MQTT client
 * Uses ESP-IDF native MQTT
 */
void mqtt_init(void)
{
    ESP_LOGI(TAG, "Initializing MQTT");

    // MQTT broker configuration
    esp_mqtt_client_config_t mqtt_cfg = {
        .broker.address.uri = CONFIG_MQTT_BROKER_URI, // public broker (safe for dev)
    };

    // Create MQTT client
    mqtt_client = esp_mqtt_client_init(&mqtt_cfg);

    // Register event handler
    esp_mqtt_client_register_event(mqtt_client,
                                   ESP_EVENT_ANY_ID,
                                   mqtt_event_handler,
                                   NULL);

    // Start MQTT client
    esp_mqtt_client_start(mqtt_client);
}

/*
 * Publish JSON payload to MQTT broker
 */
void mqtt_publish(const char *payload)
{
    if (mqtt_client == NULL) {
        ESP_LOGW(TAG, "MQTT client not initialized");
        return;
    }

    if (payload == NULL) {
        ESP_LOGW(TAG, "MQTT payload is NULL");
        return;
    }

    int msg_id = esp_mqtt_client_publish(
                    mqtt_client,
                    CONFIG_MQTT_PUB_TOPIC,
                    payload,
                    0,
                    1,
                    0);

    if (msg_id == -1) {
        ESP_LOGW(TAG, "MQTT publish failed");
    } else {
        ESP_LOGD(TAG, "MQTT published, msg_id=%d", msg_id);
    }
}

