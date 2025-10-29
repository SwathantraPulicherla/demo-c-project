/* test_temp_sensor.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include "temp_sensor.h" // For public API functions like validate_temperature_range, check_temperature_status, get_temperature_celsius
#include <stdbool.h>     // For bool type
#include <stdint.h>      // For uint32_t in stub struct
#include <string.h>      // For memset in setUp/tearDown

// External function to stub: raw_to_celsius
// Inferred signature based on usage in get_temperature_celsius: float raw_to_celsius(int raw_value)
typedef struct {
    float return_value;
    bool was_called;
    uint32_t call_count;
    int last_raw_value; // Captures the 'raw_value' parameter passed to the stub
} stub_raw_to_celsius_t;

// Static instance of the stub control structure, initialized to zeros
static stub_raw_to_celsius_t stub_raw_to_celsius = {0};

// Stub implementation for the external dependency raw_to_celsius
float raw_to_celsius(int raw_value) {
    stub_raw_to_celsius.was_called = true;
    stub_raw_to_celsius.call_count++;
    stub_raw_to_celsius.last_raw_value = raw_value;
    return stub_raw_to_celsius.return_value;
}

// Function to set up the test environment before each test
void setUp(void) {
    // Reset all stub control structures to their default state (zeros)
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
}

// Function to tear down the test environment after each test
void tearDown(void) {
    // Reset all stub control structures again after each test for robustness
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
}

// ==============================================================================
// Tests for validate_temperature_range(float temp_c)
// Logic: return temp_c >= 0.0f && temp_c <= 125.0f;
// ==============================================================================

void test_validate_temperature_range_valid_min_edge(void) {
    // Expected: 0.0f is exactly the minimum valid temperature, so it should be true.
    TEST_ASSERT_TRUE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_invalid_below_min(void) {
    // Expected: 0.0f is below the minimum valid temperature of 0.0f, so it should be false.
    TEST_ASSERT_FALSE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_valid_max_edge(void) {
    // Expected: 125.0f is exactly the maximum valid temperature, so it should be true.
    TEST_ASSERT_TRUE(validate_temperature_range(125.0f));
}

void test_validate_temperature_range_invalid_above_max(void) {
    // Expected: 125.1f is above the maximum valid temperature of 125.0f, so it should be false.
    TEST_ASSERT_FALSE(validate_temperature_range(125.1f));
}

void test_validate_temperature_range_valid_mid_range(void) {
    // Expected: 25.0f is within the valid temperature range, so it should be true.
    TEST_ASSERT_TRUE(validate_temperature_range(25.0f));
}

// ==============================================================================
// Tests for check_temperature_status(float temp_c)
// Logic: if > 120.0f "CRITICAL", else if > 85.0f "HOT", else if < 0.0f "COLD", else "NORMAL"
// ==============================================================================

void test_check_temperature_status_critical_above_threshold(void) {
    // Expected: 120.1f is greater than 120.0f, triggering the "CRITICAL" status.
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(120.1f));
}

void test_check_temperature_status_hot_above_85_threshold(void) {
    // Expected: 85.1f is greater than 85.0f (but not >120.0f), triggering the "HOT" status.
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(85.1f));
}

void test_check_temperature_status_hot_at_critical_edge(void) {
    // Expected: 120.0f is not strictly greater than 120.0f, but it is greater than 85.0f, so it's "HOT".
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(120.0f));
}

void test_check_temperature_status_normal_at_hot_edge(void) {
    // Expected: 85.0f is not strictly greater than 85.0f and not less than 0.0f, thus "NORMAL".
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(85.0f));
}

void test_check_temperature_status_normal_mid_range(void) {
    // Expected: 25.0f is between 0.0f and 85.0f (inclusive of 85.0f boundary from previous branch), thus "NORMAL".
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(25.0f));
}

void test_check_temperature_status_normal_at_cold_edge(void) {
    // Expected: 0.0f is not less than 0.0f, so it falls into the "NORMAL" category.
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(0.0f));
}

void test_check_temperature_status_cold_below_cold_threshold(void) {
    // Expected: 0.0f is less than 0.0f, triggering the "COLD" status.
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(0.0f));
}

void test_check_temperature_status_cold_at_min_valid_range(void) {
    // Expected: 0.0f, while valid for the sensor, is less than 0.0f, so it's "COLD".
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(0.0f));
}

// ==============================================================================
// Tests for get_temperature_celsius()
// Logic: Calls read_temperature_raw() (internal, uses rand()), then raw_to_celsius(raw) (external stub)
// Note: read_temperature_raw() is internal and uses rand(). Per rules, it cannot be stubbed.
// We verify its output range by checking the parameter passed to the stubbed raw_to_celsius.
// ==============================================================================

void test_get_temperature_celsius_nominal_conversion_and_raw_range(void) {
    // Configure stub to return a typical operational temperature
    stub_raw_to_celsius.return_value = 25.0f; 

    float result = get_temperature_celsius();

    // Expected: raw_to_celsius should be called exactly once
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    // Expected: The raw value passed to the converter should be within 00.0f (rand() % 1024)
    TEST_ASSERT_GREATER_OR_EQUAL_INT(0, stub_raw_to_celsius.last_raw_value);
    TEST_ASSERT_LESS_OR_EQUAL_INT(1023, stub_raw_to_celsius.last_raw_value);
    // Expected: The function should return the configured Celsius value from the stub
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 25.0f, result);
}

void test_get_temperature_celsius_min_valid_output_conversion_and_raw_range(void) {
    // Configure stub to return the minimum valid temperature for the sensor
    stub_raw_to_celsius.return_value = 0.0f;

    float result = get_temperature_celsius();

    // Expected: raw_to_celsius should be called exactly once
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    // Expected: The raw value passed to the converter should be within 00.0f
    TEST_ASSERT_GREATER_OR_EQUAL_INT(0, stub_raw_to_celsius.last_raw_value);
    TEST_ASSERT_LESS_OR_EQUAL_INT(1023, stub_raw_to_celsius.last_raw_value);
    // Expected: The function should return the configured Celsius value from the stub
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, result);
}

void test_get_temperature_celsius_max_valid_output_conversion_and_raw_range(void) {
    // Configure stub to return the maximum valid temperature for the sensor
    stub_raw_to_celsius.return_value = 125.0f;

    float result = get_temperature_celsius();

    // Expected: raw_to_celsius should be called exactly once
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    // Expected: The raw value passed to the converter should be within 00.0f
    TEST_ASSERT_GREATER_OR_EQUAL_INT(0, stub_raw_to_celsius.last_raw_value);
    TEST_ASSERT_LESS_OR_EQUAL_INT(1023, stub_raw_to_celsius.last_raw_value);
    // Expected: The function should return the configured Celsius value from the stub
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 125.0f, result);
}

// ==============================================================================
// No direct tests for read_temperature_raw()
// This function relies on rand() and is internal. Per rules, internal functions
// cannot be stubbed. Testing its specific return value deterministically is
// impossible without controlling rand(), which is not an external dependency
// to stub here. Its integration behavior and the range of values it produces
// are implicitly covered by the get_temperature_celsius tests, which
// assert that the parameter passed to the raw_to_celsius stub is within
// the expected 00.0f range.
// ==============================================================================

// Main function to run all tests



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_validate_temperature_range_valid_min_edge);
    RUN_TEST(test_validate_temperature_range_invalid_below_min);
    RUN_TEST(test_validate_temperature_range_valid_max_edge);
    RUN_TEST(test_validate_temperature_range_invalid_above_max);
    RUN_TEST(test_validate_temperature_range_valid_mid_range);
    RUN_TEST(test_check_temperature_status_critical_above_threshold);
    RUN_TEST(test_check_temperature_status_hot_above_85_threshold);
    RUN_TEST(test_check_temperature_status_hot_at_critical_edge);
    RUN_TEST(test_check_temperature_status_normal_at_hot_edge);
    RUN_TEST(test_check_temperature_status_normal_mid_range);
    RUN_TEST(test_check_temperature_status_normal_at_cold_edge);
    RUN_TEST(test_check_temperature_status_cold_below_cold_threshold);
    RUN_TEST(test_check_temperature_status_cold_at_min_valid_range);
    RUN_TEST(test_get_temperature_celsius_nominal_conversion_and_raw_range);
    RUN_TEST(test_get_temperature_celsius_min_valid_output_conversion_and_raw_range);
    RUN_TEST(test_get_temperature_celsius_max_valid_output_conversion_and_raw_range);

    return UNITY_END();
}