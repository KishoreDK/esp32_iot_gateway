#include "unity.h"
#include "sensors.h"

/*
 * UNIT TEST:
 * Validate that sensors_read_all()
 * returns a valid structure with sane values.
 * No real hardware is required.
 */
void test_sensors_read_all_returns_valid_data(void)
{
    sensor_data_t data = sensors_read_all();

    // Structure should exist
    TEST_ASSERT_NOT_EQUAL(0, sizeof(data));

    // Basic sanity checks (mock values)
    TEST_ASSERT_TRUE(data.temperature > -50);
    TEST_ASSERT_TRUE(data.temperature < 100);

    TEST_ASSERT_TRUE(data.humidity >= 0);
    TEST_ASSERT_TRUE(data.humidity <= 100);
}

/*
 * Unity test entry point
 */
void app_main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_sensors_read_all_returns_valid_data);

    UNITY_END();
}
