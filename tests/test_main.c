/* test_main.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

// Source module under test will define main, so declare it as extern here.
extern int main(void);

// Declare external functions that are called by main() but not stubbed (from temp_converter.h)
// Assume these are linked from their actual implementation as they are not in the stub list.
extern const char* check_temperature_status(float temperature);

// --- STUB DEFINITIONS FOR EXTERNAL DEPENDENCIES ---

// Stub control structure for get_temperature_celsius
typedef struct {
    float return_value;
    bool was_called;
    uint32_t call_count;
} stub_get_temperature_celsius_t;

static stub_get_temperature_celsius_t stub_get_temperature_celsius = {0};

// Implementation of the stub for get_temperature_celsius
float get_temperature_celsius(void) {
    stub_get_temperature_celsius.was_called = true;
    stub_get_temperature_celsius.call_count++;
    return stub_get_temperature_celsius.return_value;
}

// --- TEST FIXTURES ---

void setUp(void) {
    // Reset all stubs to default state
    memset(&stub_get_temperature_celsius, 0, sizeof(stub_get_temperature_celsius));
    // Set default return values for stubs
    stub_get_temperature_celsius.return_value = 25.0f; // Default nominal temperature
}

void tearDown(void) {
    // Ensure all stubs are fully reset after each test
    memset(&stub_get_temperature_celsius, 0, sizeof(stub_get_temperature_celsius));
}

// --- TEST CASES ---

/**
 * @brief Test main function with a nominal temperature.
 *
 * Verifies that main calls get_temperature_celsius and returns 0 under normal conditions.
 */
void test_main_nominal_temperature(void) {
    int result;

    // Configure stub for a nominal temperature (e.g., 25.0f)
    stub_get_temperature_celsius.return_value = 25.0f; // A typical, normal room temperature

    // Call the main function
    result = 

    // Assert that get_temperature_celsius was called exactly once
    TEST_ASSERT_TRUE_MESSAGE(stub_get_temperature_celsius.was_called, "get_temperature_celsius should have been called.");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(1, stub_get_temperature_celsius.call_count, "get_temperature_celsius should have been called once.");

    // Assert that main returns 0
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, result, "main() should return 0 on successful execution.");

    // Note: printf output is not asserted here. This would require redirecting stdout.
}

/**
 * @brief Test main function with a cold temperature.
 *
 * Verifies that main calls get_temperature_celsius and returns 0 when simulating a cold condition.
 */
void test_main_cold_temperature(void) {
    int result;

    // Configure stub for a cold temperature (e.g., 0.0f)
    // 0.0f is a realistic cold temperature value in many applications.
    stub_get_temperature_celsius.return_value = 0.0f; 

    // Call the main function
    result = 

    // Assert that get_temperature_celsius was called exactly once
    TEST_ASSERT_TRUE_MESSAGE(stub_get_temperature_celsius.was_called, "get_temperature_celsius should have been called.");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(1, stub_get_temperature_celsius.call_count, "get_temperature_celsius should have been called once.");

    // Assert that main returns 0
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, result, "main() should return 0 on successful execution.");
}

/**
 * @brief Test main function with a hot temperature.
 *
 * Verifies that main calls get_temperature_celsius and returns 0 when simulating a hot condition.
 */
void test_main_hot_temperature(void) {
    int result;

    // Configure stub for a hot temperature (e.g., 90.0f)
    // 90.0f is a realistic hot temperature, potentially near an upper warning threshold.
    stub_get_temperature_celsius.return_value = 90.0f;

    // Call the main function
    result = 

    // Assert that get_temperature_celsius was called exactly once
    TEST_ASSERT_TRUE_MESSAGE(stub_get_temperature_celsius.was_called, "get_temperature_celsius should have been called.");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(1, stub_get_temperature_celsius.call_count, "get_temperature_celsius should have been called once.");

    // Assert that main returns 0
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, result, "main() should return 0 on successful execution.");
}

// --- UNITY TEST RUNNER ---



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_main_nominal_temperature);
    RUN_TEST(test_main_cold_temperature);
    RUN_TEST(test_main_hot_temperature);

    return UNITY_END();
}