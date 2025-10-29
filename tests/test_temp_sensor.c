/* test_temp_sensor.c – Auto-generated Expert Unity Tests */

#include "unity.h"
#include "temp_sensor.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h> // Required for memset in setUp/tearDown

// =================================================================================================
// EXTERNAL FUNCTION STUBS
//
// These stubs are for functions declared in other modules but called by temp_sensor.c.
// They allow isolation of the unit under test (temp_sensor.c).
// =================================================================================================

// Stub control structure for raw_to_celsius
typedef struct {
    float return_value;
    bool was_called;
    uint32_t call_count;
    int last_raw_param;
} stub_raw_to_celsius_t;

static stub_raw_to_celsius_t stub_raw_to_celsius = {0};

// Stub implementation for raw_to_celsius
// Inferred signature: float raw_to_celsius(int raw)
float raw_to_celsius(int raw) {
    stub_raw_to_celsius.was_called = true;
    stub_raw_to_celsius.call_count++;
    stub_raw_to_celsius.last_raw_param = raw;
    return stub_raw_to_celsius.return_value;
}

// =================================================================================================
// TEST FIXTURES
//
// setUp and tearDown functions ensure a clean state for each test.
// =================================================================================================

void setUp(void) {
    // Reset all stub control structures before each test
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
}

void tearDown(void) {
    // Reset all stub control structures after each test
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
}

// =================================================================================================
// TEST CASES FOR read_temperature_raw
// int read_temperature_raw()
// Logic: return rand() % 1024;
// =================================================================================================

void test_read_temperature_raw_returns_in_expected_range(void) {
    int raw_temp;

    // Expected: The raw temperature should be between 0 and 1023 (inclusive) due to the % 1024 operation.
    // As rand() is non-deterministic and read_temperature_raw is internal (cannot be stubbed),
    // we only test the guaranteed range.
    raw_temp = read_temperature_raw();
    TEST_ASSERT_TRUE_MESSAGE(raw_temp >= 0 && raw_temp < 1024, "Raw temp should be between 0 and 1023");

    raw_temp = read_temperature_raw(); // Call again to check consistency
    TEST_ASSERT_TRUE_MESSAGE(raw_temp >= 0 && raw_temp < 1024, "Raw temp should be between 0 and 1023 on second call");
}

// =================================================================================================
// TEST CASES FOR validate_temperature_range
// bool validate_temperature_range(float temp_c)
// Logic: return temp_c >= 0.0f && temp_c <= 125.0f;
// =================================================================================================

void test_validate_temperature_range_valid_min_edge(void) {
    // Expected: 0.0f is the minimum valid temperature, so it should return true.
    TEST_ASSERT_TRUE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_invalid_below_min_edge(void) {
    // Expected: 0.0f is just below the minimum valid temperature, so it should return false.
    TEST_ASSERT_FALSE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_valid_max_edge(void) {
    // Expected: 125.0f is the maximum valid temperature, so it should return true.
    TEST_ASSERT_TRUE(validate_temperature_range(125.0f));
}

void test_validate_temperature_range_invalid_above_max_edge(void) {
    // Expected: 125.1f is just above the maximum valid temperature, so it should return false.
    TEST_ASSERT_FALSE(validate_temperature_range(125.1f));
}

void test_validate_temperature_range_valid_mid_range(void) {
    // Expected: 25.0f is within the valid range [0.0f, 125.0f], so it should return true.
    TEST_ASSERT_TRUE(validate_temperature_range(25.0f));
}

void test_validate_temperature_range_invalid_extreme_low(void) {
    // Expected: 0.0f is well below the minimum valid temperature, so it should return false.
    TEST_ASSERT_FALSE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_invalid_extreme_high(void) {
    // Expected: 200.0f is well above the maximum valid temperature, so it should return false.
    TEST_ASSERT_FALSE(validate_temperature_range(200.0f));
}

// =================================================================================================
// TEST CASES FOR check_temperature_status
// const char* check_temperature_status(float temp_c)
// Logic: if/else if/else branches for CRITICAL (>120), HOT (>85), COLD (<0.0f), NORMAL (otherwise)
// =================================================================================================

void test_check_temperature_status_critical_above_threshold(void) {
    // Expected: 120.1f is greater than 120.0f, so status should be "CRITICAL".
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(120.1f));
}

void test_check_temperature_status_critical_max_valid_temp(void) {
    // Expected: 125.0f is greater than 120.0f, so status should be "CRITICAL".
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(125.0f));
}

void test_check_temperature_status_hot_above_threshold(void) {
    // Expected: 85.1f is greater than 85.0f but not > 120.0f, so status should be "HOT".
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(85.1f));
}

