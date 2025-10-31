/* test_temp_sensor.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h> // For memset
#include <stdlib.h> // For rand(), srand()

// temp_sensor.c functions (declared extern as no public header is provided and not part of test file)
extern int read_temperature_raw(void);
extern bool validate_temperature_range(float temp_c);
extern const char* check_temperature_status(float temp_c);
extern float get_temperature_celsius(void);

// --- External Stub Definitions ---
// Function to stub: raw_to_celsius
// Signature inferred from get_temperature_celsius(): float raw_to_celsius(int raw_val)
typedef struct {
    float return_value;
    bool was_called;
    uint32_t call_count;
    int last_raw_param;
} stub_raw_to_celsius_t;

static stub_raw_to_celsius_t stub_raw_to_celsius = {0};

float raw_to_celsius(int raw_val) {
    stub_raw_to_celsius.was_called = true;
    stub_raw_to_celsius.call_count++;
    stub_raw_to_celsius.last_raw_param = raw_val;
    return stub_raw_to_celsius.return_value;
}

// --- Test Fixture Setup and Teardown ---
void setUp(void) {
    // Reset all stubs
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
    // Set default return values for stubs
    stub_raw_to_celsius.return_value = 25.0f; // A nominal temperature
    // For read_temperature_raw, to ensure some determinism for testing raw values,
    // we can re-seed srand. However, since rand() itself is not stubbed,
    // and read_temperature_raw is internal, we will focus on testing the range.
    srand(1); // Seed rand for a somewhat deterministic sequence for range testing
}

void tearDown(void) {
    // Reset all stubs completely
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
}

// --- Tests for read_temperature_raw ---
void test_read_temperature_raw_returns_within_valid_range(void) {
    int raw_temp;
    // Expected: raw_temperature_raw should return a value between 0 and 1023 (inclusive)
    for (int i = 0; i < 100; i++) { // Run multiple times to cover non-deterministic nature
        raw_temp = read_temperature_raw();
        // Expected: Return value must be greater than or equal to 0
        TEST_ASSERT_GREATER_OR_EQUAL_INT(0, raw_temp);
        // Expected: Return value must be less than or equal to 1023 (10240.0f)
        TEST_ASSERT_LESS_OR_EQUAL_INT(1023, raw_temp);
    }
}

// --- Tests for validate_temperature_range ---
void test_validate_temperature_range_valid_min_edge(void) {
    float temp = 0.0f;
    // Expected: 0.0f is valid, as per temp_c >= 0.0f
    TEST_ASSERT_TRUE(validate_temperature_range(temp));
}

void test_validate_temperature_range_invalid_below_min(void) {
    float temp = 0.0f;
    // Expected: 0.0f is invalid, as per temp_c >= 0.0f
    TEST_ASSERT_FALSE(validate_temperature_range(temp));
}

void test_validate_temperature_range_valid_max_edge(void) {
    float temp = 125.0f;
    // Expected: 125.0f is valid, as per temp_c <= 125.0f
    TEST_ASSERT_TRUE(validate_temperature_range(temp));
}

void test_validate_temperature_range_invalid_above_max(void) {
    float temp = 125.1f;
    // Expected: 125.1f is invalid, as per temp_c <= 125.0f
    TEST_ASSERT_FALSE(validate_temperature_range(temp));
}

void test_validate_temperature_range_valid_nominal(void) {
    float temp = 25.0f;
    // Expected: 25.0f is valid, within 0.0f and 125.0f
    TEST_ASSERT_TRUE(validate_temperature_range(temp));
}

// --- Tests for check_temperature_status ---
void test_check_temperature_status_critical_hot_above_edge(void) {
    float temp = 120.1f;
    // Expected: "CRITICAL_HOT" per temp_c > 120.0f
    TEST_ASSERT_EQUAL_STRING("CRITICAL_HOT", check_temperature_status(temp));
}

void test_check_temperature_status_warning_hot_on_critical_edge(void) {
    float temp = 120.0f;
    // Expected: "WARNING_HOT" per else if temp_c > 85.0f (since 120.0f is not > 120.0f)
    TEST_ASSERT_EQUAL_STRING("WARNING_HOT", check_temperature_status(temp));
}

void test_check_temperature_status_warning_hot_above_edge(void) {
    float temp = 85.1f;
    // Expected: "WARNING_HOT" per else if temp_c > 85.0f
    TEST_ASSERT_EQUAL_STRING("WARNING_HOT", check_temperature_status(temp));
}

void test_check_temperature_status_normal_on_warning_edge(void) {
    float temp = 85.0f;
    // Expected: "NORMAL_TEMP" per else (since 85.0f is not > 85.0f)
    TEST_ASSERT_EQUAL_STRING("NORMAL_TEMP", check_temperature_status(temp));
}

void test_check_temperature_status_critical_cold_below_edge(void) {
    float temp = 0.0f;
    // Expected: "CRITICAL_COLD" per else if temp_c < 0.0f
    TEST_ASSERT_EQUAL_STRING("CRITICAL_COLD", check_temperature_status(temp));
}

void test_check_temperature_status_normal_on_cold_edge(void) {
    float temp = 0.0f;
    // Expected: "NORMAL_TEMP" per else (since 0.0f is not < 0.0f)
    TEST_ASSERT_EQUAL_STRING("NORMAL_TEMP", check_temperature_status(temp));
}

void test_check_temperature_status_nominal_mid_range(void) {
    float temp = 25.0f;
    // Expected: "NORMAL_TEMP" per else
    TEST_ASSERT_EQUAL_STRING("NORMAL_TEMP", check_temperature_status(temp));
}

// --- Tests for get_temperature_celsius ---
void test_get_temperature_celsius_nominal_conversion(void) {
    float expected_celsius = 25.5f;
    stub_raw_to_celsius.return_value = expected_celsius;

    float actual_celsius = get_temperature_celsius();

    // Expected: raw_to_celsius should have been called once
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    // Expected: raw_to_celsius should have been called exactly once
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    // Expected: The raw parameter passed to raw_to_celsius must be within 0 and 1023
    TEST_ASSERT_GREATER_OR_EQUAL_INT(0, stub_raw_to_celsius.last_raw_param);
    TEST_ASSERT_LESS_OR_EQUAL_INT(1023, stub_raw_to_celsius.last_raw_param);
    // Expected: The returned Celsius value should match the stub's configured return
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

void test_get_temperature_celsius_cold_conversion(void) {
    float expected_celsius = 0.0f;
    stub_raw_to_celsius.return_value = expected_celsius;

    float actual_celsius = get_temperature_celsius();

    // Expected: raw_to_celsius should have been called once
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    // Expected: raw_to_celsius should have been called exactly once
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    // Expected: The raw parameter passed to raw_to_celsius must be within 0 and 1023
    TEST_ASSERT_GREATER_OR_EQUAL_INT(0, stub_raw_to_celsius.last_raw_param);
    TEST_ASSERT_LESS_OR_EQUAL_INT(1023, stub_raw_to_celsius.last_raw_param);
    // Expected: The returned Celsius value should match the stub's configured return
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

void test_get_temperature_celsius_hot_conversion(void) {
    float expected_celsius = 100.0f;
    stub_raw_to_celsius.return_value = expected_celsius;

    float actual_celsius = get_temperature_celsius();

    // Expected: raw_to_celsius should have been called once
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    // Expected: raw_to_celsius should have been called exactly once
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    // Expected: The raw parameter passed to raw_to_celsius must be within 0 and 1023
    TEST_ASSERT_GREATER_OR_EQUAL_INT(0, stub_raw_to_celsius.last_raw_param);
    TEST_ASSERT_LESS_OR_EQUAL_INT(1023, stub_raw_to_celsius.last_raw_param);
    // Expected: The returned Celsius value should match the stub's configured return
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

// --- Main Test Runner ---


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_read_temperature_raw_returns_within_valid_range);
    RUN_TEST(test_validate_temperature_range_valid_min_edge);
    RUN_TEST(test_validate_temperature_range_invalid_below_min);
    RUN_TEST(test_validate_temperature_range_valid_max_edge);
    RUN_TEST(test_validate_temperature_range_invalid_above_max);
    RUN_TEST(test_validate_temperature_range_valid_nominal);
    RUN_TEST(test_check_temperature_status_critical_hot_above_edge);
    RUN_TEST(test_check_temperature_status_warning_hot_on_critical_edge);
    RUN_TEST(test_check_temperature_status_warning_hot_above_edge);
    RUN_TEST(test_check_temperature_status_normal_on_warning_edge);
    RUN_TEST(test_check_temperature_status_critical_cold_below_edge);
    RUN_TEST(test_check_temperature_status_normal_on_cold_edge);
    RUN_TEST(test_check_temperature_status_nominal_mid_range);
    RUN_TEST(test_get_temperature_celsius_nominal_conversion);
    RUN_TEST(test_get_temperature_celsius_cold_conversion);
    RUN_TEST(test_get_temperature_celsius_hot_conversion);

    return UNITY_END();
}