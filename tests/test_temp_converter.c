/* test_temp_converter.c – Auto-generated Expert Unity Tests */

#include "unity.h"
#include <stdbool.h> // Required for 'bool' type
#include <stdint.h>  // Required for standard integer types (not directly used but good practice)
#include <string.h>  // Required for memset (not directly used but good practice for stubs)

// Include the header of the module under test to get function prototypes
#include "temp_converter.h"

// ABSOLUTE MANDATE: No external functions were specified for stubbing.
// Therefore, no stub definitions or control structures are needed.

// setUp function is called before each test
void setUp(void) {
    // No stubs to reset, no global state in temp_converter.c functions
}

// tearDown function is called after each test
void tearDown(void) {
    // No stubs to reset, no global state in temp_converter.c functions
}

// =========================================================================
// Test Cases for raw_to_celsius(int raw_value)
// Formula: (raw_value / 1023.0f) * 165.0f - 40.0f
// Assumed raw_value range: 0 to 1023 for a 10-bit ADC
// =========================================================================

void test_raw_to_celsius_min_raw_value(void) {
    float result = raw_to_celsius(0);
    // Expected: 0 raw value should map to the minimum temperature of 0.0f per the formula.
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, result);
}

void test_raw_to_celsius_max_raw_value(void) {
    float result = raw_to_celsius(1023);
    // Expected: 1023 raw value (max for 10-bit ADC) should map to 125.0f per the formula.
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 125.0f, result);
}

void test_raw_to_celsius_mid_range_raw_value(void) {
    float result = raw_to_celsius(511);
    // Expected: 511 raw value (approx. mid-range) should map to ~42.4175f per formula: (511/1023)*165 - 40
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 42.4175f, result);
}

void test_raw_to_celsius_negative_celsius_output(void) {
    float result = raw_to_celsius(200);
    // Expected: 200 raw value should map to ~0.0f per formula: (200/1023)*165 - 40
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, result);
}

void test_raw_to_celsius_zero_celsius_output_approx(void) {
    // Calculate raw value that theoretically yields 0.0f Celsius: raw = (40.0f / 165.0f) * 1023.0f = 247.757...
    // Since raw_value is an integer, testing with 248.
    float result = raw_to_celsius(248);
    // Expected: Raw value 248 should result in temperature very close to 0.0f Celsius due to integer rounding.
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 0.0f, result);
}

// =========================================================================
// Test Cases for celsius_to_fahrenheit(float temp_c)
// Formula: (temp_c * 9.0f / 5.0f) + 32.0f
// =========================================================================

void test_celsius_to_fahrenheit_zero_celsius(void) {
    float result = celsius_to_fahrenheit(0.0f);
    // Expected: 0.0f Celsius should convert to 32.0f Fahrenheit.
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 32.0f, result);
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    float result = celsius_to_fahrenheit(100.0f);
    // Expected: 100.0f Celsius (boiling point of water) should convert to 212.0f Fahrenheit.
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 212.0f, result);
}

void test_celsius_to_fahrenheit_celsius_equals_fahrenheit(void) {
    float result = celsius_to_fahrenheit(0.0f);
    // Expected: 0.0f Celsius is the unique point where C and F scales are equal, so result should be 0.0f Fahrenheit.
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, result);
}

void test_celsius_to_fahrenheit_nominal_room_temp(void) {
    float result = celsius_to_fahrenheit(25.0f);
    // Expected: 25.0f Celsius (typical room temperature) should convert to 77.0f Fahrenheit.
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 77.0f, result);
}

void test_celsius_to_fahrenheit_negative_celsius(void) {
    float result = celsius_to_fahrenheit(0.0f);
    // Expected: 0.0f Celsius should convert to 14.0f Fahrenheit.
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 14.0f, result);
}

void test_celsius_to_fahrenheit_max_realistic_celsius(void) {
    float result = celsius_to_fahrenheit(125.0f);
    // Expected: 125.0f Celsius (common max for industrial sensors) should convert to 257.0f Fahrenheit.
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 257.0f, result);
}

