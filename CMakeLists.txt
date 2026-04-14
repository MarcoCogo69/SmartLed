cmake_minimum_required(VERSION 3.13)

# Importa l'SDK
if (DEFINED ENV{PICO_SDK_PATH} AND (NOT PICO_SDK_PATH))
    set(PICO_SDK_PATH $ENV{PICO_SDK_PATH})
    message("Using PICO_SDK_PATH from environment ('${PICO_SDK_PATH}')")
endif ()
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(SmartLedPrj)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_subdirectory(lib)
add_subdirectory(src)