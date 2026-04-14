add_executable(SmartLedTest
    main.cpp
)

target_link_libraries(SmartLedTest
        pico_stdlib
        SmartLed
)

target_include_directories(SmartLedTest
        PRIVATE ${PROJECT_SOURCE_DIR}/include
)

pico_enable_stdio_uart(SmartLedTest 0)
pico_enable_stdio_usb(SmartLedTest 1)

pico_add_extra_outputs(SmartLedTest)

