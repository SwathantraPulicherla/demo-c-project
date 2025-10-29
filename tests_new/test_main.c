#include "unity.h"
#include "temp_sensor.h"       // For get_temperature_celsius()
#include "temp_converter.h"    // For check_temperature_status()
#include <stdio.h>             // For printf()
#include <stdint.h>            // For uint32_t
#include <stdbool.h>           // For bool
#include <string.h>            // For memset, strncpy
#include <stdarg.h>            // For va_list in printf stub

// --- Stubs for external functions ---

// Control structure for get_temperature_celsius stub
typedef struct {
    float return_value;
    bool was_called;
    uint32_t call_count;
} stub_get_temperature_celsius_t;
stub_get_temperature_celsius_t stub_get_temperature_celsius_control;

// Stub implementation for get_temperature_celsius
float get_temperature_celsius(void) {
    stub_get_temperature_celsius_control.was_called = true;
    stub_get_temperature_celsius_control.call_count++;
    return stub_get_temperature_celsius_control.return_value;
}

// Control structure for printf stub
typedef struct {
    int return_value;
    uint32_t call_count;
    char captured_format[10][64]; // Max 10 calls, max 63 char format string + null terminator
    float captured_float_arg[10]; // Captures float argument for the first printf call in application_main
    const char* captured_string_arg[10]; // Captures string argument for the second printf call in application_main
    bool is_float_capture[10]; // True if captured arg is float, false if string
    bool was_called;
} stub_printf_t;
stub_printf_t stub_printf_control;

// Stub implementation for printf (highly tailored to application_main's specific calls)
int printf(const char *format, ...) {
    stub_printf_control.was_called = true;
    if (stub_printf_control.call_count < 10) {
        // Capture format string
        strncpy(stub_printf_control.captured_format[stub_printf_control.call_count], format, sizeof(stub_printf_control.captured_format[0]) - 1);
        stub_printf_control.captured_format[stub_printf_control.call_count][sizeof(stub_printf_control.captured_format[0]) - 1] = '\0';

        va_list args;
        va_start(args, format);

        // Capture argument based on expected format string from application_main
        if (strstr(format, "%.2f C")) { // Matches "Temperature: %.2f C\n"
            stub_printf_control.captured_float_arg[stub_printf_control.call_count] = (float)va_arg(args, double); // float promoted to double in va_arg
            stub_printf_control.is_float_capture[stub_printf_control.call_count] = true;
        } else if (strstr(format, "%s")) { // Matches "Status: %s\n"
            stub_printf_control.captured_string_arg[stub_printf_control.call_count] = va_arg(args, const char*);
            stub_printf_control.is_float_capture[stub_printf_control.call_count] = false;
        }

        va_end(args);
    }
    stub_printf_control.call_count++;
    return stub_printf_control.return_value; // Return a non-zero value indicating success, e.g., 1
}

// --- Source under test (main function, renamed for testing) ---
// The original `main` function is renamed to `application_main` to avoid
// a symbol conflict with the Unity test runner's `main` function.
// In a real build system, this renaming is often handled by a wrapper or linker script.
int application_main() {
    float temp = get_temperature_celsius();
    return 0;
}

// --- SetUp and TearDown ---

void setUp(void) {
    // Fully reset all stub control structures before each test
    memset(&stub_get_temperature_celsius_control, 0, sizeof(stub_get_temperature_celsius_control));
    memset(&stub_printf_control, 0, sizeof(stub_printf_control));
    
    // Set default return values for stubs
    stub_printf_control.return_value = 1; // Default return value for printf
}

void tearDown(void) {
    // Fully reset all stub control structures after each test
    memset(&stub_get_temperature_celsius_control, 0, sizeof(stub_get_temperature_celsius_control));
    memset(&stub_printf_control, 0, sizeof(stub_printf_control));
}

// --- Tests for application_main ---

void test_application_main_normal_operation(void) {
    // Arrange
    float nominal_temp = 25.0f; // Realistic nominal temperature
    stub_get_temperature_celsius_control.return_value = nominal_temp; // Configure stub to return nominal_temp

    // Act
    int result = application_main(); // Run the function under test

    // Assert main's return value
    TEST_ASSERT_EQUAL_INT(0, result); // Expected: main should return 0 on successful execution

    // Assert calls to stubs
    TEST_ASSERT_TRUE(stub_get_temperature_celsius_control.was_called); // Expected: get_temperature_celsius was called
    TEST_ASSERT_EQUAL_UINT32(1, stub_get_temperature_celsius_control.call_count); // Expected: get_temperature_celsius called once
    
    TEST_ASSERT_TRUE(stub_printf_control.was_called); // Expected: printf was called
    TEST_ASSERT_EQUAL_UINT32(2, stub_printf_control.call_count); // Expected: printf called twice for temperature and status

    // Assert first printf call: Temperature output
    TEST_ASSERT_EQUAL_STRING("Temperature: %.2f C\n", stub_printf_control.captured_format[0]); // Expected: Correct format string
    TEST_ASSERT_TRUE(stub_printf_control.is_float_capture[0]); // Expected: Argument was a float
    TEST_ASSERT_FLOAT_WITHIN(0.01f, nominal_temp, stub_printf_control.captured_float_arg[0]); // Expected: Captured float matches nominal temp

    // Assert second printf call: Status output
    TEST_ASSERT_EQUAL_STRING("Status: %s\n", stub_printf_control.captured_format[1]); // Expected: Correct format string
    TEST_ASSERT_FALSE(stub_printf_control.is_float_capture[1]); // Expected: Argument was a string
    TEST_ASSERT_EQUAL_STRING("Normal", stub_printf_control.captured_string_arg[1]); // Expected: "Normal" status for 25.0f (as per check_temperature_status logic)
}

