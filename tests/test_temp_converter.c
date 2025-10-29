/* test_temp_converter.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include "temp_converter.h" // Includes declarations for the functions under test
#include <stdbool.h>        // For bool type
#include <string.h>         // Not strictly needed here, but good practice for embedded if memset/strcpy were used.

// No external functions to stub, as per prompt.

void setUp(void) {
    // No stubs to reset, no global state to initialize.
}

void tearDown(void) {
    // No stubs to reset, no global state to clean up.
}

// ==============================================================================
// Tests for raw_to_celsius(int raw_value)
// Formula: (raw_value / 1023.0f) * 165.0f - 40.0f
// Implied ADC range 00.0f
// Implied Celsius range: 0.0f to 125.0f
// ==============================================================================

void test_raw_to_celsius_min_raw_value(void) {
    int raw_value = 0;
    float expected_celsius = 0.0f;
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: Raw value 0 should map to the minimum temperature 0.0f0C
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_max_raw_value(void) {
    int raw_value = 1023;
    float expected_celsius = 125.0f; // (1023.0/1023.0)*165.0 - 40.0 = 125.0
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: Raw value 1023 should map to the maximum temperature 125.0C
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_mid_raw_value(void) {
    int raw_value = 512;
    float expected_celsius = (512.0f / 1023.0f) * 165.0f - 40.0f; // Approx 42.66C
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: Mid-range raw value should convert correctly based on formula
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_ambient_raw_value(void) {
    // Calculate raw value for a common ambient temp like 25.0C
    // 25.0 = (raw/1023.0)*165.0 - 40.0  => 65.0 = (raw/1023.0)*165.0 => raw = (65.0 * 1023.0) / 165.0 = 402.0
    int raw_value = 402;
    float expected_celsius = 25.0f;
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: Raw value corresponding to 25.0C should return 25.0C
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_low_raw_value_just_above_min(void) {
    int raw_value = 1;
    float expected_celsius = (1.0f / 1023.0f) * 165.0f - 40.0f; // Approx 0.0f83C
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: Raw value 1 should produce a Celsius value slightly above minimum
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

// ==============================================================================
// Tests for celsius_to_fahrenheit(float temp_c)
// Formula: (temp_c * 9.0f / 5.0f) + 32.0f
// Input C range based on raw_to_celsius: 0.0f to 125.0f
// ==============================================================================

void test_celsius_to_fahrenheit_min_celsius(void) {
    float temp_c = 0.0f;
    float expected_fahrenheit = 0.0f; // -40C is -40F
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // Expected: 0.0f0C should convert to 0.0f0F
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_max_celsius(void) {
    float temp_c = 125.0f;
    float expected_fahrenheit = (125.0f * 9.0f / 5.0f) + 32.0f; // 257.0F
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // Expected: 125.0C should convert to 257.0F
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_freezing_point(void) {
    float temp_c = 0.0f;
    float expected_fahrenheit = 32.0f;
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // Expected: 0.0C (freezing point) should convert to 32.0F
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    float temp_c = 100.0f;
    float expected_fahrenheit = 212.0f;
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // Expected: 100.0C (boiling point) should convert to 212.0F
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_room_temp(void) {
    float temp_c = 25.0f;
    float expected_fahrenheit = (25.0f * 9.0f / 5.0f) + 32.0f; // 77.0F
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // Expected: 25.0C (typical room temperature) should convert to 77.0F
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_negative_temp_above_min(void) {
    float temp_c = 0.0f;
    float expected_fahrenheit = (0.0f * 9.0f / 5.0f) + 32.0f; // 14.0F
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // Expected: 0.0f0C should convert to 14.0F
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit);
}

// ==============================================================================
// Tests for is_temperature_rising(float prev_temp, float current_temp, float threshold)
// Formula: (current_temp - prev_temp) > threshold
// ==============================================================================

void test_is_temperature_rising_above_threshold(void) {
    float prev_temp = 25.0f;
    float current_temp = 26.0f;
    float threshold = 0.5f;
    bool expected_result = true; // (26.0 - 25.0) = 1.0; 1.0 > 0.5 is true
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: Temperature difference is significantly above threshold, so it's rising
    TEST_ASSERT_TRUE(actual_result);
}

void test_is_temperature_rising_at_threshold(void) {
    float prev_temp = 25.0f;
    float current_temp = 25.5f;
    float threshold = 0.5f;
    bool expected_result = false; // (25.5 - 25.0) = 0.5; 0.5 > 0.5 is false (not strictly greater)
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: Temperature difference is exactly at threshold, not strictly greater, so it's not rising (according to > operator)
    TEST_ASSERT_FALSE(actual_result);
}

void test_is_temperature_rising_below_threshold(void) {
    float prev_temp = 25.0f;
    float current_temp = 25.4f;
    float threshold = 0.5f;
    bool expected_result = false; // (25.4 - 25.0) = 0.4; 0.4 > 0.5 is false
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: Temperature difference is below threshold, so it's not rising
    TEST_ASSERT_FALSE(actual_result);
}

void test_is_temperature_rising_decreasing_temp(void) {
    float prev_temp = 26.0f;
    float current_temp = 25.0f;
    float threshold = 0.5f;
    bool expected_result = false; // (25.0 - 26.0) = 0.0f; 0.0f > 0.5 is false
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: Temperature is decreasing, so it's not rising
    TEST_ASSERT_FALSE(actual_result);
}

void test_is_temperature_rising_stable_temp(void) {
    float prev_temp = 25.0f;
    float current_temp = 25.0f;
    float threshold = 0.5f;
    bool expected_result = false; // (25.0 - 25.0) = 0.0; 0.0 > 0.5 is false
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: Temperature is stable (no change), so it's not rising
    TEST_ASSERT_FALSE(actual_result);
}

void test_is_temperature_rising_zero_threshold_rising(void) {
    float prev_temp = 25.0f;
    float current_temp = 25.1f;
    float threshold = 0.0f;
    bool expected_result = true; // (25.1 - 25.0) = 0.1; 0.1 > 0.0 is true
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: Any positive change should trigger true when threshold is 0.0f
    TEST_ASSERT_TRUE(actual_result);
}

void test_is_temperature_rising_zero_threshold_stable(void) {
    float prev_temp = 25.0f;
    float current_temp = 25.0f;
    float threshold = 0.0f;
    bool expected_result = false; // (25.0 - 25.0) = 0.0; 0.0 > 0.0 is false
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: No change should be false when threshold is 0.0f due to strict greater than
    TEST_ASSERT_FALSE(actual_result);
}

void test_is_temperature_rising_negative_threshold_rising(void) {
    float prev_temp = 25.0f;
    float current_temp = 25.1f;
    float threshold = 0.0f; // A change > 0.0f (i.e., 0.0f, 0.0, 0.1, etc.) implies rising
    bool expected_result = true; // (25.1 - 25.0) = 0.1; 0.1 > 0.0f is true
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: A small positive change is greater than a negative threshold
    TEST_ASSERT_TRUE(actual_result);
}

void test_is_temperature_rising_negative_threshold_decreasing_but_still_above(void) {
    float prev_temp = 25.0f;
    float current_temp = 24.8f;
    float threshold = 0.0f; // temp dropped by 0.2, but 0.2 > 0.0f
    bool expected_result = true; // (24.8 - 25.0) = 0.0f; 0.0f > 0.0f is true
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: Even a slight decrease might still be considered "rising" if the threshold is sufficiently negative.
    // This tests the strict inequality logic with negative thresholds.
    TEST_ASSERT_TRUE(actual_result);
}



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_min_raw_value);
    RUN_TEST(test_raw_to_celsius_max_raw_value);
    RUN_TEST(test_raw_to_celsius_mid_raw_value);
    RUN_TEST(test_raw_to_celsius_ambient_raw_value);
    RUN_TEST(test_raw_to_celsius_low_raw_value_just_above_min);
    RUN_TEST(test_celsius_to_fahrenheit_min_celsius);
    RUN_TEST(test_celsius_to_fahrenheit_max_celsius);
    RUN_TEST(test_celsius_to_fahrenheit_freezing_point);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_room_temp);
    RUN_TEST(test_celsius_to_fahrenheit_negative_temp_above_min);
    RUN_TEST(test_is_temperature_rising_above_threshold);
    RUN_TEST(test_is_temperature_rising_at_threshold);
    RUN_TEST(test_is_temperature_rising_below_threshold);
    RUN_TEST(test_is_temperature_rising_decreasing_temp);
    RUN_TEST(test_is_temperature_rising_stable_temp);
    RUN_TEST(test_is_temperature_rising_zero_threshold_rising);
    RUN_TEST(test_is_temperature_rising_zero_threshold_stable);
    RUN_TEST(test_is_temperature_rising_negative_threshold_rising);
    RUN_TEST(test_is_temperature_rising_negative_threshold_decreasing_but_still_above);

    return UNITY_END();
}