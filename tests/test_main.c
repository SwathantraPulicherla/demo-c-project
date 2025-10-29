/* test_main.c – Auto-generated Expert Unity Tests */

#include "unity.h"
#include <stdint.h>   // For uint32_t
#include <stdbool.h>  // For bool
#include <string.h>   // For memset

// Extern declaration for the main function from src/main.c
extern int main(void);

// External functions to be stubbed
extern float get_temperature_celsius(void);
extern const char* check_temperature_status(float temperature);

// --- Stubs Definitions ---

// Stub control structure for get_temperature_celsius
typedef struct {
    float return_value;
    uint32_t call_count;
} stub_get_temperature_celsius_t;

static stub_get_temperature_celsius_t stub_get_temperature_celsius = {0};

float get_temperature_celsius(void) {
    stub_get_temperature_celsius.call_count++;
    return stub_get_temperature_celsius.return_value;
}

// Stub control structure for check_temperature_status
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

// --- Test Fixture Setup and Teardown ---

void setUp(void) {
    // Complete reset of all stubs to ensure test isolation
    memset(&stub_get_temperature_celsius, 0, sizeof(stub_get_temperature_celsius));
    memset(&stub_check_temperature_status, 0, sizeof(stub_check_temperature_status));

    // Set default return values for stubs for a 'normal' scenario
    stub_get_temperature_celsius.return_value = 25.0f;     // Default normal temperature
    stub_check_temperature_status.return_value = "NORMAL"; // Default status
}

void tearDown(void) {
    // Complete reset of all stubs (identical to setUp for thorough cleanup)
    memset(&stub_get_temperature_celsius, 0, sizeof(stub_get_temperature_celsius));
    memset(&stub_check_temperature_status, 0, sizeof(stub_check_temperature_status));
}

// --- Test Cases ---

/**
 * @brief Test main function under normal operating conditions.
 *
 * Verifies that main correctly calls `get_temperature_celsius`, passes its result to
 * `check_temperature_status`, and returns 0 indicating successful execution.
 */
void test_main_normal_operation(void) {
    int result;
    float expected_temp = 25.5f; // A typical normal temperature for a sensor
    const char* expected_status = "NORMAL";

    stub_get_temperature_celsius.return_value = expected_temp;
    stub_check_temperature_status.return_value = expected_status;

    result =  // Call the actual main function

    TEST_ASSERT_EQUAL_INT(0, result); // Expected: main should return 0 on successful execution

    TEST_ASSERT_EQUAL_UINT32(1, stub_get_temperature_celsius.call_count); // Expected: get_temperature_celsius is called exactly once
    TEST_ASSERT_EQUAL_UINT32(1, stub_check_temperature_status.call_count); // Expected: check_temperature_status is called exactly once

    // Expected: The temperature returned by get_temperature_celsius is passed as a parameter to check_temperature_status
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_temp, stub_check_temperature_status.last_temperature_param);

    // Note: Direct printf output assertion is not handled in typical embedded unit tests;
    // this test focuses on function call flow, parameter passing, and return values.
}

/**
 * @brief Test main function when a cold temperature is reported by the sensor.
 *
 * Verifies the call flow and parameter passing when `get_temperature_celsius`
 * returns a cold temperature, leading to a "COLD" status.
 */
void test_main_cold_temperature(void) {
    int result;
    float expected_temp = 0.0f; // A cold temperature, valid for embedded sensors (e.g., -40C to 125C range)
    const char* expected_status = "COLD";

    stub_get_temperature_celsius.return_value = expected_temp;
    stub_check_temperature_status.return_value = expected_status;

    result =  // Call the actual main function

    TEST_ASSERT_EQUAL_INT(0, result); // Expected: main should return 0

    TEST_ASSERT_EQUAL_UINT32(1, stub_get_temperature_celsius.call_count); // Expected: get_temperature_celsius is called once
    TEST_ASSERT_EQUAL_UINT32(1, stub_check_temperature_status.call_count); // Expected: check_temperature_status is called once

    // Expected: The cold temperature is accurately passed to check_temperature_status
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_temp, stub_check_temperature_status.last_temperature_param);
}

/**
 * @brief Test main function when a hot temperature is reported by the sensor.
 *
 * Verifies the call flow and parameter passing when `get_temperature_celsius`
 * returns a hot temperature, leading to a "HOT" status.
 */
void test_main_hot_temperature(void) {
    int result;
    float expected_temp = 95.0f; // A hot temperature, valid for embedded sensors
    const char* expected_status = "HOT";

    stub_get_temperature_celsius.return_value = expected_temp;
    stub_check_temperature_status.return_value = expected_status;

    result =  // Call the actual main function

    TEST_ASSERT_EQUAL_INT(0, result); // Expected: main should return 0

    TEST_ASSERT_EQUAL_UINT32(1, stub_get_temperature_celsius.call_count); // Expected: get_temperature_celsius is called once
    TEST_ASSERT_EQUAL_UINT32(1, stub_check_temperature_status.call_count); // Expected: check_temperature_status is called once

    // Expected: The hot temperature is accurately passed to check_temperature_status
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_temp, stub_check_temperature_status.last_temperature_param);
}

// --- Main Test Runner ---



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_main_normal_operation);
    RUN_TEST(test_main_cold_temperature);
    RUN_TEST(test_main_hot_temperature);

    return UNITY_END();
}