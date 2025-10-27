#include "unity.h"
#include "temp_sensor.h"
#include "temp_converter.h" // For stubbing raw_to_celsius
#include <stdlib.h>         // Required for rand() used by read_temperature_raw()

// --- Stub Implementations ---

// Stub for raw_to_celsius
static int raw_to_celsius_Calls;
static int raw_to_celsius_RawArg_Last;
static float raw_to_celsius_Return_Value;

float raw_to_celsius(int raw) {
    raw_to_celsius_Calls++;
    raw_to_celsius_RawArg_Last = raw;
    return raw_to_celsius_Return_Value;
}

// Helper function to configure the stub's return value
void set_raw_to_celsius_return_value(float value) {
    raw_to_celsius_Return_Value = value;
}

// --- Test Setup and Teardown ---

void setUp(void) {
    // Reset stub state before each test
    raw_to_celsius_Calls = 0;
    raw_to_celsius_RawArg_Last = 0;
    raw_to_celsius_Return_Value = 0.0f;
    // Note: read_temperature_raw() uses rand().
    // We cannot control rand() directly without stubbing it, which is not requested.
    // Tests for read_temperature_raw will therefore check the range of its output.
}

void tearDown(void) {
    // Ensure all stub variables are reset after each test
    raw_to_celsius_Calls = 0;
    raw_to_celsius_RawArg_Last = 0;
    raw_to_celsius_Return_Value = 0.0f;
}

// --- Test Cases for read_temperature_raw ---

void test_read_temperature_raw_returns_value_in_expected_range(void) {
    // rand() % 1024 should produce values from 0 to 1023
    int raw_temp = read_temperature_raw();
    TEST_ASSERT_TRUE(raw_temp >= 0);
    TEST_ASSERT_TRUE(raw_temp <= 1023);
}

void test_read_temperature_raw_returns_values_in_range_multiple_times(void) {
    for (int i = 0; i < 10; i++) { // Test multiple calls to ensure range consistency
        int raw_temp = read_temperature_raw();
        TEST_ASSERT_TRUE_MESSAGE(raw_temp >= 0, "Raw temp should be >= 0");
        TEST_ASSERT_TRUE_MESSAGE(raw_temp <= 1023, "Raw temp should be <= 1023");
    }
}

// --- Test Cases for validate_temperature_range ---

void test_validate_temperature_range_valid_min_boundary(void) {
    TEST_ASSERT_TRUE(validate_temperature_range(-40.0f));
}

void test_validate_temperature_range_valid_max_boundary(void) {
    TEST_ASSERT_TRUE(validate_temperature_range(125.0f));
}

void test_validate_temperature_range_valid_mid_range(void) {
    TEST_ASSERT_TRUE(validate_temperature_range(25.0f));
}

void test_validate_temperature_range_invalid_just_below_min(void) {
    TEST_ASSERT_FALSE(validate_temperature_range(-40.01f));
}

void test_validate_temperature_range_invalid_just_above_max(void) {
    TEST_ASSERT_FALSE(validate_temperature_range(125.01f));
}

void test_validate_temperature_range_invalid_far_below_min(void) {
    TEST_ASSERT_FALSE(validate_temperature_range(-100.0f));
}

void test_validate_temperature_range_invalid_far_above_max(void) {
    TEST_ASSERT_FALSE(validate_temperature_range(200.0f));
}

// --- Test Cases for check_temperature_status ---

void test_check_temperature_status_critical_above_120(void) {
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(120.01f));
}

void test_check_temperature_status_critical_at_max_range(void) {
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(125.0f));
}

void test_check_temperature_status_hot_above_85(void) {
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(85.01f));
}

void test_check_temperature_status_hot_at_120_boundary(void) {
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(120.0f));
}

void test_check_temperature_status_cold_below_neg10(void) {
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(-10.01f));
}

void test_check_temperature_status_cold_at_min_range(void) {
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(-40.0f));
}

void test_check_temperature_status_normal_at_neg10_boundary(void) {
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(-10.0f));
}

void test_check_temperature_status_normal_at_85_boundary(void) {
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(85.0f));
}

void test_check_temperature_status_normal_mid_range(void) {
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(25.0f));
}

// --- Test Cases for get_temperature_celsius ---

void test_get_temperature_celsius_calls_raw_to_celsius_and_returns_converted_value(void) {
    set_raw_to_celsius_return_value(25.5f);
    float result = get_temperature_celsius();

    TEST_ASSERT_EQUAL_INT(1, raw_to_celsius_Calls); // Verify stub was called once
    // The raw argument passed to raw_to_celsius comes from read_temperature_raw(), which uses rand().
    // So we can only assert that it's within the expected range.
    TEST_ASSERT_TRUE(raw_to_celsius_RawArg_Last >= 0);
    TEST_ASSERT_TRUE(raw_to_celsius_RawArg_Last <= 1023);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 25.5f, result); // Verify the returned value
}

void test_get_temperature_celsius_with_negative_conversion(void) {
    set_raw_to_celsius_return_value(-5.0f);
    float result = get_temperature_celsius();

    TEST_ASSERT_EQUAL_INT(1, raw_to_celsius_Calls);
    TEST_ASSERT_TRUE(raw_to_celsius_RawArg_Last >= 0);
    TEST_ASSERT_TRUE(raw_to_celsius_RawArg_Last <= 1023);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, -5.0f, result);
}

void test_get_temperature_celsius_with_zero_conversion(void) {
    set_raw_to_celsius_return_value(0.0f);
    float result = get_temperature_celsius();

    TEST_ASSERT_EQUAL_INT(1, raw_to_celsius_Calls);
    TEST_ASSERT_TRUE(raw_to_celsius_RawArg_Last >= 0);
    TEST_ASSERT_TRUE(raw_to_celsius_RawArg_Last <= 1023);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 0.0f, result);
}

// --- Main for Unity Test Runner ---


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_read_temperature_raw_returns_value_in_expected_range);
    RUN_TEST(test_read_temperature_raw_returns_values_in_range_multiple_times);
    RUN_TEST(test_validate_temperature_range_valid_min_boundary);
    RUN_TEST(test_validate_temperature_range_valid_max_boundary);
    RUN_TEST(test_validate_temperature_range_valid_mid_range);
    RUN_TEST(test_validate_temperature_range_invalid_just_below_min);
    RUN_TEST(test_validate_temperature_range_invalid_just_above_max);
    RUN_TEST(test_validate_temperature_range_invalid_far_below_min);
    RUN_TEST(test_validate_temperature_range_invalid_far_above_max);
    RUN_TEST(test_check_temperature_status_critical_above_120);
    RUN_TEST(test_check_temperature_status_critical_at_max_range);
    RUN_TEST(test_check_temperature_status_hot_above_85);
    RUN_TEST(test_check_temperature_status_hot_at_120_boundary);
    RUN_TEST(test_check_temperature_status_cold_below_neg10);
    RUN_TEST(test_check_temperature_status_cold_at_min_range);
    RUN_TEST(test_check_temperature_status_normal_at_neg10_boundary);
    RUN_TEST(test_check_temperature_status_normal_at_85_boundary);
    RUN_TEST(test_check_temperature_status_normal_mid_range);
    RUN_TEST(test_get_temperature_celsius_calls_raw_to_celsius_and_returns_converted_value);
    RUN_TEST(test_get_temperature_celsius_with_negative_conversion);
    RUN_TEST(test_get_temperature_celsius_with_zero_conversion);

    return UNITY_END();
}