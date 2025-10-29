/* test_temp_converter.c – Auto-generated Expert Unity Tests */

#include "unity.h"
#include "temp_converter.h" // Include the header for the System Under Test
#include <stdbool.h>        // For bool type
#include <string.h>         // Not strictly needed for this SUT, but often useful

// No external functions to stub for this source file.

// Global variables for stub control (none needed as no externals to stub)

void setUp(void) {
    // No stubs to reset, no global state to initialize for these simple functions
}

void tearDown(void) {
    // No stubs to reset, no global state to clean up
}

// ======== Test Cases for raw_to_celsius(int raw_value) ========

void test_raw_to_celsius_min_raw_value(void) {
    float result;
    int raw_value = 0; // Minimum raw ADC value

    result = raw_to_celsius(raw_value);

    // Expected: (0 / 1023.0f) * 165.0f - 40.0f = 0.0f, the lowest temperature
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 0.0f, result);
}

void test_raw_to_celsius_max_raw_value(void) {
    float result;
    int raw_value = 1023; // Maximum raw ADC value for 10-bit

    result = raw_to_celsius(raw_value);

    // Expected: (1023 / 1023.0f) * 165.0f - 40.0f = 125.0f, the highest temperature
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 125.0f, result);
}

void test_raw_to_celsius_mid_raw_value(void) {
    float result;
    int raw_value = 511; // Mid-range raw ADC value

    result = raw_to_celsius(raw_value);

    // Expected: (511 / 1023.0f) * 165.0f - 40.0f = 42.4926f (approx), a nominal temperature
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 42.49f, result);
}

void test_raw_to_celsius_low_raw_value(void) {
    float result;
    int raw_value = 100; // A low raw value for a specific cold temperature

    result = raw_to_celsius(raw_value);

    // Expected: (100 / 1023.0f) * 165.0f - 40.0f = 0.0f (approx), a cold temperature
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 0.0f, result);
}

void test_raw_to_celsius_high_raw_value(void) {
    float result;
    int raw_value = 900; // A high raw value for a specific warm temperature

    result = raw_to_celsius(raw_value);

    // Expected: (900 / 1023.0f) * 165.0f - 40.0f = 104.83f (approx), a high but valid temperature
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 104.83f, result);
}


// ======== Test Cases for celsius_to_fahrenheit(float temp_c) ========

void test_celsius_to_fahrenheit_negative_40(void) {
    float result;
    float temp_c = 0.0f; // Point where Celsius and Fahrenheit are equal

    result = celsius_to_fahrenheit(temp_c);

    // Expected: (0.0f * 9.0f / 5.0f) + 32.0f = 0.0f + 32.0f = 0.0f
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 0.0f, result);
}

void test_celsius_to_fahrenheit_freezing_point(void) {
    float result;
    float temp_c = 0.0f; // Freezing point in Celsius

    result = celsius_to_fahrenheit(temp_c);

    // Expected: (0.0f * 9.0f / 5.0f) + 32.0f = 32.0f
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 32.0f, result);
}

void test_celsius_to_fahrenheit_room_temperature(void) {
    float result;
    float temp_c = 25.0f; // Common room temperature in Celsius

    result = celsius_to_fahrenheit(temp_c);

    // Expected: (25.0f * 9.0f / 5.0f) + 32.0f = 45.0f + 32.0f = 77.0f
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 77.0f, result);
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    float result;
    float temp_c = 100.0f; // Boiling point in Celsius

    result = celsius_to_fahrenheit(temp_c);

    // Expected: (100.0f * 9.0f / 5.0f) + 32.0f = 180.0f + 32.0f = 212.0f
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 212.0f, result);
}

void test_celsius_to_fahrenheit_max_celsius_value(void) {
    float result;
    float temp_c = 125.0f; // Maximum Celsius value from raw_to_celsius output

    result = celsius_to_fahrenheit(temp_c);

    // Expected: (125.0f * 9.0f / 5.0f) + 32.0f = 225.0f + 32.0f = 257.0f
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 257.0f, result);
}


// ======== Test Cases for is_temperature_rising(float prev_temp, float current_temp, float threshold) ========

