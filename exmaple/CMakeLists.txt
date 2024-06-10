cmake_minimum_required(VERSION 3.20)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (DEFINED ENV{PICO_SDK_PATH})
  set(PICO_SDK_PATH "$ENV{PICO_SDK_PATH}")
else()
  set(PICO_SDK_PATH "/opt/pico/pico-sdk")
endif()

set(PICO_BOARD pico_w CACHE STRING "Board type")

include("${PICO_SDK_PATH}/external/pico_sdk_import.cmake")

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.5.1")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.5.1 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

project(hello-pico C CXX ASM)

pico_sdk_init()

add_executable(hello_world hello_world.cpp)
target_link_libraries(hello_world pico_stdlib)
# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(hello_world)

pico_enable_stdio_uart(hello_world 1)
pico_enable_stdio_usb (hello_world 0)
