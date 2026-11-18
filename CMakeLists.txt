# sdlarc: the Acorn Archimedes with SDL 3.
#
#   cmake -S . -B build -G Ninja && cmake --build build
#   build/sdlarc --help
#
# The Archimedes itself is esp32arc's (../esp32arc/components/archimedes,
# platform independent), the runtime sdlemu's (../sdlemu), the ARM2
# esp32emu's (../esp32emu): all four cloned side by side.
cmake_minimum_required(VERSION 3.20)
project(sdlarc C)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "" FORCE)
endif()

set(ESP32ARC_DIR "${CMAKE_CURRENT_LIST_DIR}/../esp32arc" CACHE PATH "esp32arc checkout: the Archimedes")
if(NOT EXISTS "${ESP32ARC_DIR}/components/archimedes/include/arc.h")
    message(FATAL_ERROR "No esp32arc at ${ESP32ARC_DIR}: clone github.com/rlucencic/esp32arc beside sdlarc")
endif()

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../sdlemu" sdlemu)

file(GLOB ARC_SOURCES "${ESP32ARC_DIR}/components/archimedes/*.c")
add_executable(sdlarc
    src/main.c
    src/settings.c
    src/rom_store.c
    ${ARC_SOURCES})
target_include_directories(sdlarc PRIVATE
    src
    "${ESP32ARC_DIR}/components/archimedes/include"
    "${ESP32ARC_DIR}/components/archimedes")
sdlemu_add_cores(sdlarc arm2 diskspace)
target_link_libraries(sdlarc PRIVATE sdlemu)
target_compile_options(sdlarc PRIVATE -Wall -Wextra -Wno-unused-parameter -Wno-unused-result)

install(TARGETS sdlarc)