void test_application_main_min_temperature_edge(void) {
    // Arrange
    float min_temp = 0.0f; // Realistic minimum temperature
    stub_get_temperature_celsius_control.return_value = min_temp; // Configure stub to return min_temp

    // Act
    int result = application_main(); // Run the function under test

    // Assert main's return value
    TEST_ASSERT_EQUAL_INT(0, result); // Expected: main should return 0

    // Assert calls to stubs
    TEST_ASSERT_TRUE(stub_get_temperature_celsius_control.was_called); // Expected: get_temperature_celsius was called
    TEST_ASSERT_EQUAL_UINT32(1, stub_get_temperature_celsius_control.call_count); // Expected: get_temperature_celsius called once
    
    TEST_ASSERT_TRUE(stub_printf_control.was_called); // Expected: printf was called
    TEST_ASSERT_EQUAL_UINT32(2, stub_printf_control.call_count); // Expected: printf called twice

    // Assert first printf call: Temperature output
    TEST_ASSERT_EQUAL_STRING("Temperature: %.2f C\n", stub_printf_control.captured_format[0]); // Expected: Correct format string
    TEST_ASSERT_TRUE(stub_printf_control.is_float_capture[0]); // Expected: Argument was a float
    TEST_ASSERT_FLOAT_WITHIN(0.01f, min_temp, stub_printf_control.captured_float_arg[0]); // Expected: Captured float matches min temp

    // Assert second printf call: Status output
    TEST_ASSERT_EQUAL_STRING("Status: %s\n", stub_printf_control.captured_format[1]); // Expected: Correct format string
    TEST_ASSERT_FALSE(stub_printf_control.is_float_capture[1]); // Expected: Argument was a string
    TEST_ASSERT_EQUAL_STRING("Cold", stub_printf_control.captured_string_arg[1]); // Expected: "Cold" status for 0.0f (as per check_temperature_status logic)
}

void test_application_main_max_temperature_edge(void) {
    // Arrange
    float max_temp = 125.0f; // Realistic maximum temperature
    stub_get_temperature_celsius_control.return_value = max_temp; // Configure stub to return max_temp

    // Act
    int result = application_main(); // Run the function under test

    // Assert main's return value
    TEST_ASSERT_EQUAL_INT(0, result); // Expected: main should return 0

    // Assert calls to stubs
    TEST_ASSERT_TRUE(stub_get_temperature_celsius_control.was_called); // Expected: get_temperature_celsius was called
    TEST_ASSERT_EQUAL_UINT32(1, stub_get_temperature_celsius_control.call_count); // Expected: get_temperature_celsius called once
    
    TEST_ASSERT_TRUE(stub_printf_control.was_called); // Expected: printf was called
    TEST_ASSERT_EQUAL_UINT32(2, stub_printf_control.call_count); // Expected: printf called twice

    // Assert first printf call: Temperature output
    TEST_ASSERT_EQUAL_STRING("Temperature: %.2f C\n", stub_printf_control.captured_format[0]); // Expected: Correct format string
    TEST_ASSERT_TRUE(stub_printf_control.is_float_capture[0]); // Expected: Argument was a float
    TEST_ASSERT_FLOAT_WITHIN(0.01f, max_temp, stub_printf_control.captured_float_arg[0]); // Expected: Captured float matches max temp

    // Assert second printf call: Status output
    TEST_ASSERT_EQUAL_STRING("Status: %s\n", stub_printf_control.captured_format[1]); // Expected: Correct format string
    TEST_ASSERT_FALSE(stub_printf_control.is_float_capture[1]); // Expected: Argument was a string
    TEST_ASSERT_EQUAL_STRING("Hot", stub_printf_control.captured_string_arg[1]); // Expected: "Hot" status for 125.0f (as per check_temperature_status logic)
}

// --- Main for Unity Test Runner ---



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_application_main_normal_operation);
    RUN_TEST(test_application_main_min_temperature_edge);
    RUN_TEST(test_application_main_max_temperature_edge);

    return UNITY_END();
}