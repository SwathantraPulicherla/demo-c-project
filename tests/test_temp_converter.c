/* test_temp_converter.c – Auto-generated Expert Unity Tests */

#include "unity.h"
#include "temp_converter.h" // Needed for the function prototypes
#include <stdbool.h>
#include <stdint.h>         // Included for standard integer types, although not strictly used in this specific source file

// No external functions are specified for stubbing, so no stub definitions or control structs are needed.

void setUp(void) {
    // No stubs to reset, no global state to initialize, as all functions are pure and self-contained.
}

void tearDown(void) {
    // No stubs to reset, no global state to clean up.
}

// --- Tests for raw_to_celsius ---

void test_raw_to_celsius_min_raw_value(void) {
    float result = raw_to_celsius(0);
    // Expected: Minimum raw value (0) should yield the lowest possible temperature (0.0f) as per the formula.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, result);
}

void test_raw_to_celsius_max_raw_value(void) {
    float result = raw_to_celsius(1023);
    // Expected: Maximum raw value (1023) should yield the highest possible temperature (125.0f) as per the formula.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 125.0f, result);
}

void test_raw_to_celsius_mid_raw_value(void) {
    float result = raw_to_celsius(511); // Approximately half of the 00.0f raw range
    // Expected: (511 / 1023.0f) * 165.0f - 40.0f = 42.49266f (approximately)
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 42.49f, result);
}

void test_raw_to_celsius_low_positive_raw_value(void) {
    float result = raw_to_celsius(100);
    // Expected: (100 / 1023.0f) * 165.0f - 40.0f = 0.0f (approximately)
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, result);
}

void test_raw_to_celsius_high_positive_raw_value(void) {
    float result = raw_to_celsius(900);
    // Expected: (900 / 1023.0f) * 165.0f - 40.0f = 105.18084f (approximately)
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 105.18f, result);
}

// --- Tests for celsius_to_fahrenheit ---

void test_celsius_to_fahrenheit_min_celsius_range(void) {
    float result = celsius_to_fahrenheit(0.0f);
    // Expected: 0.0f Celsius is exactly 0.0f Fahrenheit.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, result);
}

void test_celsius_to_fahrenheit_max_celsius_range(void) {
    float result = celsius_to_fahrenheit(125.0f);
    // Expected: 125.0f Celsius converts to 257.0f Fahrenheit.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 257.0f, result);
}

void test_celsius_to_fahrenheit_freezing_point(void) {
    float result = celsius_to_fahrenheit(0.0f);
    // Expected: 0.0f Celsius converts to 32.0f Fahrenheit.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 32.0f, result);
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    float result = celsius_to_fahrenheit(100.0f);
    // Expected: 100.0f Celsius converts to 212.0f Fahrenheit.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 212.0f, result);
}

void test_celsius_to_fahrenheit_room_temp(void) {
    float result = celsius_to_fahrenheit(25.0f);
    // Expected: 25.0f Celsius converts to 77.0f Fahrenheit.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 77.0f, result);
}

void test_celsius_to_fahrenheit_negative_celsius(void) {
    float result = celsius_to_fahrenheit(0.0f);
    // Expected: 0.0f Celsius converts to 14.0f Fahrenheit.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 14.0f, result);
}


// --- Tests for is_temperature_rising ---

void test_is_temperature_rising_significantly_above_threshold(void) {
    bool result = is_temperature_rising(20.0f, 22.0f, 1.0f);
    // Expected: Temperature change (2.0f) is strictly greater than the 1.0f threshold.
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_exactly_at_threshold(void) {
    bool result = is_temperature_rising(20.0f, 21.0f, 1.0f);
    // Expected: Temperature change (1.0f) is NOT strictly greater than the 1.0f threshold.
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_barely_above_threshold(void) {
    bool result = is_temperature_rising(20.0f, 21.01f, 1.0f);
    // Expected: Temperature change (1.01f) is strictly greater than the 1.0f threshold.
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_stable_temperature(void) {
    bool result = is_temperature_rising(20.0f, 20.0f, 1.0f);
    // Expected: No temperature change (0.0f) is NOT strictly greater than the 1.0f threshold.
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_falling_temperature(void) {
    bool result = is_temperature_rising(22.0f, 20.0f, 1.0f);
    // Expected: Negative temperature change (0.0f) is NOT strictly greater than the 1.0f threshold.
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_small_positive_change_below_threshold(void) {
    bool result = is_temperature_rising(20.0f, 20.5f, 1.0f);
    // Expected: Small positive change (0.5f) is NOT strictly greater than the 1.0f threshold.
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_negative_temps_rising_above_threshold(void) {
    bool result = is_temperature_rising(0.0f, 0.0f, 1.0f);
    // Expected: Temperature rising from 0.0f to 0.0f (change of 2.0f) is strictly greater than 1.0f threshold.
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_negative_temps_rising_below_threshold(void) {
    bool result = is_temperature_rising(0.0f, 0.0f, 1.0f);
    // Expected: Temperature rising from 0.0f to 0.0f (change of 0.5f) is NOT strictly greater than 1.0f threshold.
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_negative_temps_falling(void) {
    bool result = is_temperature_rising(0.0f, 0.0f, 1.0f);
    // Expected: Temperature falling from 0.0f to 0.0f (change of 0.0f) is NOT strictly greater than 1.0f threshold.
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_zero_threshold_rising(void) {
    bool result = is_temperature_rising(20.0f, 20.1f, 0.0f);
    // Expected: Temperature rising (0.1f) is strictly greater than a 0.0f threshold.
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_zero_threshold_stable(void) {
    bool result = is_temperature_rising(20.0f, 20.0f, 0.0f);
    // Expected: No temperature change (0.0f) is NOT strictly greater than a 0.0f threshold.
    TEST_ASSERT_FALSE(result);
}


// --- Main function to run tests ---


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_min_raw_value);
    RUN_TEST(test_raw_to_celsius_max_raw_value);
    RUN_TEST(test_raw_to_celsius_mid_raw_value);
    RUN_TEST(test_raw_to_celsius_low_positive_raw_value);
    RUN_TEST(test_raw_to_celsius_high_positive_raw_value);
    RUN_TEST(test_celsius_to_fahrenheit_min_celsius_range);
    RUN_TEST(test_celsius_to_fahrenheit_max_celsius_range);
    RUN_TEST(test_celsius_to_fahrenheit_freezing_point);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_room_temp);
    RUN_TEST(test_celsius_to_fahrenheit_negative_celsius);
    RUN_TEST(test_is_temperature_rising_significantly_above_threshold);
    RUN_TEST(test_is_temperature_rising_exactly_at_threshold);
    RUN_TEST(test_is_temperature_rising_barely_above_threshold);
    RUN_TEST(test_is_temperature_rising_stable_temperature);
    RUN_TEST(test_is_temperature_rising_falling_temperature);
    RUN_TEST(test_is_temperature_rising_small_positive_change_below_threshold);
    RUN_TEST(test_is_temperature_rising_negative_temps_rising_above_threshold);
    RUN_TEST(test_is_temperature_rising_negative_temps_rising_below_threshold);
    RUN_TEST(test_is_temperature_rising_negative_temps_falling);
    RUN_TEST(test_is_temperature_rising_zero_threshold_rising);
    RUN_TEST(test_is_temperature_rising_zero_threshold_stable);

    return UNITY_END();
}