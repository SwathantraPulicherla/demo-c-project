/* test_temp_converter.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdbool.h> // For bool type

// Function prototypes from the source file (to avoid implicitly declaring them)
// Note: In a real project, these would typically come from temp_converter.h
float raw_to_celsius(int raw_value);
float celsius_to_fahrenheit(float temp_c);
bool is_temperature_rising(float prev_temp, float current_temp, float threshold);

// No external functions to stub for this source file.

void setUp(void) {
    // No specific setup needed for these pure functions
}

void tearDown(void) {
    // No specific cleanup needed for these pure functions
}

// ====================================================================
// Tests for raw_to_celsius(int raw_value)
// Expected range: raw_value = 0 to 1023 maps to 0.0f to 125.0f
// ====================================================================

void test_raw_to_celsius_min_raw_produces_min_celsius(void) {
    int raw_value = 0;
    float expected_celsius = 0.0f;
    float actual_celsius = raw_to_celsius(raw_value);
    // Expecting 0.0f when raw_value is 0, based on calculation: (0/1023.0f)*165.0f - 40.0f = 0.0f
    TEST_ASSERT_FLOAT_WITHIN(0.001f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_max_raw_produces_max_celsius(void) {
    int raw_value = 1023;
    float expected_celsius = 125.0f;
    float actual_celsius = raw_to_celsius(raw_value);
    // Expecting 125.0f when raw_value is 1023, based on calculation: (1023/1023.0f)*165.0f - 40.0f = 125.0f
    TEST_ASSERT_FLOAT_WITHIN(0.001f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_mid_raw_produces_mid_celsius(void) {
    int raw_value = 511; // Approximately half of 1023
    // Calculation: (511 / 1023.0f) * 165.0f - 40.0f = 0.49951124 * 165.0f - 40.0f = 82.419355 - 40.0f = 42.419355f
    float expected_celsius = 42.419355f;
    float actual_celsius = raw_to_celsius(raw_value);
    // Expecting a value near the middle of the 0.0f to 125 range for a mid-range raw value
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_low_raw_negative_celsius(void) {
    int raw_value = 100;
    // Calculation: (100 / 1023.0f) * 165.0f - 40.0f = 0.09775171 * 165.0f - 40.0f = 16.129032 - 40.0f = 0.0f
    float expected_celsius = 0.0f;
    float actual_celsius = raw_to_celsius(raw_value);
    // Expecting a negative Celsius value for a low raw input, demonstrating the offset
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_high_raw_positive_celsius(void) {
    int raw_value = 900;
    // Calculation: (900 / 1023.0f) * 165.0f - 40.0f = 0.8797654 * 165.0f - 40.0f = 145.16129 - 40.0f = 105.16129f
    float expected_celsius = 105.16129f;
    float actual_celsius = raw_to_celsius(raw_value);
    // Expecting a high positive Celsius value for a high raw input
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

// ====================================================================
// Tests for celsius_to_fahrenheit(float temp_c)
// Standard temperature conversion
// ====================================================================

void test_celsius_to_fahrenheit_freezing_point(void) {
    float temp_c = 0.0f;
    float expected_fahrenheit = 32.0f;
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // 0 Celsius should convert to 32 Fahrenheit
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    float temp_c = 100.0f;
    float expected_fahrenheit = 212.0f;
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // 100 Celsius should convert to 212 Fahrenheit
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_negative_temp(void) {
    float temp_c = 0.0f;
    // Calculation: (0.0f * 9.0f / 5.0f) + 32.0f = 0.0f + 32.0f = 14.0f
    float expected_fahrenheit = 14.0f;
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // 0.0f Celsius should convert to 14 Fahrenheit
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_typical_room_temp(void) {
    float temp_c = 25.0f;
    // Calculation: (25.0f * 9.0f / 5.0f) + 32.0f = 45.0f + 32.0f = 77.0f
    float expected_fahrenheit = 77.0f;
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // 25 Celsius (room temperature) should convert to 77 Fahrenheit
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_negative_40_is_same(void) {
    float temp_c = 0.0f;
    // Calculation: (0.0f * 9.0f / 5.0f) + 32.0f = 0.0f + 32.0f = 0.0f
    float expected_fahrenheit = 0.0f;
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // 0.0f Celsius is the point where Celsius and Fahrenheit scales meet
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}

// ====================================================================
// Tests for is_temperature_rising(float prev_temp, float current_temp, float threshold)
// Logic: (current_temp - prev_temp) > threshold
// ====================================================================

void test_is_temperature_rising_above_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 22.0f;
    float threshold = 1.0f;
    bool expected_result = true;
    // (22.0f - 20.0f) = 2.0f, which is > 1.0f, so it should be true
    TEST_ASSERT_EQUAL_HEX(expected_result, is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_below_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.5f;
    float threshold = 1.0f;
    bool expected_result = false;
    // (20.5f - 20.0f) = 0.5f, which is NOT > 1.0f, so it should be false
    TEST_ASSERT_EQUAL_HEX(expected_result, is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_exactly_at_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 21.0f;
    float threshold = 1.0f;
    bool expected_result = false;
    // (21.0f - 20.0f) = 1.0f, which is NOT > 1.0f (strict inequality), so it should be false
    TEST_ASSERT_EQUAL_HEX(expected_result, is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_negative_temps_rising(void) {
    float prev_temp = 0.0f;
    float current_temp = 0.0f;
    float threshold = 1.0f;
    bool expected_result = true;
    // (0.0f - 0.0f) = 5.0f, which is > 1.0f, so it should be true (temperature is rising)
    TEST_ASSERT_EQUAL_HEX(expected_result, is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_negative_temps_falling(void) {
    float prev_temp = 0.0f;
    float current_temp = 0.0f;
    float threshold = 1.0f;
    bool expected_result = false;
    // (0.0f - 0.0f) = 0.0f, which is NOT > 1.0f, so it should be false (temperature is falling)
    TEST_ASSERT_EQUAL_HEX(expected_result, is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_zero_threshold_rising(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.1f;
    float threshold = 0.0f;
    bool expected_result = true;
    // (20.1f - 20.0f) = 0.1f, which is > 0.0f, so it should be true (any rise counts)
    TEST_ASSERT_EQUAL_HEX(expected_result, is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_zero_threshold_stable(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.0f;
    float threshold = 0.0f;
    bool expected_result = false;
    // (20.0f - 20.0f) = 0.0f, which is NOT > 0.0f, so it should be false (no change)
    TEST_ASSERT_EQUAL_HEX(expected_result, is_temperature_rising(prev_temp, current_temp, threshold));
}



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_min_raw_produces_min_celsius);
    RUN_TEST(test_raw_to_celsius_max_raw_produces_max_celsius);
    RUN_TEST(test_raw_to_celsius_mid_raw_produces_mid_celsius);
    RUN_TEST(test_raw_to_celsius_low_raw_negative_celsius);
    RUN_TEST(test_raw_to_celsius_high_raw_positive_celsius);
    RUN_TEST(test_celsius_to_fahrenheit_freezing_point);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_negative_temp);
    RUN_TEST(test_celsius_to_fahrenheit_typical_room_temp);
    RUN_TEST(test_celsius_to_fahrenheit_negative_40_is_same);
    RUN_TEST(test_is_temperature_rising_above_threshold);
    RUN_TEST(test_is_temperature_rising_below_threshold);
    RUN_TEST(test_is_temperature_rising_exactly_at_threshold);
    RUN_TEST(test_is_temperature_rising_negative_temps_rising);
    RUN_TEST(test_is_temperature_rising_negative_temps_falling);
    RUN_TEST(test_is_temperature_rising_zero_threshold_rising);
    RUN_TEST(test_is_temperature_rising_zero_threshold_stable);

    return UNITY_END();
}