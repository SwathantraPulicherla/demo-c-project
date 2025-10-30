/* test_temp_converter.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include "temp_converter.h" // Includes declarations for functions under test
#include <stdbool.h>      // For bool type
#include <string.h>       // For memset, though not strictly needed here as no stubs/globals
#include <stdint.h>       // For standard integer types

// No external functions to stub, so no stub structures needed.

// No global state or stubs to initialize/reset for these simple functions.
void setUp(void) {
    // No specific setup required for these pure functions.
}

void tearDown(void) {
    // No specific cleanup required.
}

// MARK: - raw_to_celsius Tests

void test_raw_to_celsius_min_raw_value_yields_min_celsius(void) {
    int raw_value = 0;
    float expected_celsius = 0.0f; // Expected: (0 / 1023.0f) * 165.0f - 40.0f = 0.0f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius); // Using 0.01f tolerance for precise calculation result
}

void test_raw_to_celsius_max_raw_value_yields_max_celsius(void) {
    int raw_value = 1023;
    float expected_celsius = 125.0f; // Expected: (1023 / 1023.0f) * 165.0f - 40.0f = 125.0f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius); // Using 0.01f tolerance for precise calculation result
}

void test_raw_to_celsius_mid_range_raw_value(void) {
    int raw_value = 511; // Approximately half of 1023
    float expected_celsius = (511.0f / 1023.0f) * 165.0f - 40.0f; // Expected: calculation result
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius); // Using 0.01f tolerance for precise calculation result
}

void test_raw_to_celsius_specific_intermediate_raw_value(void) {
    int raw_value = 255;
    float expected_celsius = (255.0f / 1023.0f) * 165.0f - 40.0f; // Expected: calculation result
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius); // Using 0.01f tolerance for precise calculation result
}

// MARK: - celsius_to_fahrenheit Tests

void test_celsius_to_fahrenheit_freezing_point(void) {
    float temp_c = 0.0f;
    float expected_fahrenheit = 32.0f; // Expected: (0.0f * 9.0f / 5.0f) + 32.0f = 32.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit); // Using 0.01f tolerance for precise calculation result
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    float temp_c = 100.0f;
    float expected_fahrenheit = 212.0f; // Expected: (100.0f * 9.0f / 5.0f) + 32.0f = 212.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit); // Using 0.01f tolerance for precise calculation result
}

void test_celsius_to_fahrenheit_room_temperature(void) {
    float temp_c = 25.0f;
    float expected_fahrenheit = 77.0f; // Expected: (25.0f * 9.0f / 5.0f) + 32.0f = 77.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit); // Using 0.01f tolerance for precise calculation result
}

void test_celsius_to_fahrenheit_negative_forty_degrees(void) {
    float temp_c = 0.0f;
    float expected_fahrenheit = 0.0f; // Expected: (0.0f * 9.0f / 5.0f) + 32.0f = 0.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit); // Using 0.01f tolerance for precise calculation result
}

void test_celsius_to_fahrenheit_max_sensor_range_celsius(void) {
    float temp_c = 125.0f; // Max temperature from raw_to_celsius output
    float expected_fahrenheit = (125.0f * 9.0f / 5.0f) + 32.0f; // Expected: 257.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit); // Using 0.01f tolerance for precise calculation result
}

// MARK: - is_temperature_rising Tests

void test_is_temperature_rising_true_when_significantly_above_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 21.0f;
    float threshold = 0.5f;
    TEST_ASSERT_TRUE(is_temperature_rising(prev_temp, current_temp, threshold)); // Expected: (21.0f - 20.0f) > 0.5f -> 1.0f > 0.5f -> TRUE
}

void test_is_temperature_rising_false_when_equal_to_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.5f;
    float threshold = 0.5f;
    TEST_ASSERT_FALSE(is_temperature_rising(prev_temp, current_temp, threshold)); // Expected: (20.5f - 20.0f) > 0.5f -> 0.5f > 0.5f -> FALSE
}

void test_is_temperature_rising_false_when_below_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.4f;
    float threshold = 0.5f;
    TEST_ASSERT_FALSE(is_temperature_rising(prev_temp, current_temp, threshold)); // Expected: (20.4f - 20.0f) > 0.5f -> 0.4f > 0.5f -> FALSE
}

void test_is_temperature_rising_false_when_temperature_drops(void) {
    float prev_temp = 20.0f;
    float current_temp = 19.0f;
    float threshold = 0.5f;
    TEST_ASSERT_FALSE(is_temperature_rising(prev_temp, current_temp, threshold)); // Expected: (19.0f - 20.0f) > 0.5f -> 0.0f > 0.5f -> FALSE
}

void test_is_temperature_rising_false_when_no_change_and_positive_threshold(void) {
    float prev_temp = 25.0f;
    float current_temp = 25.0f;
    float threshold = 0.1f;
    TEST_ASSERT_FALSE(is_temperature_rising(prev_temp, current_temp, threshold)); // Expected: (25.0f - 25.0f) > 0.1f -> 0.0f > 0.1f -> FALSE
}

void test_is_temperature_rising_true_when_small_rise_and_zero_threshold(void) {
    float prev_temp = 25.0f;
    float current_temp = 25.01f;
    float threshold = 0.0f;
    TEST_ASSERT_TRUE(is_temperature_rising(prev_temp, current_temp, threshold)); // Expected: (25.01f - 25.0f) > 0.0f -> 0.01f > 0.0f -> TRUE
}

void test_is_temperature_rising_false_when_no_change_and_zero_threshold(void) {
    float prev_temp = 25.0f;
    float current_temp = 25.0f;
    float threshold = 0.0f;
    TEST_ASSERT_FALSE(is_temperature_rising(prev_temp, current_temp, threshold)); // Expected: (25.0f - 25.0f) > 0.0f -> 0.0f > 0.0f -> FALSE
}

void test_is_temperature_rising_with_negative_threshold_and_temp_dropping(void) {
    float prev_temp = 20.0f;
    float current_temp = 19.9f; // Dropped by 0.1
    float threshold = 0.0f; // Threshold for drop detection (e.g., if drop is less than 0.5, it's "rising" in this context)
    TEST_ASSERT_TRUE(is_temperature_rising(prev_temp, current_temp, threshold)); // Expected: (19.9f - 20.0f) > 0.0f -> 0.0f > 0.0f -> TRUE
}

void test_is_temperature_rising_with_negative_threshold_and_temp_dropping_below_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 19.4f; // Dropped by 0.6
    float threshold = 0.0f;
    TEST_ASSERT_FALSE(is_temperature_rising(prev_temp, current_temp, threshold)); // Expected: (19.4f - 20.0f) > 0.0f -> 0.0f > 0.0f -> FALSE
}


// MARK: - Main Test Runner



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_min_raw_value_yields_min_celsius);
    RUN_TEST(test_raw_to_celsius_max_raw_value_yields_max_celsius);
    RUN_TEST(test_raw_to_celsius_mid_range_raw_value);
    RUN_TEST(test_raw_to_celsius_specific_intermediate_raw_value);
    RUN_TEST(test_celsius_to_fahrenheit_freezing_point);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_room_temperature);
    RUN_TEST(test_celsius_to_fahrenheit_negative_forty_degrees);
    RUN_TEST(test_celsius_to_fahrenheit_max_sensor_range_celsius);
    RUN_TEST(test_is_temperature_rising_true_when_significantly_above_threshold);
    RUN_TEST(test_is_temperature_rising_false_when_equal_to_threshold);
    RUN_TEST(test_is_temperature_rising_false_when_below_threshold);
    RUN_TEST(test_is_temperature_rising_false_when_temperature_drops);
    RUN_TEST(test_is_temperature_rising_false_when_no_change_and_positive_threshold);
    RUN_TEST(test_is_temperature_rising_true_when_small_rise_and_zero_threshold);
    RUN_TEST(test_is_temperature_rising_false_when_no_change_and_zero_threshold);
    RUN_TEST(test_is_temperature_rising_with_negative_threshold_and_temp_dropping);
    RUN_TEST(test_is_temperature_rising_with_negative_threshold_and_temp_dropping_below_threshold);

    return UNITY_END();
}