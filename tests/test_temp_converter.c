/* test_temp_converter.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include "temp_converter.h" // Required to access the functions under test
#include <stdbool.h>       // Required for bool type
#include <string.h>        // Not explicitly needed for this source, but common for setup/teardown

// No external functions to stub, so no stub control structures or implementations needed.

// SetUp function is called before each test
void setUp(void) {
    // No global state or stubs to initialize for this module.
}

// TearDown function is called after each test
void tearDown(void) {
    // No global state or stubs to clean up for this module.
}

// --- Test cases for raw_to_celsius ---

void test_raw_to_celsius_min_adc_value(void) {
    float result;
    // Test with the minimum possible ADC raw value (0)
    result = raw_to_celsius(0);
    // Expected: (0 / 1023.0f) * 165.0f - 40.0f = -40.0f
    TEST_ASSERT_FLOAT_WITHIN(0.1f, -40.0f, result);
}

void test_raw_to_celsius_max_adc_value(void) {
    float result;
    // Test with the maximum possible ADC raw value (1023) for a 10-bit ADC
    result = raw_to_celsius(1023);
    // Expected: (1023 / 1023.0f) * 165.0f - 40.0f = 165.0f - 40.0f = 125.0f
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 125.0f, result);
}

void test_raw_to_celsius_mid_adc_value(void) {
    float result;
    // Test with a mid-range ADC raw value (512, roughly half of 1023)
    result = raw_to_celsius(512);
    // Expected: (512 / 1023.0f) * 165.0f - 40.0f = ~42.7f
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 42.74f, result);
}

void test_raw_to_celsius_cold_value(void) {
    float result;
    // Test with an ADC raw value that results in a cold temperature (e.g., 185 for -10C)
    result = raw_to_celsius(185);
    // Expected: (185 / 1023.0f) * 165.0f - 40.0f = ~-10.2f
    TEST_ASSERT_FLOAT_WITHIN(0.1f, -10.2f, result);
}

void test_raw_to_celsius_hot_value(void) {
    float result;
    // Test with an ADC raw value that results in a hot temperature (e.g., 850 for ~97.5C)
    result = raw_to_celsius(850);
    // Expected: (850 / 1023.0f) * 165.0f - 40.0f = ~97.46f
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 97.46f, result);
}

// --- Test cases for celsius_to_fahrenheit ---

void test_celsius_to_fahrenheit_freezing_point(void) {
    float result;
    // Test with the freezing point of water in Celsius
    result = celsius_to_fahrenheit(0.0f);
    // Expected: (0.0f * 9.0f / 5.0f) + 32.0f = 32.0f
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 32.0f, result);
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    float result;
    // Test with the boiling point of water in Celsius
    result = celsius_to_fahrenheit(100.0f);
    // Expected: (100.0f * 9.0f / 5.0f) + 32.0f = 212.0f
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 212.0f, result);
}

void test_celsius_to_fahrenheit_absolute_min_c_valid_range(void) {
    float result;
    // Test with the minimum temperature output from raw_to_celsius
    result = celsius_to_fahrenheit(0.0f);
    // Expected: (0.0f * 9.0f / 5.0f) + 32.0f = 0.0f + 32.0f = 32.0f
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 32.0f, result);
}

void test_celsius_to_fahrenheit_absolute_max_c_valid_range(void) {
    float result;
    // Test with the maximum temperature output from raw_to_celsius
    result = celsius_to_fahrenheit(125.0f);
    // Expected: (125.0f * 9.0f / 5.0f) + 32.0f = 225.0f + 32.0f = 257.0f
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 257.0f, result);
}

void test_celsius_to_fahrenheit_room_temp(void) {
    float result;
    // Test with a typical room temperature in Celsius
    result = celsius_to_fahrenheit(25.0f);
    // Expected: (25.0f * 9.0f / 5.0f) + 32.0f = 45.0f + 32.0f = 77.0f
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 77.0f, result);
}

// --- Test cases for is_temperature_rising ---

void test_is_temperature_rising_true_positive(void) {
    bool result;
    // Current temperature is significantly higher than previous, exceeding threshold
    result = is_temperature_rising(20.0f, 25.0f, 3.0f);
    // Expected: (25.0f - 20.0f) > 3.0f => 5.0f > 3.0f is true
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_false_negative_below_threshold(void) {
    bool result;
    // Current temperature is slightly higher, but not enough to exceed threshold
    result = is_temperature_rising(20.0f, 22.0f, 3.0f);
    // Expected: (22.0f - 20.0f) > 3.0f => 2.0f > 3.0f is false
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_false_negative_equal_threshold(void) {
    bool result;
    // Current temperature increase exactly equals the threshold, so it's not "greater than"
    result = is_temperature_rising(20.0f, 23.0f, 3.0f);
    // Expected: (23.0f - 20.0f) > 3.0f => 3.0f > 3.0f is false
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_false_negative_decreasing(void) {
    bool result;
    // Current temperature is lower than previous temperature
    result = is_temperature_rising(25.0f, 20.0f, 3.0f);
    // Expected: (20.0f - 25.0f) > 3.0f => 0.0f > 3.0f is false
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_no_change(void) {
    bool result;
    // Current temperature is the same as previous, with a positive threshold
    result = is_temperature_rising(20.0f, 20.0f, 1.0f);
    // Expected: (20.0f - 20.0f) > 1.0f => 0.0f > 1.0f is false
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_edge_threshold_zero_rising(void) {
    bool result;
    // Test with a zero threshold, temperature is rising
    result = is_temperature_rising(20.0f, 20.1f, 0.0f);
    // Expected: (20.1f - 20.0f) > 0.0f => 0.1f > 0.0f is true
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_edge_threshold_zero_not_rising(void) {
    bool result;
    // Test with a zero threshold, temperature is not rising (or decreasing)
    result = is_temperature_rising(20.0f, 20.0f, 0.0f);
    // Expected: (20.0f - 20.0f) > 0.0f => 0.0f > 0.0f is false
    TEST_ASSERT_FALSE(result);
}



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_min_adc_value);
    RUN_TEST(test_raw_to_celsius_max_adc_value);
    RUN_TEST(test_raw_to_celsius_mid_adc_value);
    RUN_TEST(test_raw_to_celsius_cold_value);
    RUN_TEST(test_raw_to_celsius_hot_value);
    RUN_TEST(test_celsius_to_fahrenheit_freezing_point);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_absolute_min_c_valid_range);
    RUN_TEST(test_celsius_to_fahrenheit_absolute_max_c_valid_range);
    RUN_TEST(test_celsius_to_fahrenheit_room_temp);
    RUN_TEST(test_is_temperature_rising_true_positive);
    RUN_TEST(test_is_temperature_rising_false_negative_below_threshold);
    RUN_TEST(test_is_temperature_rising_false_negative_equal_threshold);
    RUN_TEST(test_is_temperature_rising_false_negative_decreasing);
    RUN_TEST(test_is_temperature_rising_no_change);
    RUN_TEST(test_is_temperature_rising_edge_threshold_zero_rising);
    RUN_TEST(test_is_temperature_rising_edge_threshold_zero_not_rising);

    return UNITY_END();
}