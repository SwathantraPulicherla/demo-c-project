/* test_main.c – Auto-generated Expert Unity Tests */

// Includes
#include "unity.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h> // For memset
#include <stdio.h>  // From source: for printf declaration
#include "temp_sensor.h"    // From source: for get_temperature_celsius declaration
#include "temp_converter.h" // From source: for check_temperature_status declaration

// External function declaration for main()
extern int main(void);

// Stubs for external dependencies
// Per prompt, only get_temperature_celsius is listed for stubbing.
typedef struct {
    float return_value;
    uint32_t call_count;
} stub_get_temperature_celsius_t;

static stub_get_temperature_celsius_t stub_get_temperature_celsius_ctrl = {0};

// Stub implementation for get_temperature_celsius
float get_temperature_celsius(void) {
    stub_get_temperature_celsius_ctrl.call_count++;
    return stub_get_temperature_celsius_ctrl.return_value;
}

// setUp function: Initializes and resets stubs before each test
void setUp(void) {
    // Reset all stub control structures to their default/zero state
    memset(&stub_get_temperature_celsius_ctrl, 0, sizeof(stub_get_temperature_celsius_ctrl));

    // Configure default return values for stubs
    stub_get_temperature_celsius_ctrl.return_value = 25.0f; // Default to a nominal room temperature
}

// tearDown function: Cleans up after each test
void tearDown(void) {
    // Reset all stub control structures again to ensure complete isolation
    memset(&stub_get_temperature_celsius_ctrl, 0, sizeof(stub_get_temperature_celsius_ctrl));
}

// Test Cases for main() function

// Test: main_normal_temperature_scenario
// Validates the main function's call sequence and return for a typical normal temperature.
void test_main_normal_temperature_scenario(void) {
    int result;
    // Configure stub: get_temperature_celsius to return a nominal temperature (e.g., 25.0f C)
    stub_get_temperature_celsius_ctrl.return_value = 25.0f;

    // Call the main function
    result = 

    // Assertions
    // Expected: get_temperature_celsius should be called exactly once by main
    TEST_ASSERT_EQUAL_UINT32(1, stub_get_temperature_celsius_ctrl.call_count);
    // Expected: main should return 0, indicating successful execution
    TEST_ASSERT_EQUAL_INT(0, result);
    // Note: printf output is not captured and check_temperature_status parameter cannot be asserted
    // directly, as stubbing these functions is not permitted by the prompt rules. The real
    // check_temperature_status from temp_converter.h will be linked.
}

// Test: main_cold_temperature_scenario
// Validates the main function's call sequence and return for a cold temperature.
void test_main_cold_temperature_scenario(void) {
    int result;
    // Configure stub: get_temperature_celsius to return a valid cold temperature (e.g., 0.0f C)
    stub_get_temperature_celsius_ctrl.return_value = 0.0f;

    // Call the main function
    result = 

    // Assertions
    // Expected: get_temperature_celsius should be called exactly once by main
    TEST_ASSERT_EQUAL_UINT32(1, stub_get_temperature_celsius_ctrl.call_count);
    // Expected: main should return 0, indicating successful execution
    TEST_ASSERT_EQUAL_INT(0, result);
    // Note: printf output is not captured and check_temperature_status parameter cannot be asserted
    // directly due to stubbing restrictions.
}

// Test: main_hot_temperature_scenario
// Validates the main function's call sequence and return for a hot temperature.
void test_main_hot_temperature_scenario(void) {
    int result;
    // Configure stub: get_temperature_celsius to return a valid hot temperature (e.g., 80.0f C)
    stub_get_temperature_celsius_ctrl.return_value = 80.0f;

    // Call the main function
    result = 

    // Assertions
    // Expected: get_temperature_celsius should be called exactly once by main
    TEST_ASSERT_EQUAL_UINT32(1, stub_get_temperature_celsius_ctrl.call_count);
    // Expected: main should return 0, indicating successful execution
    TEST_ASSERT_EQUAL_INT(0, result);
    // Note: printf output is not captured and check_temperature_status parameter cannot be asserted
    // directly due to stubbing restrictions.
}

// Main function to run all tests


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_main_normal_temperature_scenario);
    RUN_TEST(test_main_cold_temperature_scenario);
    RUN_TEST(test_main_hot_temperature_scenario);

    return UNITY_END();
}