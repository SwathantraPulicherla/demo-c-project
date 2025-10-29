/* test_temp_converter.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdbool.h> // Required for 'bool' type
#include <string.h>  // Required for memset, though not used here as there are no stubs
#include "temp_converter.h" // Required to get function prototypes for the SUT

// Define a suitable tolerance for floating-point comparisons
#define TEMPERATURE_TOLERANCE 0.1f

// No external functions to stub, so no stub control structs needed.

void setUp(void) {
    // No global state or stubs to initialize/reset for these pure functions.
}

void tearDown(void) {
    // No global state or stubs to clean up.
}

/**
 * @brief Test case for raw_to_celsius with minimum raw ADC value.
 * @details Verifies the conversion of the minimum raw value (0) to Celsius.
 *          Expected: 0.0f C, based on (0 / 1023.0f) * 165.0f - 40.0f.
 */
void test_raw_to_celsius_min_raw(void) {
    int raw_value = 0;
    float expected_celsius = 0.0f;
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: 0.0f is the minimum temperature for raw_value = 0
    TEST_ASSERT_FLOAT_WITHIN(TEMPERATURE_TOLERANCE, expected_celsius, actual_celsius);
}

/**
 * @brief Test case for raw_to_celsius with maximum raw ADC value.
 * @details Verifies the conversion of the maximum raw value (1023) to Celsius.
 *          Expected: 125.0f C, based on (1023 / 1023.0f) * 165.0f - 40.0f.
 */
void test_raw_to_celsius_max_raw(void) {
    int raw_value = 1023;
    float expected_celsius = 125.0f;
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: 125.0f is the maximum temperature for raw_value = 1023
    TEST_ASSERT_FLOAT_WITHIN(TEMPERATURE_TOLERANCE, expected_celsius, actual_celsius);
}

/**
 * @brief Test case for raw_to_celsius with a mid-range raw ADC value.
 * @details Verifies the conversion of a typical mid-range raw value (512) to Celsius.
 *          Expected: 42.61f C, based on (512 / 1023.0f) * 165.0f - 40.0f.
 */
void test_raw_to_celsius_mid_range_raw(void) {
    int raw_value = 512;
    float expected_celsius = (512.0f / 1023.0f) * 165.0f - 40.0f; // Approx 42.61f
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: A calculated value for a mid-range raw input
    TEST_ASSERT_FLOAT_WITHIN(TEMPERATURE_TOLERANCE, expected_celsius, actual_celsius);
}

/**
 * @brief Test case for raw_to_celsius with a common room temperature raw value.
 * @details Verifies the conversion of a raw value that should result in roughly 25.0C.
 *          Calculated: raw = (25.0f + 40.0f) / 165.0f * 1023.0f = 405.0f.
 */
void test_raw_to_celsius_room_temp_raw(void) {
    int raw_value = 405; // Corresponds roughly to 25.0C
    float expected_celsius = 25.0f;
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: Approximately 25.0f C for a raw input of 405
    TEST_ASSERT_FLOAT_WITHIN(TEMPERATURE_TOLERANCE, expected_celsius, actual_celsius);
}

/**
 * @brief Test case for celsius_to_fahrenheit at the freezing point.
 * @details Verifies 0.0f Celsius converts to 32.0f Fahrenheit.
 *          Expected: (0.0f * 9.0f / 5.0f) + 32.0f = 32.0f.
 */
void test_celsius_to_fahrenheit_freezing_point(void) {
    float temp_c = 0.0f;
    float expected_f = 32.0f;
    float actual_f = celsius_to_fahrenheit(temp_c);
    // Expected: 32.0f F is the freezing point equivalent of 0.0f C
    TEST_ASSERT_FLOAT_WITHIN(TEMPERATURE_TOLERANCE, expected_f, actual_f);
}

/**
 * @brief Test case for celsius_to_fahrenheit at the boiling point.
 * @details Verifies 100.0f Celsius converts to 212.0f Fahrenheit.
 *          Expected: (100.0f * 9.0f / 5.0f) + 32.0f = 212.0f.
 */
void test_celsius_to_fahrenheit_boiling_point(void) {
    float temp_c = 100.0f;
    float expected_f = 212.0f;
    float actual_f = celsius_to_fahrenheit(temp_c);
    // Expected: 212.0f F is the boiling point equivalent of 100.0f C
    TEST_ASSERT_FLOAT_WITHIN(TEMPERATURE_TOLERANCE, expected_f, actual_f);
}

/**
 * @brief Test case for celsius_to_fahrenheit with a negative temperature.
 * @details Verifies 0.0f Celsius converts to 0.0f Fahrenheit.
 *          Expected: (0.0f * 9.0f / 5.0f) + 32.0f = 0.0f + 32.0f = 0.0f.
 */