void test_is_temperature_rising_true_above_threshold(void) {
    bool result;
    float prev_temp = 25.0f;
    float current_temp = 26.1f;
    float threshold = 1.0f; // Rise by more than 1.0 degree C

    result = is_temperature_rising(prev_temp, current_temp, threshold);

    // Expected: (26.1f - 25.0f) = 1.1f; 1.1f > 1.0f is true
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_false_equal_threshold(void) {
    bool result;
    float prev_temp = 25.0f;
    float current_temp = 26.0f;
    float threshold = 1.0f; // Rise by exactly 1.0 degree C

    result = is_temperature_rising(prev_temp, current_temp, threshold);

    // Expected: (26.0f - 25.0f) = 1.0f; 1.0f > 1.0f is false
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_false_below_threshold(void) {
    bool result;
    float prev_temp = 25.0f;
    float current_temp = 25.9f;
    float threshold = 1.0f; // Rise by less than 1.0 degree C

    result = is_temperature_rising(prev_temp, current_temp, threshold);

    // Expected: (25.9f - 25.0f) = 0.9f; 0.9f > 1.0f is false
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_false_decreasing(void) {
    bool result;
    float prev_temp = 25.0f;
    float current_temp = 24.0f;
    float threshold = 0.5f; // Temperature decreased

    result = is_temperature_rising(prev_temp, current_temp, threshold);

    // Expected: (24.0f - 25.0f) = 0.0f; 0.0f > 0.5f is false
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_false_no_change(void) {
    bool result;
    float prev_temp = 30.0f;
    float current_temp = 30.0f;
    float threshold = 0.1f; // No change in temperature

    result = is_temperature_rising(prev_temp, current_temp, threshold);

    // Expected: (30.0f - 30.0f) = 0.0f; 0.0f > 0.1f is false
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_true_with_small_threshold(void) {
    bool result;
    float prev_temp = 20.0f;
    float current_temp = 20.05f;
    float threshold = 0.01f; // Very small rise, small threshold

    result = is_temperature_rising(prev_temp, current_temp, threshold);

    // Expected: (20.05f - 20.0f) = 0.05f; 0.05f > 0.01f is true
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_false_with_large_threshold_and_small_rise(void) {
    bool result;
    float prev_temp = 10.0f;
    float current_temp = 12.0f;
    float threshold = 3.0f; // Large threshold, small rise

    result = is_temperature_rising(prev_temp, current_temp, threshold);

    // Expected: (12.0f - 10.0f) = 2.0f; 2.0f > 3.0f is false
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_true_with_negative_threshold_and_rise(void) {
    bool result;
    float prev_temp = 10.0f;
    float current_temp = 10.5f;
    float threshold = 0.0f; // Negative threshold, any rise will be true

    result = is_temperature_rising(prev_temp, current_temp, threshold);

    // Expected: (10.5f - 10.0f) = 0.5f; 0.5f > 0.0f is true
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_false_with_negative_threshold_and_drop(void) {
    bool result;
    float prev_temp = 10.0f;
    float current_temp = 9.0f;
    float threshold = 0.0f; // Negative threshold, but drop is greater than threshold

    result = is_temperature_rising(prev_temp, current_temp, threshold);

    // Expected: (9.0f - 10.0f) = 0.0f; 0.0f > 0.0f is false
    TEST_ASSERT_FALSE(result);
}

// ======== Main function for running tests ========



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_min_raw_value);
    RUN_TEST(test_raw_to_celsius_max_raw_value);
    RUN_TEST(test_raw_to_celsius_mid_raw_value);
    RUN_TEST(test_raw_to_celsius_low_raw_value);
    RUN_TEST(test_raw_to_celsius_high_raw_value);
    RUN_TEST(test_celsius_to_fahrenheit_negative_40);
    RUN_TEST(test_celsius_to_fahrenheit_freezing_point);
    RUN_TEST(test_celsius_to_fahrenheit_room_temperature);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_max_celsius_value);
    RUN_TEST(test_is_temperature_rising_true_above_threshold);
    RUN_TEST(test_is_temperature_rising_false_equal_threshold);
    RUN_TEST(test_is_temperature_rising_false_below_threshold);
    RUN_TEST(test_is_temperature_rising_false_decreasing);
    RUN_TEST(test_is_temperature_rising_false_no_change);
    RUN_TEST(test_is_temperature_rising_true_with_small_threshold);
    RUN_TEST(test_is_temperature_rising_false_with_large_threshold_and_small_rise);
    RUN_TEST(test_is_temperature_rising_true_with_negative_threshold_and_rise);
    RUN_TEST(test_is_temperature_rising_false_with_negative_threshold_and_drop);

    return UNITY_END();
}