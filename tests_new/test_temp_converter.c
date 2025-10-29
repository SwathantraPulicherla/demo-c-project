#include "unity.h"
#include "temp_converter.h" // Source code header
#include <stdbool.h>        // For bool type
#include <string.h>         // For memset (if stubs were present)

// No stubs are required for the provided source code, so no stub control structs or functions are defined.

void setUp(void) {
    // No stubs to reset, no global state to set up for these pure functions.
}

void tearDown(void) {
    // No stubs to reset, no global state to clean up.
}

// MARK: - raw_to_celsius Tests

void test_raw_to_celsius_min_raw_value(void) {
    // Test with the minimum possible raw ADC value (0)
    int raw_value = 0;
    float expected_celsius = 0.0f; // Expected: (0 / 1023.0f) * 165.0f - 40.0f = 0.0f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, expected_celsius, actual_celsius); // Expected: 0 raw value converts to 0.0f°C
}

void test_raw_to_celsius_max_raw_value(void) {
    // Test with the maximum possible raw ADC value (1023 for 10-bit ADC)
    int raw_value = 1023;
    float expected_celsius = 125.0f; // Expected: (1023 / 1023.0f) * 165.0f - 40.0f = 125.0f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, expected_celsius, actual_celsius); // Expected: 1023 raw value converts to 125.0°C
}

void test_raw_to_celsius_mid_range(void) {
    // Test with a mid-range raw ADC value
    int raw_value = 511; // Approximately half of 1023
    float expected_celsius = (511 / 1023.0f) * 165.0f - 40.0f; // Expected: (0.4995f * 165.0f) - 40.0f = 42.419f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, expected_celsius, actual_celsius); // Expected: Mid-range raw value converts correctly
}

void test_raw_to_celsius_specific_value(void) {
    // Test with another specific raw ADC value corresponding to a valid temperature
    int raw_value = 204;
    float expected_celsius = (204 / 1023.0f) * 165.0f - 40.0f; // Expected: (0.1994f * 165.0f) - 40.0f = 0.0f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, expected_celsius, actual_celsius); // Expected: Specific raw value converts correctly
}

// MARK: - celsius_to_fahrenheit Tests

void test_celsius_to_fahrenheit_freezing_point(void) {
    // Test conversion of water's freezing point
    float temp_c = 0.0f;
    float expected_f = 32.0f; // Expected: (0 * 9/5) + 32 = 32.0f
    float actual_f = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, expected_f, actual_f); // Expected: 0°C converts to 32.0°F
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    // Test conversion of water's boiling point
    float temp_c = 100.0f;
    float expected_f = 212.0f; // Expected: (100 * 9/5) + 32 = 212.0f
    float actual_f = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, expected_f, actual_f); // Expected: 100°C converts to 212.0°F
}

void test_celsius_to_fahrenheit_nominal_temp(void) {
    // Test conversion of a nominal room temperature
    float temp_c = 25.0f;
    float expected_f = 77.0f; // Expected: (25 * 9/5) + 32 = 77.0f
    float actual_f = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, expected_f, actual_f); // Expected: 25°C converts to 77.0°F
}

void test_celsius_to_fahrenheit_min_valid_temp(void) {
    // Test conversion of the minimum valid temperature (0.0f°C)
    float temp_c = 0.0f;
    float expected_f = 0.0f; // Expected: (0.0f * 9/5) + 32 = 0.0f
    float actual_f = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, expected_f, actual_f); // Expected: 0.0f°C converts to 0.0f°F
}

void test_celsius_to_fahrenheit_max_valid_temp(void) {
    // Test conversion of the maximum valid temperature (125°C)
    float temp_c = 125.0f;
    float expected_f = 257.0f; // Expected: (125 * 9/5) + 32 = 257.0f
    float actual_f = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, expected_f, actual_f); // Expected: 125°C converts to 257.0°F
}

// MARK: - is_temperature_rising Tests

