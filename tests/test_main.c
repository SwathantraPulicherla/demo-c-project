/* test_main.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h> // Required for memset
#include <stdio.h>    // Required for printf in main.c, even if not directly tested
#include "temp_sensor.h" // For get_temperature_celsius declaration
#include "temp_converter.h" // For check_temperature_status declaration

// Forward declaration for main function in main.c
extern int main(void);

// =================================================================================================
// Stub for external function: get_temperature_celsius
// Inferred signature: float get_temperature_celsius(void)
// =================================================================================================
typedef struct {
    float return_value;
    bool was_called;
    uint32_t call_count;
} stub_get_temperature_celsius_t;

static stub_get_temperature_celsius_t stub_get_temperature_celsius_data;

float get_temperature_celsius(void) {
    stub_get_temperature_celsius_data.was_called = true;
    stub_get_temperature_celsius_data.call_count++;
    return stub_get_temperature_celsius_data.return_value;
}

// =================================================================================================
// Test Setup and Teardown
// =================================================================================================

void setUp(void) {
    // Reset all stub data to ensure test isolation
    memset(&stub_get_temperature_celsius_data, 0, sizeof(stub_get_temperature_celsius_data));
}

void tearDown(void) {
    // Reset all stub data again after each test
    memset(&stub_get_temperature_celsius_data, 0, sizeof(stub_get_temperature_celsius_data));
}

// =================================================================================================
// Tests for main() function
// =================================================================================================

// Test scenario: Normal temperature
void test_main_normal_temperature(void) {
    // Expected: main should call get_temperature_celsius and return 0
    // Test input: get_temperature_celsius returns a nominal temperature (25.0f)
    float expected_temp = 25.0f; // Nominal temperature, typically "NORMAL" status
    stub_get_temperature_celsius_data.return_value = expected_temp;

    // Call the main function
    int result = 

    // Assert that get_temperature_celsius was called exactly once
    TEST_ASSERT_TRUE(stub_get_temperature_celsius_data.was_called); // get_temperature_celsius must be called
    TEST_ASSERT_EQUAL_INT(1, stub_get_temperature_celsius_data.call_count); // get_temperature_celsius called once

    // Assert that main returns 0 on successful execution
    TEST_ASSERT_EQUAL_INT(0, result); // main should return 0

    // Note: printf output is not assertable directly without output redirection.
    // The call to check_temperature_status(temp) cannot be spied on without stubbing it,
    // which is not allowed per the prompt's "EXTERNAL FUNCTIONS TO STUB (only these)" rule.
    // We assume check_temperature_status and printf function correctly as linked dependencies.
}

// Test scenario: Cold temperature
void test_main_cold_temperature(void) {
    // Expected: main should call get_temperature_celsius and return 0
    // Test input: get_temperature_celsius returns a cold temperature (0.0f)
    float expected_temp = 0.0f; // A cold temperature, typically "COLD" status
    stub_get_temperature_celsius_data.return_value = expected_temp;

    // Call the main function
    int result = 

    // Assert that get_temperature_celsius was called exactly once
    TEST_ASSERT_TRUE(stub_get_temperature_celsius_data.was_called); // get_temperature_celsius must be called
    TEST_ASSERT_EQUAL_INT(1, stub_get_temperature_celsius_data.call_count); // get_temperature_celsius called once

    // Assert that main returns 0 on successful execution
    TEST_ASSERT_EQUAL_INT(0, result); // main should return 0
}

// Test scenario: Hot temperature
void test_main_hot_temperature(void) {
    // Expected: main should call get_temperature_celsius and return 0
    // Test input: get_temperature_celsius returns a hot temperature (85.1f)
    float expected_temp = 85.1f; // A hot temperature, typically "HOT" or "CRITICAL" status
    stub_get_temperature_celsius_data.return_value = expected_temp;

    // Call the main function
    int result = 

    // Assert that get_temperature_celsius was called exactly once
    TEST_ASSERT_TRUE(stub_get_temperature_celsius_data.was_called); // get_temperature_celsius must be called
    TEST_ASSERT_EQUAL_INT(1, stub_get_temperature_celsius_data.call_count); // get_temperature_celsius called once

    // Assert that main returns 0 on successful execution
    TEST_ASSERT_EQUAL_INT(0, result); // main should return 0
}

// Test scenario: Minimum valid edge temperature
void test_main_min_edge_temperature(void) {
    // Expected: main should call get_temperature_celsius and return 0
    // Test input: get_temperature_celsius returns the minimum valid temperature (0.0f)
    float expected_temp = 0.0f; // Minimum valid temperature for many sensors
    stub_get_temperature_celsius_data.return_value = expected_temp;

    // Call the main function
    int result = 

    // Assert that get_temperature_celsius was called exactly once
    TEST_ASSERT_TRUE(stub_get_temperature_celsius_data.was_called); // get_temperature_celsius must be called
    TEST_ASSERT_EQUAL_INT(1, stub_get_temperature_celsius_data.call_count); // get_temperature_celsius called once

    // Assert that main returns 0 on successful execution
    TEST_ASSERT_EQUAL_INT(0, result); // main should return 0
}

// Test scenario: Maximum valid edge temperature
void test_main_max_edge_temperature(void) {
    // Expected: main should call get_temperature_celsius and return 0
    // Test input: get_temperature_celsius returns the maximum valid temperature (125.0f)
    float expected_temp = 125.0f; // Maximum valid temperature for many sensors
    stub_get_temperature_celsius_data.return_value = expected_temp;

    // Call the main function
    int result = 

    // Assert that get_temperature_celsius was called exactly once
    TEST_ASSERT_TRUE(stub_get_temperature_celsius_data.was_called); // get_temperature_celsius must be called
    TEST_ASSERT_EQUAL_INT(1, stub_get_temperature_celsius_data.call_count); // get_temperature_celsius called once

    // Assert that main returns 0 on successful execution
    TEST_ASSERT_EQUAL_INT(0, result); // main should return 0
}

// =================================================================================================
// Main test runner
// =================================================================================================



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_main_normal_temperature);
    RUN_TEST(test_main_cold_temperature);
    RUN_TEST(test_main_hot_temperature);
    RUN_TEST(test_main_min_edge_temperature);
    RUN_TEST(test_main_max_edge_temperature);

    return UNITY_END();
}