void test_check_temperature_status_hot_below_critical_edge(void) {
    // Expected: 120.0f is not > 120.0f but is > 85.0f, so status should be "HOT".
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(120.0f));
}

void test_check_temperature_status_cold_below_threshold(void) {
    // Expected: 0.0f is less than 0.0f, so status should be "COLD".
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(0.0f));
}

void test_check_temperature_status_cold_min_valid_temp(void) {
    // Expected: 0.0f is less than 0.0f, so status should be "COLD".
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(0.0f));
}

void test_check_temperature_status_normal_mid_range(void) {
    // Expected: 25.0f is not > 120.0f, not > 85.0f, and not < 0.0f, so status should be "NORMAL".
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(25.0f));
}

void test_check_temperature_status_normal_above_cold_edge(void) {
    // Expected: 0.0f is not < 0.0f, so status should be "NORMAL".
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(0.0f));
}

void test_check_temperature_status_normal_below_hot_edge(void) {
    // Expected: 85.0f is not > 85.0f, so status should be "NORMAL".
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(85.0f));
}

// =================================================================================================
// TEST CASES FOR get_temperature_celsius
// float get_temperature_celsius()
// Logic: int raw = read_temperature_raw(); return raw_to_celsius(raw);
// =================================================================================================

void test_get_temperature_celsius_calls_dependencies_and_returns_converted_value(void) {
    // Expected: get_temperature_celsius should call read_temperature_raw (internal, non-stubbed),
    // then pass its result to raw_to_celsius (external, stubbed), and return the stubbed value.
    float expected_celsius = 42.5f;
    stub_raw_to_celsius.return_value = expected_celsius;

    float result = get_temperature_celsius();

    // Verify raw_to_celsius was called exactly once
    TEST_ASSERT_TRUE_MESSAGE(stub_raw_to_celsius.was_called, "raw_to_celsius should have been called.");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(1, stub_raw_to_celsius.call_count, "raw_to_celsius should have been called exactly once.");

    // Verify the parameter passed to raw_to_celsius (from read_temperature_raw) is in range
    TEST_ASSERT_TRUE_MESSAGE(stub_raw_to_celsius.last_raw_param >= 0 && stub_raw_to_celsius.last_raw_param < 1024,
                             "raw_to_celsius should receive a raw value between 0 and 1023.");

    // Verify get_temperature_celsius returns the value provided by the stub
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, result);
}

void test_get_temperature_celsius_another_stubbed_value(void) {
    // Expected: Test with a different stub return to ensure flexibility and correct propagation.
    float expected_celsius = 0.0f;
    stub_raw_to_celsius.return_value = expected_celsius;

    float result = get_temperature_celsius();

    TEST_ASSERT_TRUE_MESSAGE(stub_raw_to_celsius.was_called, "raw_to_celsius should have been called.");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(1, stub_raw_to_celsius.call_count, "raw_to_celsius should have been called exactly once.");
    TEST_ASSERT_TRUE_MESSAGE(stub_raw_to_celsius.last_raw_param >= 0 && stub_raw_to_celsius.last_raw_param < 1024,
                             "raw_to_celsius should receive a raw value between 0 and 1023.");
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, result);
}

// =================================================================================================
// MAIN TEST RUNNER
// =================================================================================================



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_read_temperature_raw_returns_in_expected_range);
    RUN_TEST(test_validate_temperature_range_valid_min_edge);
    RUN_TEST(test_validate_temperature_range_invalid_below_min_edge);
    RUN_TEST(test_validate_temperature_range_valid_max_edge);
    RUN_TEST(test_validate_temperature_range_invalid_above_max_edge);
    RUN_TEST(test_validate_temperature_range_valid_mid_range);
    RUN_TEST(test_validate_temperature_range_invalid_extreme_low);
    RUN_TEST(test_validate_temperature_range_invalid_extreme_high);
    RUN_TEST(test_check_temperature_status_critical_above_threshold);
    RUN_TEST(test_check_temperature_status_critical_max_valid_temp);
    RUN_TEST(test_check_temperature_status_hot_above_threshold);
    RUN_TEST(test_check_temperature_status_hot_below_critical_edge);
    RUN_TEST(test_check_temperature_status_cold_below_threshold);
    RUN_TEST(test_check_temperature_status_cold_min_valid_temp);
    RUN_TEST(test_check_temperature_status_normal_mid_range);
    RUN_TEST(test_check_temperature_status_normal_above_cold_edge);
    RUN_TEST(test_check_temperature_status_normal_below_hot_edge);
    RUN_TEST(test_get_temperature_celsius_calls_dependencies_and_returns_converted_value);
    RUN_TEST(test_get_temperature_celsius_another_stubbed_value);

    return UNITY_END();
}