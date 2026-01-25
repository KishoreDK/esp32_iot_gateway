idf_component_register(
    SRCS
        "app_main.c"

        "wifi/wifi.c"
        "mqtt/mqtt.c"
        "sensors/sensors.c"
        "payload/payload.c"
        "actuators/actuators.c"

        "protocols/i2c_bus.c"
        "protocols/spi_bus.c"
        "protocols/can_bus.c"
        "protocols/uart_bus.c"

    INCLUDE_DIRS
        "."
        "wifi"
        "mqtt"
        "sensors"
        "payload"
        "actuators"
        "protocols"
)
