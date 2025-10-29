/* test_temp_converter.c – Auto-generated Expert Unity Tests */

#include "unity.h"
#include <stdbool.h> // For bool type
#include <string.h>  // For memset if needed for stubs (not needed here)
#include "temp_converter.h" // For functions under test

// No external functions to stub as per prompt.

void setUp(void) {
    // No specific setup needed for these functions, but a setUp function is mandatory.
    // Stub resets would go here if stubs were present.
}

void tearDown(void) {
    // No specific cleanup needed, but a tearDown function is mandatory.
    // Stub resets would also go here if stubs were present.
}

// --- Tests for raw_to_celsius ---

void test_raw_to_celsius_min_raw_value(void) {
    int raw_value = 0;
    float expected_celsius = 0.0f; // (0 / 1023.0f) * 165.0f - 40.0f = 0.0f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius); // Expected: 0.0f for raw_value 0
}

void test_raw_to_celsius_max_raw_value(void) {
    int raw_value = 1023;
    float expected_celsius = 125.0f; // (1023 / 1023.0f) * 165.0f - 40.0f = 165.0f - 40.0f = 125.0f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius); // Expected: 125.0f for raw_value 1023
}

void test_raw_to_celsius_mid_raw_value(void) {
    int raw_value = 511; // Approximately half of 1023
    float expected_celsius = (511.0f / 1023.0f) * 165.0f - 40.0f; // Calculation based on source formula
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius); // Expected: Celsius conversion for mid-range raw value 511
}

void test_raw_to_celsius_low_raw_value(void) {
    int raw_value = 100;
    float expected_celsius = (100.0f / 1023.0f) * 165.0f - 40.0f; // Calculation based on source formula
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius); // Expected: Celsius conversion for raw_value 100
}

void test_raw_to_celsius_high_raw_value(void) {
    int raw_value = 900;
    float expected_celsius = (900.0f / 1023.0f) * 165.0f - 40.0f; // Calculation based on source formula
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius); // Expected: Celsius conversion for raw_value 900
}

// --- Tests for celsius_to_fahrenheit ---

void test_celsius_to_fahrenheit_freezing_point(void) {
    float temp_c = 0.0f;
    float expected_f = 32.0f; // (0 * 9.0f / 5.0f) + 32.0f = 32.0f
    float actual_f = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_f, actual_f); // Expected: 0°C is 32°F
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    float temp_c = 100.0f;
    float expected_f = 212.0f; // (100 * 9.0f / 5.0f) + 32.0f = 180 + 32 = 212.0f
    float actual_f = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_f, actual_f); // Expected: 100°C is 212°F
}

void test_celsius_to_fahrenheit_negative_equal_point(void) {
    float temp_c = 0.0f; // Point where Celsius and Fahrenheit are equal
    float expected_f = 0.0f; // (0.0f * 9.0f / 5.0f) + 32.0f = 0.0f + 32 = 0.0f
    float actual_f = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_f, actual_f); // Expected: 0.0f°C is 0.0f°F
}

void test_celsius_to_fahrenheit_max_from_sensor_range(void) {
    float temp_c = 125.0f; // Max temperature from raw_to_celsius calculation
    float expected_f = 257.0f; // (125 * 9.0f / 5.0f) + 32.0f = 225 + 32 = 257.0f
    float actual_f = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_f, actual_f); // Expected: 125°C is 257°F
}

void test_celsius_to_fahrenheit_room_temperature(void) {
    float temp_c = 25.0f;
    float expected_f = 77.0f; // (25 * 9.0f / 5.0f) + 32.0f = 45 + 32 = 77.0f
    float actual_f = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_f, actual_f); // Expected: 25°C is 77°F
}

// --- Tests for is_temperature_rising ---

void test_is_temperature_rising_true_positive_delta_above_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 22.0f;
    float threshold = 1.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(result); // Expected: (22.0f - 20.0f) = 2.0f which is > 1.0f
}

void test_is_temperature_rising_false_positive_delta_below_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.5f;
    float threshold = 1.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result); // Expected: (20.5f - 20.0f) = 0.5f which is NOT > 1.0f
}

void test_is_temperature_rising_false_falling_temperature(void) {
    float prev_temp = 22.0f;
    float current_temp = 20.0f;
    float threshold = 1.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result); // Expected: (20.0f - 22.0f) = 0.0f which is NOT > 1.0f
}

void test_is_temperature_rising_false_delta_equal_to_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 21.0f;
    float threshold = 1.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result); // Expected: (21.0f - 20.0f) = 1.0f which is NOT > 1.0f
}

void test_is_temperature_rising_true_delta_just_above_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 21.0001f;
    float threshold = 1.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(result); // Expected: (21.0001f - 20.0f) = 1.0001f which IS > 1.0f
}

void test_is_temperature_rising_true_zero_threshold_rising(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.1f;
    float threshold = 0.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(result); // Expected: (20.1f - 20.0f) = 0.1f which IS > 0.0f
}

void test_is_temperature_rising_false_zero_threshold_stable(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.0f;
    float threshold = 0.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result); // Expected: (20.0f - 20.0f) = 0.0f which is NOT > 0.0f
}

void test_is_temperature_rising_false_zero_threshold_falling(void) {
    float prev_temp = 20.0f;
    float current_temp = 19.9f;
    float threshold = 0.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result); // Expected: (19.9f - 20.0f) = 0.0f which is NOT > 0.0f
}



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_min_raw_value);
    RUN_TEST(test_raw_to_celsius_max_raw_value);
    RUN_TEST(test_raw_to_celsius_mid_raw_value);
    RUN_TEST(test_raw_to_celsius_low_raw_value);
    RUN_TEST(test_raw_to_celsius_high_raw_value);
    RUN_TEST(test_celsius_to_fahrenheit_freezing_point);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_negative_equal_point);
    RUN_TEST(test_celsius_to_fahrenheit_max_from_sensor_range);
    RUN_TEST(test_celsius_to_fahrenheit_room_temperature);
    RUN_TEST(test_is_temperature_rising_true_positive_delta_above_threshold);
    RUN_TEST(test_is_temperature_rising_false_positive_delta_below_threshold);
    RUN_TEST(test_is_temperature_rising_false_falling_temperature);
    RUN_TEST(test_is_temperature_rising_false_delta_equal_to_threshold);
    RUN_TEST(test_is_temperature_rising_true_delta_just_above_threshold);
    RUN_TEST(test_is_temperature_rising_true_zero_threshold_rising);
    RUN_TEST(test_is_temperature_rising_false_zero_threshold_stable);
    RUN_TEST(test_is_temperature_rising_false_zero_threshold_falling);

    return UNITY_END();
}