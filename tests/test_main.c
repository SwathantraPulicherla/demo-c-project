/* test_main.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdint.h>   // For uint32_t
#include <stdbool.h>  // For bool
#include <string.h>   // For memset

// Declare main externally to allow testing it directly, as it's typically excluded by UNIT_TEST define
extern int main(void);

// =================================================================================================
// STUB DECLARATIONS AND CONTROL STRUCTURES
// These stubs are for functions external to main.c that main() depends on.
// =================================================================================================

// Stub for get_temperature_celsius()
typedef struct {
    float return_value;
    uint32_t call_count;
} stub_get_temperature_celsius_t;
static stub_get_temperature_celsius_t stub_get_temperature_celsius = {0};

// Mock implementation of get_temperature_celsius
float get_temperature_celsius(void) {
    stub_get_temperature_celsius.call_count++;
    return stub_get_temperature_celsius.return_value;
}

// Stub for check_temperature_status()
typedef struct {
    const char* return_value;
    uint32_t call_count;
    float last_temperature_c; // Captured parameter for verification
} stub_check_temperature_status_t;
static stub_check_temperature_status_t stub_check_temperature_status = {0};

// Mock implementation of check_temperature_status
const char* check_temperature_status(float temperature_c) {
    stub_check_temperature_status.call_count++;
    stub_check_temperature_status.last_temperature_c = temperature_c; // Capture input parameter
    return stub_check_temperature_status.return_value;
}

// =================================================================================================
// UNITY FRAMEWORK SETUP AND TEARDOWN
// =================================================================================================

void setUp(void) {
    // Reset all stub control structures to a known state before each test
    memset(&stub_get_temperature_celsius, 0, sizeof(stub_get_temperature_celsius));
    memset(&stub_check_temperature_status, 0, sizeof(stub_check_temperature_status));

    // Set default return values for stubs for a typical scenario
    stub_get_temperature_celsius.return_value = 25.0f;     // Default to a nominal room temperature
    stub_check_temperature_status.return_value = "NORMAL"; // Default to a normal status string
}

void tearDown(void) {
    // Reset all stub control structures again after each test to ensure complete isolation
    memset(&stub_get_temperature_celsius, 0, sizeof(stub_get_temperature_celsius));
    memset(&stub_check_temperature_status, 0, sizeof(stub_check_temperature_status));
}

// =================================================================================================
// TEST CASES FOR main()
// Note: printf output validation is beyond the scope of typical embedded unit testing
// and would require output redirection, which is not implemented here. We focus on function
// call sequences, parameters, and return values.
// =================================================================================================

void test_main_normal_temperature(void) {
    int result;
    // Configure stubs for a nominal operating temperature scenario
    stub_get_temperature_celsius.return_value = 25.0f;
    stub_check_temperature_status.return_value = "NORMAL";

    result =  // Call the main function directly

    // Verify main's orchestration logic
    TEST_ASSERT_EQUAL_INT(1, stub_get_temperature_celsius.call_count);          // Expected: get_temperature_celsius should be called exactly once
    TEST_ASSERT_EQUAL_INT(1, stub_check_temperature_status.call_count);         // Expected: check_temperature_status should be called exactly once
    // Expected: 25.0f from get_temperature_celsius should be passed to check_temperature_status
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 25.0f, stub_check_temperature_status.last_temperature_c);
    TEST_ASSERT_EQUAL_INT(0, result);                                           // Expected: main() should return 0 indicating success
}

void test_main_cold_temperature_edge(void) {
    int result;
    // Configure stubs for a cold temperature scenario, at a typical edge case (e.g., just below normal)
    stub_get_temperature_celsius.return_value = 0.0f; // Example: temperature that would be classified as "COLD"
    stub_check_temperature_status.return_value = "COLD"; // Expected status based on input temperature

    result =  // Call the main function

    // Verify main's orchestration logic
    TEST_ASSERT_EQUAL_INT(1, stub_get_temperature_celsius.call_count);          // Expected: get_temperature_celsius should be called once
    TEST_ASSERT_EQUAL_INT(1, stub_check_temperature_status.call_count);         // Expected: check_temperature_status should be called once
    // Expected: 0.0f from get_temperature_celsius should be passed to check_temperature_status
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, stub_check_temperature_status.last_temperature_c);
    TEST_ASSERT_EQUAL_INT(0, result);                                           // Expected: main() should return 0
}

void test_main_hot_temperature_nominal(void) {
    int result;
    // Configure stubs for a hot temperature scenario
    stub_get_temperature_celsius.return_value = 90.0f; // Example: a temperature that would be classified as "HOT"
    stub_check_temperature_status.return_value = "HOT"; // Expected status based on input temperature

    result =  // Call the main function

    // Verify main's orchestration logic
    TEST_ASSERT_EQUAL_INT(1, stub_get_temperature_celsius.call_count);          // Expected: get_temperature_celsius should be called once
    TEST_ASSERT_EQUAL_INT(1, stub_check_temperature_status.call_count);         // Expected: check_temperature_status should be called once
    // Expected: 90.0f from get_temperature_celsius should be passed to check_temperature_status
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 90.0f, stub_check_temperature_status.last_temperature_c);
    TEST_ASSERT_EQUAL_INT(0, result);                                           // Expected: main() should return 0
}

void test_main_critical_high_temperature_edge(void) {
    int result;
    // Configure stubs for a critical high temperature scenario, at the maximum valid limit
    stub_get_temperature_celsius.return_value = 125.0f; // Expected: Max valid temperature as per prompt rules
    stub_check_temperature_status.return_value = "CRITICAL HIGH"; // Expected status for maximum temperature

    result =  // Call the main function

    // Verify main's orchestration logic
    TEST_ASSERT_EQUAL_INT(1, stub_get_temperature_celsius.call_count);          // Expected: get_temperature_celsius should be called once
    TEST_ASSERT_EQUAL_INT(1, stub_check_temperature_status.call_count);         // Expected: check_temperature_status should be called once
    // Expected: 125.0f from get_temperature_celsius should be passed to check_temperature_status
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 125.0f, stub_check_temperature_status.last_temperature_c);
    TEST_ASSERT_EQUAL_INT(0, result);                                           // Expected: main() should return 0
}

void test_main_critical_low_temperature_edge(void) {
    int result;
    // Configure stubs for a critical low temperature scenario, at the minimum valid limit
    stub_get_temperature_celsius.return_value = 0.0f; // Expected: Min valid temperature as per prompt rules
    stub_check_temperature_status.return_value = "CRITICAL LOW"; // Expected status for minimum temperature

    result =  // Call the main function

    // Verify main's orchestration logic
    TEST_ASSERT_EQUAL_INT(1, stub_get_temperature_celsius.call_count);          // Expected: get_temperature_celsius should be called once
    TEST_ASSERT_EQUAL_INT(1, stub_check_temperature_status.call_count);         // Expected: check_temperature_status should be called once
    // Expected: 0.0f from get_temperature_celsius should be passed to check_temperature_status
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, stub_check_temperature_status.last_temperature_c);
    TEST_ASSERT_EQUAL_INT(0, result);                                           // Expected: main() should return 0
}


// =================================================================================================
// MAIN FUNCTION TO RUN ALL TESTS
// =================================================================================================



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_main_normal_temperature);
    RUN_TEST(test_main_cold_temperature_edge);
    RUN_TEST(test_main_hot_temperature_nominal);
    RUN_TEST(test_main_critical_high_temperature_edge);
    RUN_TEST(test_main_critical_low_temperature_edge);

    return UNITY_END();
}