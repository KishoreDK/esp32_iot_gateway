#include "unity.h"
#include "payload.h"
#include "sensors.h"
#include <string.h>

/*
 * UNIT TEST:
 * Verify payload_build() creates valid JSON
 * and contains mandatory fields.
 */
void test_payload_build_valid_json(void)
{
    sensor_data_t data = sensors_read_all();

    char *json = payload_build(&data);

    // JSON must be created
    TEST_ASSERT_NOT_NULL(json);

    // Mandatory JSON keys
    TEST_ASSERT_NOT_NULL(strstr(json, "device_id"));
    TEST_ASSERT_NOT_NULL(strstr(json, "sensors"));
    TEST_ASSERT_NOT_NULL(strstr(json, "temperature"));
    TEST_ASSERT_NOT_NULL(strstr(json, "humidity"));

    // Free heap memory
    free(json);
}

/*
 * Unity entry point
 */
void app_main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_payload_build_valid_json);
    UNITY_END();
}
