/* test_main.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdint.h>   // For uint32_t
#include <stdbool.h>  // For bool
#include <string.h>   // For memset

// The main.h header is mandated to be included in the test file.
// However, the provided main.c source does not include main.h itself,
// and it does not define a public API that would typically be placed in main.h.
// To adhere to "NO invented functions or headers" for main.h's content,
// we assume main.h is either empty or declares only the main function.
// For the stub declarations, we will define them directly in the test file,
// as they are part of the test setup, not the module's public API.
// If main.h existed and declared externals, it would be included here.
// For now, assume it's minimal as no content for it was provided nor inferable from main.c usage.
// #include "main.h" // Uncomment if a main.h with declarations for externs exists and is provided.

// External function declarations for stubbing.
// These are inferred from main.c's usage and are necessary for compilation of the test.
// They are not "invented functions" but declarations of external dependencies.
float get_temperature_celsius(void);
const char* check_temperature_status(float temperature);

// --- Stubs for External Dependencies ---

// Stub control structure for get_temperature_celsius
typedef struct {
    float return_value;
    bool was_called;
    uint32_t call_count;
} stub_get_temperature_celsius_t;
static stub_get_temperature_celsius_t stub_get_temperature_celsius_data = {0};

// Stub implementation for get_temperature_celsius
float get_temperature_celsius(void) {
    stub_get_temperature_celsius_data.was_called = true;
    stub_get_temperature_celsius_data.call_count++;
    return stub_get_temperature_celsius_data.return_value;
}

// Stub control structure for check_temperature_status
typedef struct {
    const char* return_value;
    bool was_called;
    uint32_t call_count;
    float last_temperature; // Captures the last argument passed to the stub
} stub_check_temperature_status_t;
static stub_check_temperature_status_t stub_check_temperature_status_data = {0};

// Stub implementation for check_temperature_status
const char* check_temperature_status(float temperature) {
    stub_check_temperature_status_data.was_called = true;
    stub_check_temperature_status_data.call_count++;
    stub_check_temperature_status_data.last_temperature = temperature;
    return stub_check_temperature_status_data.return_value;
}

// printf is an external variadic function. Stubbing it reliably without inventing
// complex platform-specific wrappers or relying on linker tricks (both forbidden
// or outside Unity's scope for embedded) is challenging.
// As printf was not explicitly listed for stubbing and cannot be meaningfully
// stubbed under the strict "NO invented functions" rule for capturing output,
// we will not stub it. This means `main`'s `printf` calls cannot be directly
// asserted for their output content in this test suite.
// The tests will focus on the flow of control and data between `get_temperature_celsius`
// and `check_temperature_status`, and `main`'s return value.

// External declaration for the main function from main.c
// This is necessary to call main() from the test runner.
extern int 

// --- Test Setup and Teardown ---

void setUp(void) {
    // Reset all stub control structures completely
    memset(&stub_get_temperature_celsius_data, 0, sizeof(stub_get_temperature_celsius_data));
    memset(&stub_check_temperature_status_data, 0, sizeof(stub_check_temperature_status_data));

    // Set default/nominal return values for stubs
    stub_get_temperature_celsius_data.return_value = 25.0f; // A common, nominal temperature
    stub_check_temperature_status_data.return_value = "NORMAL"; // A common, nominal status
}

void tearDown(void) {
    // Ensure all stub control structures are fully reset after each test
    memset(&stub_get_temperature_celsius_data, 0, sizeof(stub_get_temperature_celsius_data));
    memset(&stub_check_temperature_status_data, 0, sizeof(stub_check_temperature_status_data));
}

// --- Test Cases for main() ---

// The main.c file contains no #defines, thresholds, ranges, magic numbers,
// if/else/switch branches, or struct/union/bitfield definitions.
// Therefore, the "logic" to cover 100% refers to the sequence of function calls
// and the final return value of the main function itself.

void test_main_calls_functions_and_returns_zero_nominal(void) {
    // Scenario: Nominal temperature returned by sensor.
    // Logic: main() should call get_temperature_celsius(), pass its result to check_temperature_status(), and return 0.

    // Arrange: Configure stub to return a nominal temperature
    float expected_temp_from_sensor = 23.5f;
    stub_get_temperature_celsius_data.return_value = expected_temp_from_sensor;
    const char* expected_status_string = "NORMAL";
    stub_check_temperature_status_data.return_value = expected_status_string;

    // Act: Call the main function
    int result = 

    // Assert: Verify interactions and return value

    // Expected: get_temperature_celsius should have been called
    TEST_ASSERT_TRUE(stub_get_temperature_celsius_data.was_called);
    // Expected: get_temperature_celsius should have been called exactly once
    TEST_ASSERT_EQUAL_UINT32(1, stub_get_temperature_celsius_data.call_count);

    // Expected: check_temperature_status should have been called
    TEST_ASSERT_TRUE(stub_check_temperature_status_data.was_called);
    // Expected: check_temperature_status should have been called exactly once
    TEST_ASSERT_EQUAL_UINT32(1, stub_check_temperature_status_data.call_count);
    // Expected: The temperature passed to check_temperature_status should match the value from the sensor stub
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_temp_from_sensor, stub_check_temperature_status_data.last_temperature);

    // Expected: main function should return 0
    TEST_ASSERT_EQUAL_INT(0, result);
}

void test_main_calls_functions_and_returns_zero_negative_temp(void) {
    // Scenario: Negative but valid temperature returned by sensor.
    // Logic: main() should call get_temperature_celsius(), pass its result to check_temperature_status(), and return 0.

    // Arrange: Configure stub to return a negative temperature (e.g., within valid range like -40C)
    float expected_temp_from_sensor = 0.0f; // A cold but valid temperature
    stub_get_temperature_celsius_data.return_value = expected_temp_from_sensor;
    const char* expected_status_string = "COLD";
    stub_check_temperature_status_data.return_value = expected_status_string;

    // Act: Call the main function
    int result = 

    // Assert: Verify interactions and return value

    // Expected: get_temperature_celsius should have been called
    TEST_ASSERT_TRUE(stub_get_temperature_celsius_data.was_called);
    // Expected: get_temperature_celsius should have been called exactly once
    TEST_ASSERT_EQUAL_UINT32(1, stub_get_temperature_celsius_data.call_count);

    // Expected: check_temperature_status should have been called
    TEST_ASSERT_TRUE(stub_check_temperature_status_data.was_called);
    // Expected: check_temperature_status should have been called exactly once
    TEST_ASSERT_EQUAL_UINT32(1, stub_check_temperature_status_data.call_count);
    // Expected: The temperature passed to check_temperature_status should match the value from the sensor stub
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_temp_from_sensor, stub_check_temperature_status_data.last_temperature);

    // Expected: main function should return 0
    TEST_ASSERT_EQUAL_INT(0, result);
}

void test_main_calls_functions_and_returns_zero_high_temp(void) {
    // Scenario: High but valid temperature returned by sensor.
    // Logic: main() should call get_temperature_celsius(), pass its result to check_temperature_status(), and return 0.

    // Arrange: Configure stub to return a high temperature (e.g., near max valid range like 100C)
    float expected_temp_from_sensor = 100.0f; // A high but valid temperature
    stub_get_temperature_celsius_data.return_value = expected_temp_from_sensor;
    const char* expected_status_string = "HOT";
    stub_check_temperature_status_data.return_value = expected_status_string;

    // Act: Call the main function
    int result = 

    // Assert: Verify interactions and return value

    // Expected: get_temperature_celsius should have been called
    TEST_ASSERT_TRUE(stub_get_temperature_celsius_data.was_called);
    // Expected: get_temperature_celsius should have been called exactly once
    TEST_ASSERT_EQUAL_UINT32(1, stub_get_temperature_celsius_data.call_count);

    // Expected: check_temperature_status should have been called
    TEST_ASSERT_TRUE(stub_check_temperature_status_data.was_called);
    // Expected: check_temperature_status should have been called exactly once
    TEST_ASSERT_EQUAL_UINT32(1, stub_check_temperature_status_data.call_count);
    // Expected: The temperature passed to check_temperature_status should match the value from the sensor stub
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_temp_from_sensor, stub_check_temperature_status_data.last_temperature);

    // Expected: main function should return 0
    TEST_ASSERT_EQUAL_INT(0, result);
}


// --- Main Test Runner ---




int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_main_calls_functions_and_returns_zero_nominal);
    RUN_TEST(test_main_calls_functions_and_returns_zero_negative_temp);
    RUN_TEST(test_main_calls_functions_and_returns_zero_high_temp);

    return UNITY_END();
}