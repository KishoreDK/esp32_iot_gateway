#include "actuators.h"
#include "esp_log.h"
#include "string.h"
#include "cJSON.h"

static const char *TAG = "ACTUATORS";

/* -------------------------------------------------
 * INTERNAL HELPERS
 * -------------------------------------------------*/

/*
 * Convert actuator name string to enum.
 * Keeps string handling out of core logic.
 */
static actuator_type_t parse_actuator_type(const char *type)
{
    if (strcmp(type, "led") == 0) return ACTUATOR_LED;
    if (strcmp(type, "relay") == 0) return ACTUATOR_RELAY;
    if (strcmp(type, "buzzer") == 0) return ACTUATOR_BUZZER;
    if (strcmp(type, "motor") == 0) return ACTUATOR_MOTOR;
    if (strcmp(type, "servo") == 0) return ACTUATOR_SERVO;

    return ACTUATOR_UNKNOWN;
}

/*
 * Execute actuator command.
 * Currently MOCK implementation.
 * Real GPIO / PWM logic will come later.
 */
static void execute_actuator_command(actuator_cmd_t *cmd)
{
    switch (cmd->type) {

        case ACTUATOR_LED:
            ESP_LOGI(TAG, "LED action: %s", cmd->action);
            break;

        case ACTUATOR_RELAY:
            ESP_LOGI(TAG, "Relay action: %s", cmd->action);
            break;

        case ACTUATOR_BUZZER:
            ESP_LOGI(TAG, "Buzzer action: %s", cmd->action);
            break;

        case ACTUATOR_MOTOR:
            ESP_LOGI(TAG, "Motor action: %s, value: %d",
                     cmd->action, cmd->value);
            break;

        case ACTUATOR_SERVO:
            ESP_LOGI(TAG, "Servo action: %s, angle: %d",
                     cmd->action, cmd->value);
            break;

        default:
            ESP_LOGW(TAG, "Unknown actuator type");
            break;
    }
}

/* -------------------------------------------------
 * PUBLIC API
 * -------------------------------------------------*/

/*
 * Handles incoming actuator command JSON.
 *
 * Expected JSON format:
 * {
 *   "target": "led",
 *   "action": "on"
 * }
 *
 * or
 *
 * {
 *   "target": "servo",
 *   "action": "set",
 *   "value": 90
 * }
 */
void actuators_handle_command(const char *json_cmd)
{
    ESP_LOGI(TAG, "Received raw command JSON: %s", json_cmd);

    cJSON *root = cJSON_Parse(json_cmd);
    if (root == NULL) {
        ESP_LOGE(TAG, "JSON parse failed");
        return;
    }

    /* -------- Validate device_id -------- */
    cJSON *device_id = cJSON_GetObjectItem(root, "device_id");
    if (!cJSON_IsString(device_id)) {
        ESP_LOGE(TAG, "Missing or invalid device_id");
        cJSON_Delete(root);
        return;
    }

    // Optional: later match against this ESP32's ID
    ESP_LOGI(TAG, "Command intended for device: %s",
             device_id->valuestring);

    /* -------- Extract command object -------- */
    cJSON *command = cJSON_GetObjectItem(root, "command");
    if (!cJSON_IsObject(command)) {
        ESP_LOGE(TAG, "Missing command object");
        cJSON_Delete(root);
        return;
    }

    cJSON *target = cJSON_GetObjectItem(command, "target");
    cJSON *action = cJSON_GetObjectItem(command, "action");
    cJSON *value  = cJSON_GetObjectItem(command, "value");

    if (!cJSON_IsString(target) || !cJSON_IsString(action)) {
        ESP_LOGE(TAG, "Invalid target or action");
        cJSON_Delete(root);
        return;
    }

    /* -------- Build internal command -------- */
    actuator_cmd_t cmd = {0};
    cmd.type = parse_actuator_type(target->valuestring);
    strncpy(cmd.action, action->valuestring,
            sizeof(cmd.action) - 1);

    if (cJSON_IsNumber(value)) {
        cmd.value = value->valueint;
    }

    /* -------- Execute -------- */
    execute_actuator_command(&cmd);

    cJSON_Delete(root);
}

