cmake_minimum_required(VERSION 3.10)
project(Tests C)

set(CMAKE_C_STANDARD 99)

include_directories(unity/src)
include_directories(src)

add_library(unity unity/src/unity.c)

add_executable(test_main tests/test_main.c src/temp_converter.c src/main.c)
target_link_libraries(test_main unity)

add_executable(test_temp_converter tests/test_temp_converter.c src/main.c src/temp_converter.c src/temp_sensor.c)
target_link_libraries(test_temp_converter unity)

add_executable(test_temp_sensor tests/test_temp_sensor.c src/main.c src/temp_sensor.c)
target_link_libraries(test_temp_sensor unity)

