#include "unity.h"
#include "temp_converter.h" // Source code under test
#include <stdbool.h>       // For bool type
#include <stdint.h>        // Not strictly necessary for this source, but good practice

// No stubs are required for this source file as per the prompt.

void setUp(void) {
    // No stubs to reset, no specific setup needed for these pure functions.
}

void tearDown(void) {
    // No stubs to reset, no specific cleanup needed.
}

// --- Test Cases for raw_to_celsius ---

void test_raw_to_celsius_min_raw_value(void) {
    int raw_value = 0;
    float expected_celsius = 0.0f; // Expected: 0 raw value (min ADC) converts to 0.0f°C (min realistic temp)
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_max_raw_value(void) {
    int raw_value = 1023;
    float expected_celsius = 125.0f; // Expected: 1023 raw value (max ADC) converts to 125.0°C (max realistic temp)
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_mid_range(void) {
    int raw_value = 512; // Realistic mid-range 10-bit ADC value
    float expected_celsius = 42.580644f; // Expected: 512 raw value converts to approx 42.58°C based on formula
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_approximates_zero_celsius(void) {
    int raw_value = 248; // ADC value that should approximate 0°C based on formula
    float expected_celsius = 0.0f; // Expected: Raw value 248 converts to approximately 0.0°C
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius); // Using a slightly larger tolerance for approximation
}

// --- Test Cases for celsius_to_fahrenheit ---

void test_celsius_to_fahrenheit_freezing_point(void) {
    float temp_c = 0.0f;
    float expected_fahrenheit = 32.0f; // Expected: 0°C converts to 32°F
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    float temp_c = 100.0f;
    float expected_fahrenheit = 212.0f; // Expected: 100°C converts to 212°F
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_room_temp(void) {
    float temp_c = 25.0f; // A common room temperature in Celsius
    float expected_fahrenheit = 77.0f; // Expected: 25°C converts to 77°F
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_min_realistic_temp(void) {
    float temp_c = 0.0f; // Minimum realistic operational temperature
    float expected_fahrenheit = 0.0f; // Expected: 0.0f°C converts to 0.0f°F
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_max_realistic_temp(void) {
    float temp_c = 125.0f; // Maximum realistic operational temperature
    float expected_fahrenheit = 257.0f; // Expected: 125°C converts to 257°F
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}

// --- Test Cases for is_temperature_rising ---

void test_is_temperature_rising_above_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 25.0f;
    float threshold = 3.0f;
    // Expected: Current temperature increase (5.0f) is greater than the threshold (3.0f)
    TEST_ASSERT_TRUE(is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_below_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 22.0f;
    float threshold = 3.0f;
    // Expected: Current temperature increase (2.0f) is not greater than the threshold (3.0f)
    TEST_ASSERT_FALSE(is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_exactly_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 23.0f;
    float threshold = 3.0f;
    // Expected: Current temperature increase (3.0f) is exactly the threshold, not strictly greater
    TEST_ASSERT_FALSE(is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_not_rising(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.0f;
    float threshold = 3.0f;
    // Expected: No temperature change (0.0f), so not rising above threshold
    TEST_ASSERT_FALSE(is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_falling(void) {
    float prev_temp = 25.0f;
    float current_temp = 20.0f;
    float threshold = 3.0f;
    // Expected: Temperature is decreasing (0.0f), so not rising above threshold
    TEST_ASSERT_FALSE(is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_small_delta_zero_threshold(void) {
    float prev_temp = 25.0f;
    float current_temp = 25.1f;
    float threshold = 0.0f;
    // Expected: A small rise (0.1f) is greater than a zero threshold
    TEST_ASSERT_TRUE(is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_equal_temps_zero_threshold(void) {
    float prev_temp = 25.0f;
    float current_temp = 25.0f;
    float threshold = 0.0f;
    // Expected: No temperature change (0.0f) is not strictly greater than a zero threshold
    TEST_ASSERT_FALSE(is_temperature_rising(prev_temp, current_temp, threshold));
}



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_min_raw_value);
    RUN_TEST(test_raw_to_celsius_max_raw_value);
    RUN_TEST(test_raw_to_celsius_mid_range);
    RUN_TEST(test_raw_to_celsius_approximates_zero_celsius);
    RUN_TEST(test_celsius_to_fahrenheit_freezing_point);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_room_temp);
    RUN_TEST(test_celsius_to_fahrenheit_min_realistic_temp);
    RUN_TEST(test_celsius_to_fahrenheit_max_realistic_temp);
    RUN_TEST(test_is_temperature_rising_above_threshold);
    RUN_TEST(test_is_temperature_rising_below_threshold);
    RUN_TEST(test_is_temperature_rising_exactly_threshold);
    RUN_TEST(test_is_temperature_not_rising);
    RUN_TEST(test_is_temperature_falling);
    RUN_TEST(test_is_temperature_rising_small_delta_zero_threshold);
    RUN_TEST(test_is_temperature_rising_equal_temps_zero_threshold);

    return UNITY_END();
}