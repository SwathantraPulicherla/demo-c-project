/* test_temp_sensor.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include "temp_sensor.h" // For the functions being tested
#include <stdbool.h>     // For bool type
#include <stdint.h>      // For uint32_t in stub struct
#include <string.h>      // For memset
#include <stdlib.h>      // For rand() in source, NOT for stubbing it here

// Mocks/Stubs for external dependencies
// EXTERNAL FUNCTION TO STUB: raw_to_celsius
// Signature inferred from temp_sensor.c: float raw_to_celsius(int raw_val)
typedef struct {
    float return_value;
    bool was_called;
    uint32_t call_count;
    int last_raw_val; // Capture last parameter
} stub_raw_to_celsius_t;

static stub_raw_to_celsius_t stub_raw_to_celsius = {0};

float raw_to_celsius(int raw_val) {
    stub_raw_to_celsius.was_called = true;
    stub_raw_to_celsius.call_count++;
    stub_raw_to_celsius.last_raw_val = raw_val;
    return stub_raw_to_celsius.return_value;
}

void setUp(void) {
    // Reset all stubs to a known state before each test
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
}

void tearDown(void) {
    // Clean up or reset all stubs after each test (mandated for complete reset in both setUp and tearDown)
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
}

// ==== Test Cases for read_temperature_raw() ====
// This function relies on rand() which is not stubbed as per strict rules (not on the allowed stub list).
// Therefore, we can only test its output range and type, not a specific deterministic value.
void test_read_temperature_raw_returns_in_range(void) {
    int raw_temp;
    // Run multiple times to increase confidence that the range is correct
    // The source code uses rand() % 1024, implying a range from 0 to 1023.
    for (int i = 0; i < 100; i++) {
        raw_temp = read_temperature_raw();
        // Expected: Raw value should be between 0 and 1023 (inclusive)
        TEST_ASSERT_GREATER_OR_EQUAL_INT(0, raw_temp);
        // Expected: Raw value should be less than 1024
        TEST_ASSERT_LESS_OR_EQUAL_INT(1024, raw_temp);
    }
}

// ==== Test Cases for validate_temperature_range() ====
void test_validate_temperature_range_valid_mid_range(void) {
    float temp = 25.0f;
    bool result = validate_temperature_range(temp);
    // Expected: 25.0f is within [0.0f, 125.0f] range, thus valid
    TEST_ASSERT_TRUE(result);
}

void test_validate_temperature_range_valid_min_edge(void) {
    float temp = 0.0f;
    bool result = validate_temperature_range(temp);
    // Expected: 0.0f is at the minimum valid edge, thus valid
    TEST_ASSERT_TRUE(result);
}

void test_validate_temperature_range_valid_max_edge(void) {
    float temp = 125.0f;
    bool result = validate_temperature_range(temp);
    // Expected: 125.0f is at the maximum valid edge, thus valid
    TEST_ASSERT_TRUE(result);
}

void test_validate_temperature_range_invalid_below_min_edge(void) {
    float temp = 0.0f;
    bool result = validate_temperature_range(temp);
    // Expected: 0.0f is just below the minimum valid edge, thus invalid
    TEST_ASSERT_FALSE(result);
}

void test_validate_temperature_range_invalid_above_max_edge(void) {
    float temp = 125.1f;
    bool result = validate_temperature_range(temp);
    // Expected: 125.1f is just above the maximum valid edge, thus invalid
    TEST_ASSERT_FALSE(result);
}

void test_validate_temperature_range_invalid_very_low(void) {
    float temp = 0.0f;
    bool result = validate_temperature_range(temp);
    // Expected: 0.0f is significantly below the minimum valid edge, thus invalid
    TEST_ASSERT_FALSE(result);
}

void test_validate_temperature_range_invalid_very_high(void) {
    float temp = 200.0f;
    bool result = validate_temperature_range(temp);
    // Expected: 200.0f is significantly above the maximum valid edge, thus invalid
    TEST_ASSERT_FALSE(result);
}

// ==== Test Cases for check_temperature_status() ====
void test_check_temperature_status_critical_above_120(void) {
    const char* status = check_temperature_status(120.1f);
    // Expected: 120.1f is > 120.0f, so status is "CRITICAL"
    TEST_ASSERT_EQUAL_STRING("CRITICAL", status);

    status = check_temperature_status(150.0f);
    // Expected: 150.0f is > 120.0f, so status is "CRITICAL"
    TEST_ASSERT_EQUAL_STRING("CRITICAL", status);
}

void test_check_temperature_status_hot_above_85_edge(void) {
    const char* status = check_temperature_status(85.1f);
    // Expected: 85.1f is > 85.0f and not > 120.0f, so status is "HOT"
    TEST_ASSERT_EQUAL_STRING("HOT", status);

    status = check_temperature_status(100.0f);
    // Expected: 100.0f is > 85.0f and not > 120.0f, so status is "HOT"
    TEST_ASSERT_EQUAL_STRING("HOT", status);
}

void test_check_temperature_status_hot_below_120_edge(void) {
    const char* status = check_temperature_status(120.0f);
    // Expected: 120.0f is NOT > 120.0f, but IS > 85.0f, so status is "HOT"
    TEST_ASSERT_EQUAL_STRING("HOT", status);
}

void test_check_temperature_status_cold_below_neg10_edge(void) {
    const char* status = check_temperature_status(0.0f);
    // Expected: 0.0f is < 0.0f, so status is "COLD"
    TEST_ASSERT_EQUAL_STRING("COLD", status);

    status = check_temperature_status(0.0f);
    // Expected: 0.0f is < 0.0f, so status is "COLD"
    TEST_ASSERT_EQUAL_STRING("COLD", status);
}

void test_check_temperature_status_normal_mid_range(void) {
    const char* status = check_temperature_status(25.0f);
    // Expected: 25.0f is not > 120, not > 85, and not < 0.0f, so status is "NORMAL"
    TEST_ASSERT_EQUAL_STRING("NORMAL", status);

    status = check_temperature_status(0.0f);
    // Expected: 0.0f is not > 120, not > 85, and not < 0.0f, so status is "NORMAL"
    TEST_ASSERT_EQUAL_STRING("NORMAL", status);
}

void test_check_temperature_status_normal_cold_edge(void) {
    const char* status = check_temperature_status(0.0f);
    // Expected: 0.0f is NOT < 0.0f, so it falls into "NORMAL"
    TEST_ASSERT_EQUAL_STRING("NORMAL", status);
}

void test_check_temperature_status_normal_hot_edge(void) {
    const char* status = check_temperature_status(85.0f);
    // Expected: 85.0f is NOT > 85.0f, so it falls into "NORMAL"
    TEST_ASSERT_EQUAL_STRING("NORMAL", status);
}

// ==== Test Cases for get_temperature_celsius() ====
// This function calls read_temperature_raw() which is non-deterministic (uses rand()).
// We can only test that raw_to_celsius is called with a value in the expected range (00.0f)
// and that the final return value matches the stubbed raw_to_celsius result.
void test_get_temperature_celsius_calls_dependencies_and_returns_value(void) {
    // Configure the stub to return a specific Celsius value
    float expected_celsius = 25.5f;
    stub_raw_to_celsius.return_value = expected_celsius;

    // Call the function under test
    float result = get_temperature_celsius();

    // Expected: raw_to_celsius should have been called
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    // Expected: raw_to_celsius should have been called exactly once
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    // Expected: The raw value passed to raw_to_celsius should be within 00.0f
    TEST_ASSERT_GREATER_OR_EQUAL_INT(0, stub_raw_to_celsius.last_raw_val);
    TEST_ASSERT_LESS_OR_EQUAL_INT(1024, stub_raw_to_celsius.last_raw_val);
    // Expected: The returned Celsius value should match the stubbed return value
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, result);
}

void test_get_temperature_celsius_low_raw_conversion(void) {
    // Simulate a low raw value leading to a low Celsius by setting the stub's return
    float expected_celsius = 0.0f;
    stub_raw_to_celsius.return_value = expected_celsius;

    float result = get_temperature_celsius();

    // Expected: raw_to_celsius should have been called
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    // Expected: The raw value passed to raw_to_celsius should be within 00.0f
    TEST_ASSERT_GREATER_OR_EQUAL_INT(0, stub_raw_to_celsius.last_raw_val);
    TEST_ASSERT_LESS_OR_EQUAL_INT(1024, stub_raw_to_celsius.last_raw_val);
    // Expected: The returned Celsius value should match the stubbed return value
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, result);
}

void test_get_temperature_celsius_high_raw_conversion(void) {
    // Simulate a high raw value leading to a high Celsius by setting the stub's return
    float expected_celsius = 100.0f;
    stub_raw_to_celsius.return_value = expected_celsius;

    float result = get_temperature_celsius();

    // Expected: raw_to_celsius should have been called
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    // Expected: The raw value passed to raw_to_celsius should be within 00.0f
    TEST_ASSERT_GREATER_OR_EQUAL_INT(0, stub_raw_to_celsius.last_raw_val);
    TEST_ASSERT_LESS_OR_EQUAL_INT(1024, stub_raw_to_celsius.last_raw_val);
    // Expected: The returned Celsius value should match the stubbed return value
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, result);
}

// ==== Main function for running tests ====


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_read_temperature_raw_returns_in_range);
    RUN_TEST(test_validate_temperature_range_valid_mid_range);
    RUN_TEST(test_validate_temperature_range_valid_min_edge);
    RUN_TEST(test_validate_temperature_range_valid_max_edge);
    RUN_TEST(test_validate_temperature_range_invalid_below_min_edge);
    RUN_TEST(test_validate_temperature_range_invalid_above_max_edge);
    RUN_TEST(test_validate_temperature_range_invalid_very_low);
    RUN_TEST(test_validate_temperature_range_invalid_very_high);
    RUN_TEST(test_check_temperature_status_critical_above_120);
    RUN_TEST(test_check_temperature_status_hot_above_85_edge);
    RUN_TEST(test_check_temperature_status_hot_below_120_edge);
    RUN_TEST(test_check_temperature_status_cold_below_neg10_edge);
    RUN_TEST(test_check_temperature_status_normal_mid_range);
    RUN_TEST(test_check_temperature_status_normal_cold_edge);
    RUN_TEST(test_check_temperature_status_normal_hot_edge);
    RUN_TEST(test_get_temperature_celsius_calls_dependencies_and_returns_value);
    RUN_TEST(test_get_temperature_celsius_low_raw_conversion);
    RUN_TEST(test_get_temperature_celsius_high_raw_conversion);

    return UNITY_END();
}