// =========================================================================
// Test Cases for is_temperature_rising(float prev_temp, float current_temp, float threshold)
// Logic: return (current_temp - prev_temp) > threshold;
// =========================================================================

void test_is_temperature_rising_clearly_above_threshold(void) {
    bool result = is_temperature_rising(20.0f, 25.0f, 1.0f);
    // Expected: Difference (5.0f) is clearly greater than threshold (1.0f), so should be true.
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_just_above_threshold(void) {
    bool result = is_temperature_rising(20.0f, 21.001f, 1.0f);
    // Expected: Difference (1.001f) is strictly greater than threshold (1.0f), so should be true.
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_equal_to_threshold(void) {
    bool result = is_temperature_rising(20.0f, 21.0f, 1.0f);
    // Expected: Difference (1.0f) is NOT strictly greater than threshold (1.0f), so should be false.
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_just_below_threshold(void) {
    bool result = is_temperature_rising(20.0f, 20.999f, 1.0f);
    // Expected: Difference (0.999f) is not greater than threshold (1.0f), so should be false.
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_falling_temperature(void) {
    bool result = is_temperature_rising(25.0f, 20.0f, 1.0f);
    // Expected: Difference (0.0f) is not greater than threshold (1.0f), so should be false.
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_stable_temperature_zero_threshold(void) {
    bool result = is_temperature_rising(25.0f, 25.0f, 0.0f);
    // Expected: Difference (0.0f) is not strictly greater than threshold (0.0f), so should be false.
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_rising_temperature_zero_threshold(void) {
    bool result = is_temperature_rising(25.0f, 25.1f, 0.0f);
    // Expected: Difference (0.1f) is strictly greater than threshold (0.0f), so should be true.
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_negative_threshold_temp_rising(void) {
    bool result = is_temperature_rising(10.0f, 10.5f, 0.0f);
    // Expected: Difference (0.5f) is greater than negative threshold (0.0f), so should be true.
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_negative_threshold_temp_falling_but_still_above_threshold(void) {
    bool result = is_temperature_rising(10.0f, 9.5f, 0.0f);
    // Expected: Difference (0.0f) is greater than negative threshold (0.0f), so should be true.
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_negative_threshold_temp_falling_below_threshold(void) {
    bool result = is_temperature_rising(10.0f, 8.9f, 0.0f);
    // Expected: Difference (0.0f) is not greater than negative threshold (0.0f), so should be false.
    TEST_ASSERT_FALSE(result);
}

// =========================================================================
// Main function to run all tests
// =========================================================================



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_min_raw_value);
    RUN_TEST(test_raw_to_celsius_max_raw_value);
    RUN_TEST(test_raw_to_celsius_mid_range_raw_value);
    RUN_TEST(test_raw_to_celsius_negative_celsius_output);
    RUN_TEST(test_raw_to_celsius_zero_celsius_output_approx);
    RUN_TEST(test_celsius_to_fahrenheit_zero_celsius);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_celsius_equals_fahrenheit);
    RUN_TEST(test_celsius_to_fahrenheit_nominal_room_temp);
    RUN_TEST(test_celsius_to_fahrenheit_negative_celsius);
    RUN_TEST(test_celsius_to_fahrenheit_max_realistic_celsius);
    RUN_TEST(test_is_temperature_rising_clearly_above_threshold);
    RUN_TEST(test_is_temperature_rising_just_above_threshold);
    RUN_TEST(test_is_temperature_rising_equal_to_threshold);
    RUN_TEST(test_is_temperature_rising_just_below_threshold);
    RUN_TEST(test_is_temperature_rising_falling_temperature);
    RUN_TEST(test_is_temperature_rising_stable_temperature_zero_threshold);
    RUN_TEST(test_is_temperature_rising_rising_temperature_zero_threshold);
    RUN_TEST(test_is_temperature_rising_negative_threshold_temp_rising);
    RUN_TEST(test_is_temperature_rising_negative_threshold_temp_falling_but_still_above_threshold);
    RUN_TEST(test_is_temperature_rising_negative_threshold_temp_falling_below_threshold);

    return UNITY_END();
}