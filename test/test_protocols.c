#include "unity.h"
#include "i2c_bus.h"
#include "spi_bus.h"
#include "can_bus.h"
#include "uart_bus.h"

void test_protocol_init_functions(void)
{
    i2c_bus_init();
    spi_bus_init();
    can_bus_init();
    uart_bus_init();
    TEST_PASS();
}

void app_main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_protocol_init_functions);
    UNITY_END();
}
