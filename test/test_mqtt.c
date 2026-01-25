#include "unity.h"
#include "mqtt.h"

void test_mqtt_publish_null_payload(void)
{
    mqtt_publish(NULL);
    TEST_PASS();
}

void app_main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_mqtt_publish_null_payload);
    UNITY_END();
}
