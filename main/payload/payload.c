#include "payload.h"
#include "cJSON.h"
#include "esp_timer.h"

/*
 * Builds a structured JSON payload.
 * Uses cJSON (already part of ESP-IDF).
 *
 * IMPORTANT:
 * - Caller must free the returned string using free()
 */
char *payload_build(sensor_data_t *data)
{
    if (data == NULL)       //Added NULL safety
    {
    return NULL;
    }

    // Root JSON object
    cJSON *root = cJSON_CreateObject();

    // ---------------- DEVICE INFO ----------------
    cJSON *device = cJSON_CreateObject();
    cJSON_AddStringToObject(device, "id", CONFIG_DEVICE_ID);

    // Uptime in seconds
    int64_t uptime_us = esp_timer_get_time();
    cJSON_AddNumberToObject(device, "uptime_sec", uptime_us / 1000000);

    cJSON_AddItemToObject(root, "device", device);

    // ---------------- SENSOR DATA ----------------
cJSON *sensors = cJSON_CreateObject();

cJSON_AddNumberToObject(sensors, "temperature", data->temperature);
cJSON_AddNumberToObject(sensors, "humidity", data->humidity);
cJSON_AddNumberToObject(sensors, "motion", data->motion);
cJSON_AddNumberToObject(sensors, "flame", data->flame);
cJSON_AddNumberToObject(sensors, "rain", data->rain);
cJSON_AddNumberToObject(sensors, "door", data->door);

cJSON_AddNumberToObject(sensors, "soil_moisture", data->soil_moisture);
cJSON_AddNumberToObject(sensors, "light", data->light);
cJSON_AddNumberToObject(sensors, "gas", data->gas);
cJSON_AddNumberToObject(sensors, "sound", data->sound);
cJSON_AddNumberToObject(sensors, "potentiometer", data->potentiometer);

cJSON_AddItemToObject(root, "sensors", sensors);


    // ---------------- SYSTEM STATUS ----------------
    cJSON *status = cJSON_CreateObject();
    cJSON_AddStringToObject(status, "wifi", "connected");
    cJSON_AddStringToObject(status, "mqtt", "connected");

    cJSON_AddItemToObject(root, "status", status);

    // Convert JSON object to string (compact, no formatting)
    char *json_string = cJSON_PrintUnformatted(root);

    // Free JSON structure (string remains)
    cJSON_Delete(root);

    return json_string;
}
