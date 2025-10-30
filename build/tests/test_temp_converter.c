/* test_temp_converter.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h> // Only if memset or similar is used for stubs, not strictly needed here

// Include the header for the source file under test to get function prototypes
#include "temp_converter.h"

// No external functions to stub for this module based on the prompt.

void setUp(void) {
    // No stubs to reset or global state to initialize for this module
}

void tearDown(void) {
    // No stubs to reset or global state to clean up for this module
}

// ==============================================================================
// Tests for raw_to_celsius(int raw_value)
// Expected conversion: (raw_value / 1023.0f) * 165.0f - 40.0f
// Expected range for raw_value 00.0f is Celsius 0.0f to 125.0f
// ==============================================================================

void test_raw_to_celsius_min_raw_value(void) {
    int raw_value = 0;
    float expected_celsius = 0.0f; // (0 / 1023.0f) * 165.0f - 40.0f = 0.0f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius); // Assert exact minimum temperature for minimum raw value
}

void test_raw_to_celsius_max_raw_value(void) {
    int raw_value = 1023;
    float expected_celsius = 125.0f; // (1023 / 1023.0f) * 165.0f - 40.0f = 125.0f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius); // Assert exact maximum temperature for maximum raw value
}

void test_raw_to_celsius_mid_range_raw_value(void) {
    int raw_value = 511; // Approximately half of 1023
    float expected_celsius = (511.0f / 1023.0f) * 165.0f - 40.0f; // Calculate expected value based on source formula
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius); // Assert correct conversion for a mid-range raw value
}

void test_raw_to_celsius_quarter_range_raw_value(void) {
    int raw_value = 256; // Approximately quarter of 1023
    float expected_celsius = (256.0f / 1023.0f) * 165.0f - 40.0f; // Calculate expected value based on source formula
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius); // Assert correct conversion for a quarter-range raw value
}

void test_raw_to_celsius_three_quarter_range_raw_value(void) {
    int raw_value = 768; // Approximately three-quarters of 1023
    float expected_celsius = (768.0f / 1023.0f) * 165.0f - 40.0f; // Calculate expected value based on source formula
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius); // Assert correct conversion for a three-quarter-range raw value
}

// ==============================================================================
// Tests for celsius_to_fahrenheit(float temp_c)
// Expected conversion: (temp_c * 9.0f / 5.0f) + 32.0f
// ==============================================================================

void test_celsius_to_fahrenheit_freezing_point(void) {
    float temp_c = 0.0f;
    float expected_f = 32.0f; // 0 C is 32 F
    float actual_f = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_f, actual_f); // Assert correct conversion for freezing point
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    float temp_c = 100.0f;
    float expected_f = 212.0f; // 100 C is 212 F
    float actual_f = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_f, actual_f); // Assert correct conversion for boiling point
}

void test_celsius_to_fahrenheit_room_temperature(void) {
    float temp_c = 25.0f;
    float expected_f = (25.0f * 9.0f / 5.0f) + 32.0f; // 25 C is 77 F
    float actual_f = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_f, actual_f); // Assert correct conversion for typical room temperature
}

void test_celsius_to_fahrenheit_negative_celsius(void) {
    float temp_c = 0.0f;
    float expected_f = (0.0f * 9.0f / 5.0f) + 32.0f; // 0.0f C is 14 F
    float actual_f = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_f, actual_f); // Assert correct conversion for a negative Celsius value
}

void test_celsius_to_fahrenheit_min_valid_celsius_from_raw(void) {
    float temp_c = 0.0f;
    float expected_f = (0.0f * 9.0f / 5.0f) + 32.0f; // 0.0f C is 0.0f F, a critical edge case
    float actual_f = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_f, actual_f); // Assert correct conversion for the lowest possible Celsius temperature
}

void test_celsius_to_fahrenheit_max_valid_celsius_from_raw(void) {
    float temp_c = 125.0f;
    float expected_f = (125.0f * 9.0f / 5.0f) + 32.0f; // 125 C is 257 F
    float actual_f = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_f, actual_f); // Assert correct conversion for the highest possible Celsius temperature
}

// ==============================================================================
// Tests for is_temperature_rising(float prev_temp, float current_temp, float threshold)
// Expected logic: (current_temp - prev_temp) > threshold
// ==============================================================================

void test_is_temperature_rising_true_significantly_rising(void) {
    float prev_temp = 20.0f;
    float current_temp = 25.0f;
    float threshold = 2.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(result); // Expected true because (25.0f - 20.0f) = 5.0f, which is > 2.0f
}

void test_is_temperature_rising_true_slightly_above_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 22.1f;
    float threshold = 2.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(result); // Expected true because (22.1f - 20.0f) = 2.1f, which is > 2.0f
}

void test_is_temperature_rising_false_exactly_at_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 22.0f;
    float threshold = 2.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result); // Expected false because (22.0f - 20.0f) = 2.0f, which is NOT > 2.0f
}

void test_is_temperature_rising_false_below_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 21.0f;
    float threshold = 2.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result); // Expected false because (21.0f - 20.0f) = 1.0f, which is NOT > 2.0f
}

void test_is_temperature_rising_false_falling_temperature(void) {
    float prev_temp = 25.0f;
    float current_temp = 20.0f;
    float threshold = 2.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result); // Expected false because (20.0f - 25.0f) = 0.0f, which is NOT > 2.0f
}

void test_is_temperature_rising_false_stable_temperature(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.0f;
    float threshold = 0.1f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result); // Expected false because (20.0f - 20.0f) = 0.0f, which is NOT > 0.1f
}

void test_is_temperature_rising_true_with_negative_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 21.0f;
    float threshold = 0.0f; // A negative threshold means even a small increase is "rising"
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(result); // Expected true because (21.0f - 20.0f) = 1.0f, which is > 0.0f
}

void test_is_temperature_rising_false_falling_with_negative_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 19.0f;
    float threshold = 0.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result); // Expected false because (19.0f - 20.0f) = 0.0f, which is NOT > 0.0f
}

// ==============================================================================
// Unity Test Runner
// ==============================================================================



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_min_raw_value);
    RUN_TEST(test_raw_to_celsius_max_raw_value);
    RUN_TEST(test_raw_to_celsius_mid_range_raw_value);
    RUN_TEST(test_raw_to_celsius_quarter_range_raw_value);
    RUN_TEST(test_raw_to_celsius_three_quarter_range_raw_value);
    RUN_TEST(test_celsius_to_fahrenheit_freezing_point);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_room_temperature);
    RUN_TEST(test_celsius_to_fahrenheit_negative_celsius);
    RUN_TEST(test_celsius_to_fahrenheit_min_valid_celsius_from_raw);
    RUN_TEST(test_celsius_to_fahrenheit_max_valid_celsius_from_raw);
    RUN_TEST(test_is_temperature_rising_true_significantly_rising);
    RUN_TEST(test_is_temperature_rising_true_slightly_above_threshold);
    RUN_TEST(test_is_temperature_rising_false_exactly_at_threshold);
    RUN_TEST(test_is_temperature_rising_false_below_threshold);
    RUN_TEST(test_is_temperature_rising_false_falling_temperature);
    RUN_TEST(test_is_temperature_rising_false_stable_temperature);
    RUN_TEST(test_is_temperature_rising_true_with_negative_threshold);
    RUN_TEST(test_is_temperature_rising_false_falling_with_negative_threshold);

    return UNITY_END();
}