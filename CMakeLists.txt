# rpi5arc: the Acorn Archimedes on the Raspberry Pi 5.
#
#   cmake -S . -B build -G Ninja && cmake --build build
#   build/rpi5arc --help
#
# The Archimedes itself is esp32arc's (../esp32arc/components/archimedes,
# platform independent), the runtime rpi5emu's (../rpi5emu), the ARM2
# esp32emu's (../esp32emu): all four cloned side by side.
cmake_minimum_required(VERSION 3.20)
project(rpi5arc C)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "" FORCE)
endif()

set(ESP32ARC_DIR "${CMAKE_CURRENT_LIST_DIR}/../esp32arc" CACHE PATH "esp32arc checkout: the Archimedes")
if(NOT EXISTS "${ESP32ARC_DIR}/components/archimedes/include/arc.h")
    message(FATAL_ERROR "No esp32arc at ${ESP32ARC_DIR}: clone github.com/rlucencic/esp32arc beside rpi5arc")
endif()

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../rpi5emu" rpi5emu)

file(GLOB ARC_SOURCES "${ESP32ARC_DIR}/components/archimedes/*.c")
add_executable(rpi5arc
    src/main.c
    src/settings.c
    src/rom_store.c
    ${ARC_SOURCES})
target_include_directories(rpi5arc PRIVATE
    src
    "${ESP32ARC_DIR}/components/archimedes/include"
    "${ESP32ARC_DIR}/components/archimedes")
rpi5emu_add_cores(rpi5arc arm2 diskspace)
target_link_libraries(rpi5arc PRIVATE rpi5emu)
target_compile_options(rpi5arc PRIVATE -Wall -Wextra -Wno-unused-parameter -Wno-unused-result)

install(TARGETS rpi5arc)
