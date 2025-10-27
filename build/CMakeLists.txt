cmake_minimum_required(VERSION 3.10)
project(AITestRunner)

# Set C standard
set(CMAKE_C_STANDARD 99)

# Add coverage flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")

# For MinGW/Windows, ensure console application
if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-subsystem,console -Wl,--allow-multiple-definition")
endif()

# Include directories
include_directories(src)
include_directories(unity/src)

# Test executables (each test includes relevant source files)
add_executable(test_temp_converter tests/test_temp_converter.c unity/src/unity.c src/main.c src/temp_sensor.c src/temp_converter.c)
add_test(NAME test_temp_converter COMMAND test_temp_converter)

add_executable(test_temp_sensor tests/test_temp_sensor.c unity/src/unity.c src/main.c src/temp_sensor.c src/temp_converter.c)
add_test(NAME test_temp_sensor COMMAND test_temp_sensor)


# Enable testing
enable_testing()
