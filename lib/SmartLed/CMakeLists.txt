add_library(SmartLed STATIC
    SmartLed.cpp
)

# Header pubblici: chiunque faccia target_link_libraries(... tm1637)
# riceve automaticamente questo include path
message("Using *Public* directory '${CMAKE_CURRENT_LIST_DIR}'")
target_include_directories(SmartLed
        PUBLIC ${CMAKE_CURRENT_LIST_DIR}
)

# Collega le dipendenze dell'SDK Pico necessarie alla libreria
target_link_libraries(SmartLed
        pico_stdlib
        hardware_gpio
)