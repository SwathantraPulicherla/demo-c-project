/* test_main.c – Auto-generated Expert Unity Tests */

#include "unity.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h> // Required for memset

// External function declaration for main() from src/main.c
// This allows the test runner to call main() directly.
extern int main(void);

// === Stub Definitions for External Dependencies ===

// Stub control structure for get_temperature_celsius()
// Signature inferred from main.c: float temp = get_temperature_celsius();
typedef struct {
    float return_value;
    bool was_called;
    uint32_t call_count;
} stub_get_temperature_celsius_t;
static stub_get_temperature_celsius_t stub_get_temperature_celsius_data;

// Stub implementation for get_temperature_celsius()
float get_temperature_celsius(void) {
    stub_get_temperature_celsius_data.was_called = true;
    stub_get_temperature_celsius_data.call_count++;
    return stub_get_temperature_celsius_data.return_value;
}

// Stub control structure for check_temperature_status()
// Signature inferred from main.c: check_temperature_status(temp) returns char* (or const char* for status strings)
typedef struct {
    const char* return_value;
    bool was_called;
    uint32_t call_count;
    float captured_temperature; // To capture the parameter passed to the stub
} stub_check_temperature_status_t;
static stub_check_temperature_status_t stub_check_temperature_status_data;

// Stub implementation for check_temperature_status()
const char* check_temperature_status(float temperature) {
    stub_check_temperature_status_data.was_called = true;
    stub_check_temperature_status_data.call_count++;
    stub_check_temperature_status_data.captured_temperature = temperature;
    return stub_check_temperature_status_data.return_value;
}

// === Unity Test Framework Setup and Teardown ===

// setUp() is called before each test function
void setUp(void) {
    // Completely reset all stub control data structures
    memset(&stub_get_temperature_celsius_data, 0, sizeof(stub_get_temperature_celsius_data));
    memset(&stub_check_temperature_status_data, 0, sizeof(stub_check_temperature_status_data));

    // Set default or nominal return values for stubs for general use
    stub_get_temperature_celsius_data.return_value = 25.0f; // Nominal ambient temperature
    stub_check_temperature_status_data.return_value = "NORMAL"; // Default status for nominal temp
}

// tearDown() is called after each test function
void tearDown(void) {
    // Ensure all stub control data structures are completely reset after each test.
    // This provides maximal isolation and guards against potential side effects if a test fails early.
    memset(&stub_get_temperature_celsius_data, 0, sizeof(stub_get_temperature_celsius_data));
    memset(&stub_check_temperature_status_data, 0, sizeof(stub_check_temperature_status_data));
}

// === Test Cases for main() ===

/**
 * @brief Test to verify main() correctly orchestrates calls to its dependencies
 *        and returns the expected value (0).
 *
 * This test covers the single execution path of main(), ensuring:
 * 1. get_temperature_celsius() is called once.
 * 2. check_temperature_status() is called once.
 * 3. The temperature returned by get_temperature_celsius() is correctly passed
 *    as an argument to check_temperature_status().
 * 4. main() returns 0.
 */
void test_main_callsDependenciesCorrectlyAndReturnsZero(void) {
    int result_main;
    float expected_temp_from_sensor = 28.5f; // A realistic, specific temperature for the test
    const char* expected_status_string = "OK"; // A specific status string for the test

    // 1. Configure stubs to control the behavior of main's dependencies
    stub_get_temperature_celsius_data.return_value = expected_temp_from_sensor;
    stub_check_temperature_status_data.return_value = expected_status_string;

    // 2. Execute the main function under test
    result_main = 

    // 3. Assertions based on main()'s expected behavior

    // Expected: main should return 0, indicating successful execution.
    TEST_ASSERT_EQUAL_INT(0, result_main);

    // Expected: get_temperature_celsius() should have been called exactly once.
    TEST_ASSERT_TRUE(stub_get_temperature_celsius_data.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_get_temperature_celsius_data.call_count);

    // Expected: check_temperature_status() should have been called exactly once.
    TEST_ASSERT_TRUE(stub_check_temperature_status_data.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_check_temperature_status_data.call_count);

    // Expected: The temperature passed to check_temperature_status() by main()
    //           must be the value returned by get_temperature_celsius().
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_temp_from_sensor, stub_check_temperature_status_data.captured_temperature);

    // Note: The `printf` calls within `main()` are not stubbed or captured in this unit test.
    // To verify `printf` output, a custom test environment for output redirection would be required.
    // For embedded unit testing, the primary focus is on functional logic and dependency interaction.
}

// === Main Test Runner ===

// The main function for the Unity test framework.


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_main_callsDependenciesCorrectlyAndReturnsZero);

    return UNITY_END();
}