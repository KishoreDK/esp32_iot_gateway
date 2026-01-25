#pragma once

#include "sensors.h"

// Build structured JSON payload from sensor data
// Returned string must be freed by caller
char *payload_build(sensor_data_t *data);
