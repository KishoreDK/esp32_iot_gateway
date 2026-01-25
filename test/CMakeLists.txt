idf_component_register(
    SRCS
        "test_sensors.c"
        "test_payload.c"
        "test_actuators.c"
        "test_negative.c"
    INCLUDE_DIRS "."
    REQUIRES unity sensors payload actuators
)
