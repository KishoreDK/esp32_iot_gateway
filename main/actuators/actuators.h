#pragma once

/*
 * Supported actuator types.
 * These map to real hardware later.
 */
typedef enum {
    ACTUATOR_LED,
    ACTUATOR_RELAY,
    ACTUATOR_BUZZER,
    ACTUATOR_MOTOR,
    ACTUATOR_SERVO,
    ACTUATOR_UNKNOWN
} actuator_type_t;

/*
 * Generic actuator command structure.
 * Parsed from incoming MQTT JSON.
 */
typedef struct {
    actuator_type_t type;   // LED / RELAY / MOTOR / etc.
    char action[16];        // "on", "off", "set"
    int value;              // PWM / angle / speed (optional)
} actuator_cmd_t;

/*
 * Entry point called by MQTT layer.
 * Accepts raw JSON command string.
 */
void actuators_handle_command(const char *json_cmd);
