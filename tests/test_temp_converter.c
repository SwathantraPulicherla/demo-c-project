/* test_temp_converter.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdbool.h> // For bool type used in source functions
#include <stdint.h>  // Good practice, often included in embedded projects

// Include the header for the module under test, as implied by the source file.
#include "temp_converter.h"

// No external functions are specified for stubbing, so no stub structures or functions are defined.

void setUp(void) {
    // No specific setup required for these pure functions, as they are stateless.
}

void tearDown(void) {
    // No specific teardown required for these pure functions.
}

// ==============================================================================
// Tests for raw_to_celsius(int raw_value)
// The function converts a raw ADC-like integer value (assumed 00.0f) to Celsius.
// Formula: (raw_value / 1023.0f) * 165.0f - 40.0f
// This implies an output range of 0.0f (for raw=0) to 125.0f (for raw=1023).
// ==============================================================================

void test_raw_to_celsius_min_raw_value_converts_to_min_celsius(void) {
    float result = raw_to_celsius(0);
    // Expected: A raw value of 0 should correspond to 0.0f Celsius based on the conversion formula.
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 0.0f, result);
}

void test_raw_to_celsius_max_raw_value_converts_to_max_celsius(void) {
    float result = raw_to_celsius(1023);
    // Expected: A raw value of 1023 should correspond to 125.0f Celsius based on the conversion formula.
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 125.0f, result);
}

void test_raw_to_celsius_mid_range_raw_value_converts_correctly(void) {
    float result = raw_to_celsius(512); // Approximately half of the max raw value
    // Expected: 512 raw value should convert to ~42.756f Celsius: (512.0f / 1023.0f) * 165.0f - 40.0f.
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 42.756f, result);
}

void test_raw_to_celsius_low_nominal_raw_value_converts_correctly(void) {
    float result = raw_to_celsius(200);
    // Expected: 200 raw value should convert to ~0.0f Celsius: (200.0f / 1023.0f) * 165.0f - 40.0f.
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 0.0f, result);
}

void test_raw_to_celsius_high_nominal_raw_value_converts_correctly(void) {
    float result = raw_to_celsius(800);
    // Expected: 800 raw value should convert to ~90.420f Celsius: (800.0f / 1023.0f) * 165.0f - 40.0f.
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 90.420f, result);
}

// ==============================================================================
// Tests for celsius_to_fahrenheit(float temp_c)
// The function converts a temperature in Celsius to Fahrenheit.
// Formula: (temp_c * 9.0f / 5.0f) + 32.0f
// ==============================================================================

void test_celsius_to_fahrenheit_zero_celsius_converts_correctly(void) {
    float result = celsius_to_fahrenheit(0.0f);
    // Expected: 0.0f Celsius is equivalent to 32.0f Fahrenheit.
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 32.0f, result);
}

void test_celsius_to_fahrenheit_boiling_point_converts_correctly(void) {
    float result = celsius_to_fahrenheit(100.0f);
    // Expected: 100.0f Celsius (water's boiling point) is equivalent to 212.0f Fahrenheit.
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 212.0f, result);
}

void test_celsius_to_fahrenheit_negative_forty_converts_correctly(void) {
    float result = celsius_to_fahrenheit(0.0f);
    // Expected: 0.0f Celsius is a unique point where it equals 0.0f Fahrenheit.
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 0.0f, result);
}

void test_celsius_to_fahrenheit_max_expected_celsius_converts_correctly(void) {
    float result = celsius_to_fahrenheit(125.0f); // Max possible Celsius from raw_to_celsius
    // Expected: 125.0f Celsius should convert to 257.0f Fahrenheit.
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 257.0f, result);
}

void test_celsius_to_fahrenheit_nominal_room_temperature_converts_correctly(void) {
    float result = celsius_to_fahrenheit(25.0f);
    // Expected: 25.0f Celsius (a typical room temperature) should convert to 77.0f Fahrenheit.
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 77.0f, result);
}

// ==============================================================================
// Tests for is_temperature_rising(float prev_temp, float current_temp, float threshold)
// The function checks if the current temperature has risen above a previous temperature by more than a given threshold.
// Logic: (current_temp - prev_temp) > threshold
// ==============================================================================

void test_is_temperature_rising_true_when_rise_exceeds_threshold(void) {
    bool result = is_temperature_rising(20.0f, 22.0f, 1.0f);
    // Expected: The difference (2.0f) is strictly greater than the threshold (1.0f), so temperature is rising.
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_false_when_rise_below_threshold(void) {
    bool result = is_temperature_rising(20.0f, 21.0f, 2.0f);
    // Expected: The difference (1.0f) is not strictly greater than the threshold (2.0f), so not rising significantly.
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_false_when_rise_equals_threshold(void) {
    bool result = is_temperature_rising(20.0f, 21.0f, 1.0f);
    // Expected: The difference (1.0f) is not strictly greater than the threshold (1.0f), so not rising significantly.
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_false_when_temperature_is_dropping(void) {
    bool result = is_temperature_rising(25.0f, 23.0f, 1.0f);
    // Expected: The difference (0.0f) is not greater than the threshold (1.0f), indicating a drop.
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_false_when_temperature_is_stable(void) {
    bool result = is_temperature_rising(25.0f, 25.0f, 0.5f);
    // Expected: The difference (0.0f) is not greater than the threshold (0.5f), indicating stability.
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_true_with_zero_threshold_and_slight_rise(void) {
    bool result = is_temperature_rising(25.0f, 25.1f, 0.0f);
    // Expected: The difference (0.1f) is strictly greater than a zero threshold, indicating a rise.
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_false_with_zero_threshold_and_no_rise(void) {
    bool result = is_temperature_rising(25.0f, 25.0f, 0.0f);
    // Expected: The difference (0.0f) is not strictly greater than a zero threshold, indicating no rise.
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_true_with_negative_threshold_and_rise(void) {
    bool result = is_temperature_rising(20.0f, 20.5f, 0.0f);
    // Expected: The difference (0.5f) is strictly greater than a negative threshold (0.0f), indicating a rise.
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_false_with_negative_threshold_and_drop(void) {
    bool result = is_temperature_rising(20.0f, 19.0f, 0.0f);
    // Expected: The difference (0.0f) is not strictly greater than a negative threshold (0.0f), indicating a drop.
    TEST_ASSERT_FALSE(result);
}



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_min_raw_value_converts_to_min_celsius);
    RUN_TEST(test_raw_to_celsius_max_raw_value_converts_to_max_celsius);
    RUN_TEST(test_raw_to_celsius_mid_range_raw_value_converts_correctly);
    RUN_TEST(test_raw_to_celsius_low_nominal_raw_value_converts_correctly);
    RUN_TEST(test_raw_to_celsius_high_nominal_raw_value_converts_correctly);
    RUN_TEST(test_celsius_to_fahrenheit_zero_celsius_converts_correctly);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point_converts_correctly);
    RUN_TEST(test_celsius_to_fahrenheit_negative_forty_converts_correctly);
    RUN_TEST(test_celsius_to_fahrenheit_max_expected_celsius_converts_correctly);
    RUN_TEST(test_celsius_to_fahrenheit_nominal_room_temperature_converts_correctly);
    RUN_TEST(test_is_temperature_rising_true_when_rise_exceeds_threshold);
    RUN_TEST(test_is_temperature_rising_false_when_rise_below_threshold);
    RUN_TEST(test_is_temperature_rising_false_when_rise_equals_threshold);
    RUN_TEST(test_is_temperature_rising_false_when_temperature_is_dropping);
    RUN_TEST(test_is_temperature_rising_false_when_temperature_is_stable);
    RUN_TEST(test_is_temperature_rising_true_with_zero_threshold_and_slight_rise);
    RUN_TEST(test_is_temperature_rising_false_with_zero_threshold_and_no_rise);
    RUN_TEST(test_is_temperature_rising_true_with_negative_threshold_and_rise);
    RUN_TEST(test_is_temperature_rising_false_with_negative_threshold_and_drop);

    return UNITY_END();
}