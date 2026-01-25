#include "unity.h"
#include "payload.h"
#include "actuators.h"

/*
 * UNIT TEST:
 * Payload builder should handle NULL input safely
 */
void test_payload_null_input(void)
{
    char *json = payload_build(NULL);

    TEST_ASSERT_NULL(json);
}

/*
 * UNIT TEST:
 * Actuator should ignore unknown target
 */
void test_actuator_unknown_target(void)
{
    const char *cmd =
        "{"
        "\"device_id\":\"esp32-gateway-01\","
        "\"command\":{"
            "\"target\":\"unknown_device\","
            "\"action\":\"on\""
        "}"
        "}";

    actuators_handle_command(cmd);

    TEST_PASS();
}

/*
 * UNIT TEST:
 * Actuator should ignore missing command object
 */
void test_actuator_missing_command(void)
{
    const char *cmd =
        "{"
        "\"device_id\":\"esp32-gateway-01\""
        "}";

    actuators_handle_command(cmd);

    TEST_PASS();
}

void app_main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_payload_null_input);
    RUN_TEST(test_actuator_unknown_target);
    RUN_TEST(test_actuator_missing_command);
    UNITY_END();
}
