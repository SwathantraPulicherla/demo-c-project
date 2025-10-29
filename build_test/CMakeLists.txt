cmake_minimum_required(VERSION 3.10)
project(AITestRunner LANGUAGES C)

# C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Coverage flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")

# Windows/MinGW fallback
if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--allow-multiple-definition")
endif()

# Include directories
include_directories(src)
include_directories(unity/src)
include_directories(tests)

# Unity source
set(UNITY_SRC unity/src/unity.c)
# Testing temp_converter – module + direct dependencies
add_executable(test_temp_converter
    tests/test_temp_converter.c
    ${UNITY_SRC}
    src/temp_converter.c
)
add_test(NAME test_temp_converter COMMAND test_temp_converter)

# Testing temp_sensor – module + direct dependencies
add_executable(test_temp_sensor
    tests/test_temp_sensor.c
    ${UNITY_SRC}
    src/temp_sensor.c
    src/temp_converter.c
)
add_test(NAME test_temp_sensor COMMAND test_temp_sensor)

enable_testing()