void test_is_temperature_rising_above_threshold(void) {
    // Test case where temperature is rising significantly above the threshold
    float prev_temp = 20.0f;
    float current_temp = 25.0f;
    float threshold = 3.0f;
    bool expected_result = true; // Expected: (25.0 - 20.0) > 3.0 -> 5.0 > 3.0 is true
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(actual_result); // Expected: Temperature rise is above threshold
}

void test_is_temperature_rising_below_threshold(void) {
    // Test case where temperature is rising but below the threshold
    float prev_temp = 20.0f;
    float current_temp = 22.0f;
    float threshold = 3.0f;
    bool expected_result = false; // Expected: (22.0 - 20.0) > 3.0 -> 2.0 > 3.0 is false
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(actual_result); // Expected: Temperature rise is not above threshold
}

void test_is_temperature_rising_equal_to_threshold(void) {
    // Test case where temperature difference is exactly equal to the threshold (should be false due to strict greater than)
    float prev_temp = 20.0f;
    float current_temp = 23.0f;
    float threshold = 3.0f;
    bool expected_result = false; // Expected: (23.0 - 20.0) > 3.0 -> 3.0 > 3.0 is false
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(actual_result); // Expected: Temperature rise equal to threshold is not considered 'rising'
}

void test_is_temperature_rising_falling(void) {
    // Test case where temperature is falling
    float prev_temp = 25.0f;
    float current_temp = 20.0f;
    float threshold = 3.0f;
    bool expected_result = false; // Expected: (20.0 - 25.0) > 3.0 -> 0.0f > 3.0 is false
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(actual_result); // Expected: Falling temperature is not considered 'rising'
}

void test_is_temperature_rising_no_change(void) {
    // Test case where temperature has not changed
    float prev_temp = 25.0f;
    float current_temp = 25.0f;
    float threshold = 0.0f; // Even with a zero threshold, it should be false (0 > 0 is false)
    bool expected_result = false; // Expected: (25.0 - 25.0) > 0.0 -> 0.0 > 0.0 is false
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(actual_result); // Expected: No temperature change is not considered 'rising'
}

void test_is_temperature_rising_zero_threshold_slight_increase(void) {
    // Test case with a very small increase and zero threshold
    float prev_temp = 20.0f;
    float current_temp = 20.1f;
    float threshold = 0.0f;
    bool expected_result = true; // Expected: (20.1 - 20.0) > 0.0 -> 0.1 > 0.0 is true
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(actual_result); // Expected: A slight increase with zero threshold is considered 'rising'
}

void test_is_temperature_rising_negative_threshold_temp_falling(void) {
    // Test case with a negative threshold, where temp is falling but still "rising" according to logic
    float prev_temp = 20.0f;
    float current_temp = 19.5f; // Temp decreased by 0.5
    float threshold = 0.0f;    // Threshold is 0.0f
    bool expected_result = true; // Expected: (19.5 - 20.0) > 0.0f -> 0.0f > 0.0f is true
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(actual_result); // Expected: A fall less than the negative threshold still triggers 'rising'
}



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_min_raw_value);
    RUN_TEST(test_raw_to_celsius_max_raw_value);
    RUN_TEST(test_raw_to_celsius_mid_range);
    RUN_TEST(test_raw_to_celsius_specific_value);
    RUN_TEST(test_celsius_to_fahrenheit_freezing_point);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_nominal_temp);
    RUN_TEST(test_celsius_to_fahrenheit_min_valid_temp);
    RUN_TEST(test_celsius_to_fahrenheit_max_valid_temp);
    RUN_TEST(test_is_temperature_rising_above_threshold);
    RUN_TEST(test_is_temperature_rising_below_threshold);
    RUN_TEST(test_is_temperature_rising_equal_to_threshold);
    RUN_TEST(test_is_temperature_rising_falling);
    RUN_TEST(test_is_temperature_rising_no_change);
    RUN_TEST(test_is_temperature_rising_zero_threshold_slight_increase);
    RUN_TEST(test_is_temperature_rising_negative_threshold_temp_falling);

    return UNITY_END();
}