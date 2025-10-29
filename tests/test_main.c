/* test_main.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdio.h> // Included as per source file
#include <stdint.h>
#include <stdbool.h>
#include <string.h> // For memset

// External function declarations (from main.c and other modules)
extern int main(void);
extern float get_temperature_celsius(void);
extern const char* check_temperature_status(float temperature);

// --- STUB DEFINITIONS FOR EXTERNAL DEPENDENCIES ---

// Stub control structure for get_temperature_celsius
typedef struct {
    float return_value;
    uint32_t call_count;
} get_temperature_celsius_stub_t;
static get_temperature_celsius_stub_t get_temperature_celsius_stub = {0};

// Stub implementation for get_temperature_celsius
float get_temperature_celsius(void) {
    get_temperature_celsius_stub.call_count++;
    return get_temperature_celsius_stub.return_value;
}

// Stub control structure for check_temperature_status
typedef struct {
    const char* return_value;
    uint32_t call_count;
    float last_temperature_param;
} check_temperature_status_stub_t;
static check_temperature_status_stub_t check_temperature_status_stub = {0};

// Stub implementation for check_temperature_status
const char* check_temperature_status(float temperature) {
    check_temperature_status_stub.call_count++;
    check_temperature_status_stub.last_temperature_param = temperature;
    return check_temperature_status_stub.return_value;
}

// --- UNITY TEST FRAMEWORK FUNCTIONS ---

void setUp(void) {
    // Reset all stub control structures before each test
    memset(&get_temperature_celsius_stub, 0, sizeof(get_temperature_celsius_stub));
    memset(&check_temperature_status_stub, 0, sizeof(check_temperature_status_stub));

    // Set sensible default return values for stubs
    get_temperature_celsius_stub.return_value = 25.0f; // Default to a nominal temperature
    check_temperature_status_stub.return_value = "UNKNOWN"; // Default to an unknown status string
}

void tearDown(void) {
    // Ensure all stub control structures are fully reset after each test
    memset(&get_temperature_celsius_stub, 0, sizeof(get_temperature_celsius_stub));
    memset(&check_temperature_status_stub, 0, sizeof(check_temperature_status_stub));
}

// --- TEST CASES FOR main() ---

/**
 * @brief Test the main function with a nominal temperature scenario.
 *        Verifies correct function call sequence and return value.
 */
void test_main_nominal_temperature_flow(void) {
    int result;
    const float nominal_temp = 25.0f;
    const char* nominal_status = "NORMAL";

    // Configure stubs for a nominal temperature scenario
    get_temperature_celsius_stub.return_value = nominal_temp;
    check_temperature_status_stub.return_value = nominal_status;

    // Call the main function directly
    result = 

    // Assertions
    // Expected: main should return 0 for successful execution
    TEST_ASSERT_EQUAL_INT(0, result);
    // Expected: get_temperature_celsius should be called exactly once
    TEST_ASSERT_EQUAL_UINT32(1, get_temperature_celsius_stub.call_count);
    // Expected: check_temperature_status should be called exactly once
    TEST_ASSERT_EQUAL_UINT32(1, check_temperature_status_stub.call_count);
    // Expected: The temperature passed to check_temperature_status should match the one returned by get_temperature_celsius
    TEST_ASSERT_FLOAT_WITHIN(0.1f, nominal_temp, check_temperature_status_stub.last_temperature_param);

    // Note: Asserting printf output requires redirection (not implemented in this unit test setup).
}

/**
 * @brief Test the main function with a cold temperature scenario.
 *        Verifies correct function call sequence and parameter passing for a cold reading.
 */
void test_main_cold_temperature_flow(void) {
    int result;
    const float cold_temp = 0.0f; // A realistic cold temperature example
    const char* cold_status = "COLD";

    // Configure stubs for a cold temperature scenario
    get_temperature_celsius_stub.return_value = cold_temp;
    check_temperature_status_stub.return_value = cold_status;

    // Call the main function directly
    result = 

    // Assertions
    // Expected: main should return 0 for successful execution
    TEST_ASSERT_EQUAL_INT(0, result);
    // Expected: get_temperature_celsius should be called exactly once
    TEST_ASSERT_EQUAL_UINT32(1, get_temperature_celsius_stub.call_count);
    // Expected: check_temperature_status should be called exactly once
    TEST_ASSERT_EQUAL_UINT32(1, check_temperature_status_stub.call_count);
    // Expected: The temperature passed to check_temperature_status should match the one returned by get_temperature_celsius
    TEST_ASSERT_FLOAT_WITHIN(0.1f, cold_temp, check_temperature_status_stub.last_temperature_param);

    // Note: Asserting printf output requires redirection (not implemented in this unit test setup).
}

/**
 * @brief Test the main function with a hot temperature scenario.
 *        Verifies correct function call sequence and parameter passing for a hot reading.
 */
void test_main_hot_temperature_flow(void) {
    int result;
    const float hot_temp = 90.5f; // A realistic hot temperature example
    const char* hot_status = "HOT";

    // Configure stubs for a hot temperature scenario
    get_temperature_celsius_stub.return_value = hot_temp;
    check_temperature_status_stub.return_value = hot_status;

    // Call the main function directly
    result = 

    // Assertions
    // Expected: main should return 0 for successful execution
    TEST_ASSERT_EQUAL_INT(0, result);
    // Expected: get_temperature_celsius should be called exactly once
    TEST_ASSERT_EQUAL_UINT32(1, get_temperature_celsius_stub.call_count);
    // Expected: check_temperature_status should be called exactly once
    TEST_ASSERT_EQUAL_UINT32(1, check_temperature_status_stub.call_count);
    // Expected: The temperature passed to check_temperature_status should match the one returned by get_temperature_celsius
    TEST_ASSERT_FLOAT_WITHIN(0.1f, hot_temp, check_temperature_status_stub.last_temperature_param);

    // Note: Asserting printf output requires redirection (not implemented in this unit test setup).
}

// --- MAIN UNITY TEST RUNNER ---



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_main_nominal_temperature_flow);
    RUN_TEST(test_main_cold_temperature_flow);
    RUN_TEST(test_main_hot_temperature_flow);

    return UNITY_END();
}