void test_celsius_to_fahrenheit_negative_temp(void) {
    float temp_c = 0.0f;
    float expected_f = 0.0f;
    float actual_f = celsius_to_fahrenheit(temp_c);
    // Expected: 0.0f F is the equivalent of 0.0f C
    TEST_ASSERT_FLOAT_WITHIN(TEMPERATURE_TOLERANCE, expected_f, actual_f);
}

/**
 * @brief Test case for celsius_to_fahrenheit with a positive room temperature.
 * @details Verifies 25.0f Celsius converts to 77.0f Fahrenheit.
 *          Expected: (25.0f * 9.0f / 5.0f) + 32.0f = 45.0f + 32.0f = 77.0f.
 */
void test_celsius_to_fahrenheit_room_temp(void) {
    float temp_c = 25.0f;
    float expected_f = 77.0f;
    float actual_f = celsius_to_fahrenheit(temp_c);
    // Expected: 77.0f F is the equivalent of 25.0f C
    TEST_ASSERT_FLOAT_WITHIN(TEMPERATURE_TOLERANCE, expected_f, actual_f);
}

/**
 * @brief Test case for is_temperature_rising when temperature is clearly rising.
 * @details Verifies that a significant increase above threshold returns true.
 *          Expected: (25.0f - 20.0f) > 3.0f  => 5.0f > 3.0f => true.
 */
void test_is_temperature_rising_true_positive(void) {
    float prev_temp = 20.0f;
    float current_temp = 25.0f;
    float threshold = 3.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: true, because the temperature increased significantly more than the threshold
    TEST_ASSERT_TRUE(result);
}

/**
 * @brief Test case for is_temperature_rising when temperature is not rising sufficiently.
 * @details Verifies that an increase below threshold returns false.
 *          Expected: (22.0f - 20.0f) > 3.0f  => 2.0f > 3.0f => false.
 */
void test_is_temperature_rising_false_negative_insufficient_rise(void) {
    float prev_temp = 20.0f;
    float current_temp = 22.0f;
    float threshold = 3.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: false, because the temperature rise is less than the threshold
    TEST_ASSERT_FALSE(result);
}

/**
 * @brief Test case for is_temperature_rising when temperature is exactly at threshold.
 * @details Verifies that an increase exactly equal to threshold returns false (strict greater than).
 *          Expected: (23.0f - 20.0f) > 3.0f  => 3.0f > 3.0f => false.
 */
void test_is_temperature_rising_false_negative_exact_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 23.0f;
    float threshold = 3.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: false, because the temperature rise is exactly equal to the threshold (not strictly greater)
    TEST_ASSERT_FALSE(result);
}

/**
 * @brief Test case for is_temperature_rising when temperature is falling.
 * @details Verifies that a falling temperature returns false.
 *          Expected: (15.0f - 20.0f) > 3.0f  => 0.0f > 3.0f => false.
 */
void test_is_temperature_rising_false_negative_falling_temp(void) {
    float prev_temp = 20.0f;
    float current_temp = 15.0f;
    float threshold = 3.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: false, because the temperature is falling
    TEST_ASSERT_FALSE(result);
}

/**
 * @brief Test case for is_temperature_rising with zero difference and zero threshold.
 * @details Verifies behavior when both difference and threshold are zero.
 *          Expected: (20.0f - 20.0f) > 0.0f  => 0.0f > 0.0f => false.
 */
void test_is_temperature_rising_zero_difference_zero_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.0f;
    float threshold = 0.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: false, because 0 is not strictly greater than 0
    TEST_ASSERT_FALSE(result);
}

/**
 * @brief Test case for is_temperature_rising with a very small rise, just above threshold.
 * @details Checks for floating point precision around the threshold boundary.
 *          Expected: (20.0f + 0.001f - 20.0f) > 0.0f => 0.001f > 0.0f => true.
 */
void test_is_temperature_rising_true_positive_tiny_rise(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.0f + 0.001f;
    float threshold = 0.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: true, as a tiny rise is strictly greater than a zero threshold
    TEST_ASSERT_TRUE(result);
}



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_min_raw);
    RUN_TEST(test_raw_to_celsius_max_raw);
    RUN_TEST(test_raw_to_celsius_mid_range_raw);
    RUN_TEST(test_raw_to_celsius_room_temp_raw);
    RUN_TEST(test_celsius_to_fahrenheit_freezing_point);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_negative_temp);
    RUN_TEST(test_celsius_to_fahrenheit_room_temp);
    RUN_TEST(test_is_temperature_rising_true_positive);
    RUN_TEST(test_is_temperature_rising_false_negative_insufficient_rise);
    RUN_TEST(test_is_temperature_rising_false_negative_exact_threshold);
    RUN_TEST(test_is_temperature_rising_false_negative_falling_temp);
    RUN_TEST(test_is_temperature_rising_zero_difference_zero_threshold);
    RUN_TEST(test_is_temperature_rising_true_positive_tiny_rise);

    return UNITY_END();
}