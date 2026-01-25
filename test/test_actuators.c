#include "unity.h"
#include "actuators.h"

/*
 * UNIT TEST:
 * Valid actuator command should not crash
 */
void test_actuator_valid_command(void)
{
    const char *cmd =
        "{"
        "\"device_id\":\"esp32-gateway-01\","
        "\"command\":{"
            "\"target\":\"led\","
            "\"action\":\"on\""
        "}"
        "}";

    actuators_handle_command(cmd);

    TEST_PASS();  // If no crash, test passes
}

/*
 * UNIT TEST:
 * Invalid JSON must fail safely
 */
void test_actuator_invalid_json(void)
{
    const char *cmd = "{ invalid json ";

    actuators_handle_command(cmd);

    TEST_PASS();  // Must not crash
}

void app_main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_actuator_valid_command);
    RUN_TEST(test_actuator_invalid_json);
    UNITY_END();
}
