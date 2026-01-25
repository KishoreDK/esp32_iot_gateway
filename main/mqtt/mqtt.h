#pragma once

// Initialize MQTT client and connect to broker
void mqtt_init(void);

// Publish JSON payload to MQTT broker
void mqtt_publish(const char *payload);
