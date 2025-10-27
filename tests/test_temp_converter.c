#include "unity.h"
#include "temp_converter.h" // Include the header for the module under test
#include <stdbool.h>

// No functions need stubs, so no stub definitions here.

// setUp function called before each test
void setUp(void) {
    // No stubs to reset.
}

// tearDown function called after each test
void tearDown(void) {
    // No stubs to reset.
}

// Test for raw_to_celsius at minimum raw value
void test_raw_to_celsius_min_raw(void) {
    int raw_value = 0;
    float expected_celsius = (0 / 1023.0f) * 165.0f - 40.0f; // Approx -40.0f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

// Test for raw_to_celsius at maximum raw value
void test_raw_to_celsius_max_raw(void) {
    int raw_value = 1023;
    float expected_celsius = (1023 / 1023.0f) * 165.0f - 40.0f; // 165.0f - 40.0f = 125.0f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

// Test for raw_to_celsius at mid-range raw value
void test_raw_to_celsius_mid_range(void) {
    int raw_value = 511; // Approximately half of 1023
    float expected_celsius = (511 / 1023.0f) * 165.0f - 40.0f; // Approx 42.1f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

// Test for raw_to_celsius with a value that should result in 0 Celsius
void test_raw_to_celsius_zero_celsius_output(void) {
    // 0 = (raw / 1023.0) * 165.0 - 40.0
    // 40.0 = (raw / 1023.0) * 165.0
    // raw = (40.0 * 1023.0) / 165.0 = 247.99... approx 248
    int raw_value = 248; 
    float expected_celsius = 0.0f;
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

// Test for celsius_to_fahrenheit with 0 Celsius
void test_celsius_to_fahrenheit_zero_celsius(void) {
    float temp_c = 0.0f;
    float expected_fahrenheit = 32.0f; // (0 * 9/5) + 32 = 32
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}

// Test for celsius_to_fahrenheit with 100 Celsius (boiling point)
void test_celsius_to_fahrenheit_boiling_point(void) {
    float temp_c = 100.0f;
    float expected_fahrenheit = 212.0f; // (100 * 9/5) + 32 = 180 + 32 = 212
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}

// Test for celsius_to_fahrenheit with -40 Celsius (same as Fahrenheit)
void test_celsius_to_fahrenheit_negative_40(void) {
    float temp_c = -40.0f;
    float expected_fahrenheit = -40.0f; // (-40 * 9/5) + 32 = -72 + 32 = -40
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}

// Test for is_temperature_rising when temperature is clearly rising above threshold
void test_is_temperature_rising_true_above_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 25.0f;
    float threshold = 3.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(result);
}

// Test for is_temperature_rising when temperature is rising but below threshold
void test_is_temperature_rising_false_below_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 22.0f;
    float threshold = 3.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result);
}

// Test for is_temperature_rising when temperature is exactly at threshold
void test_is_temperature_rising_false_at_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 23.0f;
    float threshold = 3.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result); // (current - prev) > threshold is false
}

// Test for is_temperature_rising when temperature is decreasing
void test_is_temperature_rising_false_decreasing(void) {
    float prev_temp = 25.0f;
    float current_temp = 20.0f;
    float threshold = 3.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result);
}

// Test for is_temperature_rising when temperature is constant
void test_is_temperature_rising_false_constant(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.0f;
    float threshold = 0.0f; // Even with 0 threshold, it needs to be > 0
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result);
}

// Test for is_temperature_rising with negative threshold
void test_is_temperature_rising_negative_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 21.0f;
    float threshold = -1.0f; // current_temp - prev_temp = 1.0; 1.0 > -1.0 is true
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(result);
}

// Test for is_temperature_rising with negative temperatures, rising
void test_is_temperature_rising_negative_temps_rising(void) {
    float prev_temp = -10.0f;
    float current_temp = -5.0f;
    float threshold = 3.0f; // -5 - (-10) = 5.0; 5.0 > 3.0 is true
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(result);
}

// Test for is_temperature_rising with negative temperatures, not rising
void test_is_temperature_rising_negative_temps_not_rising(void) {
    float prev_temp = -5.0f;
    float current_temp = -10.0f;
    float threshold = 3.0f; // -10 - (-5) = -5.0; -5.0 > 3.0 is false
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result);
}

// Main function for running tests


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_min_raw);
    RUN_TEST(test_raw_to_celsius_max_raw);
    RUN_TEST(test_raw_to_celsius_mid_range);
    RUN_TEST(test_raw_to_celsius_zero_celsius_output);
    RUN_TEST(test_celsius_to_fahrenheit_zero_celsius);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_negative_40);
    RUN_TEST(test_is_temperature_rising_true_above_threshold);
    RUN_TEST(test_is_temperature_rising_false_below_threshold);
    RUN_TEST(test_is_temperature_rising_false_at_threshold);
    RUN_TEST(test_is_temperature_rising_false_decreasing);
    RUN_TEST(test_is_temperature_rising_false_constant);
    RUN_TEST(test_is_temperature_rising_negative_threshold);
    RUN_TEST(test_is_temperature_rising_negative_temps_rising);
    RUN_TEST(test_is_temperature_rising_negative_temps_not_rising);

    return UNITY_END();
}