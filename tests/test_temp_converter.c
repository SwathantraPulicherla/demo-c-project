/* test_temp_converter.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdbool.h> // For bool type
#include <string.h>  // Not strictly needed but good practice for embedded headers sometimes

// Include the header for the module under test
// This is necessary to get function prototypes and types for compilation
#include "temp_converter.h"

// No external functions to stub, so no stub structures or functions are defined.

// setUp function - called before each test
void setUp(void) {
    // No stubs to reset, no global state to initialize for this simple module.
    // If there were stubs, they would be reset here using memset.
}

// tearDown function - called after each test
void tearDown(void) {
    // No stubs to reset, no global state to clean up.
    // If there were stubs, they would be reset here using memset.
}

// === Tests for raw_to_celsius function ===

void test_raw_to_celsius_min_raw_value(void) {
    int raw_value = 0;
    float expected_celsius = 0.0f; // Calculation: (0 / 1023.0f) * 165.0f - 40.0f = 0.0f
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: Minimum raw value (0) should map to the minimum temperature (0.0f C)
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_max_raw_value(void) {
    int raw_value = 1023;
    float expected_celsius = 125.0f; // Calculation: (1023 / 1023.0f) * 165.0f - 40.0f = 165.0f - 40.0f = 125.0f
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: Maximum raw value (1023) should map to the maximum temperature (125.0f C)
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_mid_range_raw_value(void) {
    int raw_value = 511; // Approximately half of 1023
    float expected_celsius = (511.0f / 1023.0f) * 165.0f - 40.0f; // Calculate based on formula
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: Mid-range raw value (511) should map to its calculated Celsius equivalent
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_quarter_range_raw_value(void) {
    int raw_value = 255; // Approx 1/4 of 1023
    float expected_celsius = (255.0f / 1023.0f) * 165.0f - 40.0f;
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: Quarter-range raw value (255) should map to its calculated Celsius equivalent
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_three_quarter_range_raw_value(void) {
    int raw_value = 767; // Approx 3/4 of 1023
    float expected_celsius = (767.0f / 1023.0f) * 165.0f - 40.0f;
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: Three-quarter-range raw value (767) should map to its calculated Celsius equivalent
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

// === Tests for celsius_to_fahrenheit function ===

void test_celsius_to_fahrenheit_freezing_point(void) {
    float temp_c = 0.0f;
    float expected_fahrenheit = 32.0f; // Calculation: (0.0f * 9.0f / 5.0f) + 32.0f = 32.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // Expected: 0.0 C (freezing point) should convert to 32.0 F
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    float temp_c = 100.0f;
    float expected_fahrenheit = 212.0f; // Calculation: (100.0f * 9.0f / 5.0f) + 32.0f = 180.0f + 32.0f = 212.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // Expected: 100.0 C (boiling point) should convert to 212.0 F
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_negative_forty(void) {
    float temp_c = 0.0f;
    float expected_fahrenheit = 0.0f; // Calculation: (0.0f * 9.0f / 5.0f) + 32.0f = 0.0f + 32.0f = 0.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // Expected: 0.0f C should convert to 0.0f F (the point where both scales are equal)
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_max_celsius(void) {
    float temp_c = 125.0f; // Max temperature from raw_to_celsius output
    float expected_fahrenheit = 257.0f; // Calculation: (125.0f * 9.0f / 5.0f) + 32.0f = 225.0f + 32.0f = 257.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // Expected: 125.0 C should convert to 257.0 F
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_nominal_room_temp(void) {
    float temp_c = 25.0f;
    float expected_fahrenheit = 77.0f; // Calculation: (25.0f * 9.0f / 5.0f) + 32.0f = 45.0f + 32.0f = 77.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // Expected: 25.0 C (nominal room temperature) should convert to 77.0 F
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_negative_cold_temp(void) {
    float temp_c = 0.0f;
    float expected_fahrenheit = 14.0f; // Calculation: (0.0f * 9.0f / 5.0f) + 32.0f = 0.0f + 32.0f = 14.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // Expected: 0.0f C should convert to 14.0 F
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}

// === Tests for is_temperature_rising function ===

void test_is_temperature_rising_true_above_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 22.5f;
    float threshold = 2.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: Current temp increased by more than the threshold (2.5f > 2.0f), so TRUE
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_false_below_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 21.5f;
    float threshold = 2.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: Current temp increased but not by more than threshold (1.5f <= 2.0f), so FALSE
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_false_at_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 22.0f;
    float threshold = 2.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: Current temp increased exactly by threshold (2.0f not > 2.0f), so FALSE
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_false_stable_temp(void) {
    float prev_temp = 25.0f;
    float current_temp = 25.0f;
    float threshold = 0.5f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: Temperature is stable (0.0f not > 0.5f), so FALSE
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_false_falling_temp(void) {
    float prev_temp = 30.0f;
    float current_temp = 28.0f;
    float threshold = 1.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: Temperature is falling (0.0f not > 1.0f), so FALSE
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_zero_threshold_rising(void) {
    float prev_temp = 10.0f;
    float current_temp = 10.1f;
    float threshold = 0.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: Temperature increased even slightly (0.1f > 0.0f), so TRUE
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_zero_threshold_stable_or_falling(void) {
    float prev_temp = 10.0f;
    float current_temp = 10.0f; // or 9.9f
    float threshold = 0.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: Temperature is not strictly rising (0.0f not > 0.0f), so FALSE
    TEST_ASSERT_FALSE(result);
}

// main function to run all tests


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_min_raw_value);
    RUN_TEST(test_raw_to_celsius_max_raw_value);
    RUN_TEST(test_raw_to_celsius_mid_range_raw_value);
    RUN_TEST(test_raw_to_celsius_quarter_range_raw_value);
    RUN_TEST(test_raw_to_celsius_three_quarter_range_raw_value);
    RUN_TEST(test_celsius_to_fahrenheit_freezing_point);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_negative_forty);
    RUN_TEST(test_celsius_to_fahrenheit_max_celsius);
    RUN_TEST(test_celsius_to_fahrenheit_nominal_room_temp);
    RUN_TEST(test_celsius_to_fahrenheit_negative_cold_temp);
    RUN_TEST(test_is_temperature_rising_true_above_threshold);
    RUN_TEST(test_is_temperature_rising_false_below_threshold);
    RUN_TEST(test_is_temperature_rising_false_at_threshold);
    RUN_TEST(test_is_temperature_rising_false_stable_temp);
    RUN_TEST(test_is_temperature_rising_false_falling_temp);
    RUN_TEST(test_is_temperature_rising_zero_threshold_rising);
    RUN_TEST(test_is_temperature_rising_zero_threshold_stable_or_falling);

    return UNITY_END();
}