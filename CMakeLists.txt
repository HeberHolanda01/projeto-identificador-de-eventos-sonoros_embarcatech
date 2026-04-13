cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# == DO NOT EDIT (VS CODE PICO EXTENSION) ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()

set(sdkVersion 2.2.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.2.0-a4)

set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# =========================================

set(PICO_BOARD pico_w CACHE STRING "Board type")

include(pico_sdk_import.cmake)

project(blink C CXX ASM)

pico_sdk_init()

# =======================
# EXECUTÁVEL
# =======================
add_executable(blink
    blink.c
)

# =======================
# BIBLIOTECAS (CORRIGIDO)
# =======================
target_link_libraries(blink
    pico_stdlib
    hardware_adc
    hardware_pwm
    hardware_i2c
    hardware_pio
)

# =======================
# USB SERIAL
# =======================
pico_enable_stdio_usb(blink 1)
pico_enable_stdio_uart(blink 0)

# =======================
# OUTPUTS
# =======================
pico_add_extra_outputs(blink)