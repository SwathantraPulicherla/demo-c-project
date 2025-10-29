/* test_main.c – Auto-generated Expert Unity Tests */

#include "unity.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h> // For memset

// Declare main function from src/main.c
extern int main(void);

// =================================================================================
// External Functions to Stub (as per prompt)
// Inferred signatures based on usage in main.c
// =================================================================================

// Stubs for get_temperature_celsius()
typedef struct {
    float return_value;
    uint32_t call_count;
} stub_get_temperature_celsius_t;

static stub_get_temperature_celsius_t stub_get_temperature_celsius = {0};

float get_temperature_celsius(void) {
    stub_get_temperature_celsius.call_count++;
    return stub_get_temperature_celsius.return_value;
}

// Stubs for check_temperature_status()
typedef struct {
    const char* return_value;
    uint32_t call_count;
    float last_temperature_param;
} stub_check_temperature_status_t;

static stub_check_temperature_status_t stub_check_temperature_status = {0};

const char* check_temperature_status(float temperature) {
    stub_check_temperature_status.call_count++;
    stub_check_temperature_status.last_temperature_param = temperature;
    return stub_check_temperature_status.return_value;
}

// =================================================================================
// Setup and Teardown
// =================================================================================

void setUp(void) {
    // Reset all stub control structures to a known state before each test
    memset(&stub_get_temperature_celsius, 0, sizeof(stub_get_temperature_celsius));
    memset(&stub_check_temperature_status, 0, sizeof(stub_check_temperature_status));

    // Default return values for stubs
    stub_get_temperature_celsius.return_value = 25.0f; // Default to a nominal temperature
    stub_check_temperature_status.return_value = "NORMAL"; // Default status
}

void tearDown(void) {
    // Ensure all stub control structures are fully reset after each test
    memset(&stub_get_temperature_celsius, 0, sizeof(stub_get_temperature_celsius));
    memset(&stub_check_temperature_status, 0, sizeof(stub_check_temperature_status));
}

// =================================================================================
// Test Cases for main()
// =================================================================================

/**
 * @brief Tests main() behavior with a normal temperature scenario.
 * It verifies that get_temperature_celsius and check_temperature_status are called
 * correctly and that the parameter passed to check_temperature_status is accurate.
 */
void test_main_normal_temperature_scenario(void) {
    int result;
    float nominal_temp = 25.0f;
    const char* status = "NORMAL";

    // Configure stubs for a nominal temperature and status
    stub_get_temperature_celsius.return_value = nominal_temp;
    stub_check_temperature_status.return_value = status;

    // Call main function directly
    result = 

    // Expected: get_temperature_celsius should be called exactly once
    TEST_ASSERT_EQUAL_UINT32(1, stub_get_temperature_celsius.call_count);
    // Expected: check_temperature_status should be called exactly once
    TEST_ASSERT_EQUAL_UINT32(1, stub_check_temperature_status.call_count);
    // Expected: The temperature passed to check_temperature_status should match the one returned by get_temperature_celsius
    TEST_ASSERT_FLOAT_WITHIN(0.1f, nominal_temp, stub_check_temperature_status.last_temperature_param);
    // Expected: main() should return 0 on successful execution
    TEST_ASSERT_EQUAL_INT(0, result);
    // Note: printf output is not asserted in unit tests; assumes console redirection for verification.
}

/**
 * @brief Tests main() behavior with a cold temperature scenario.
 * Verifies correct call sequence and parameter passing for a temperature indicating 'COLD'.
 */
void test_main_cold_temperature_scenario(void) {
    int result;
    float cold_temp = 0.0f; // A realistic cold temperature (e.g., below 0°C)
    const char* status = "COLD";

    // Configure stubs for a cold temperature and status
    stub_get_temperature_celsius.return_value = cold_temp;
    stub_check_temperature_status.return_value = status;

    // Call main function directly
    result = 

    // Expected: get_temperature_celsius should be called exactly once
    TEST_ASSERT_EQUAL_UINT32(1, stub_get_temperature_celsius.call_count);
    // Expected: check_temperature_status should be called exactly once
    TEST_ASSERT_EQUAL_UINT32(1, stub_check_temperature_status.call_count);
    // Expected: The temperature passed to check_temperature_status should match the one returned by get_temperature_celsius
    TEST_ASSERT_FLOAT_WITHIN(0.1f, cold_temp, stub_check_temperature_status.last_temperature_param);
    // Expected: main() should return 0 on successful execution
    TEST_ASSERT_EQUAL_INT(0, result);
    // Note: printf output is not asserted in unit tests; assumes console redirection for verification.
}

/**
 * @brief Tests main() behavior with a hot temperature scenario.
 * Verifies correct call sequence and parameter passing for a temperature indicating 'HOT'.
 */
void test_main_hot_temperature_scenario(void) {
    int result;
    float hot_temp = 100.0f; // A realistic hot temperature (e.g., boiling point)
    const char* status = "HOT";

    // Configure stubs for a hot temperature and status
    stub_get_temperature_celsius.return_value = hot_temp;
    stub_check_temperature_status.return_value = status;

    // Call main function directly
    result = 

    // Expected: get_temperature_celsius should be called exactly once
    TEST_ASSERT_EQUAL_UINT32(1, stub_get_temperature_celsius.call_count);
    // Expected: check_temperature_status should be called exactly once
    TEST_ASSERT_EQUAL_UINT32(1, stub_check_temperature_status.call_count);
    // Expected: The temperature passed to check_temperature_status should match the one returned by get_temperature_celsius
    TEST_ASSERT_FLOAT_WITHIN(0.1f, hot_temp, stub_check_temperature_status.last_temperature_param);
    // Expected: main() should return 0 on successful execution
    TEST_ASSERT_EQUAL_INT(0, result);
    // Note: printf output is not asserted in unit tests; assumes console redirection for verification.
}

// =================================================================================
// Main Test Runner
// =================================================================================



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_main_normal_temperature_scenario);
    RUN_TEST(test_main_cold_temperature_scenario);
    RUN_TEST(test_main_hot_temperature_scenario);

    return UNITY_END();
}