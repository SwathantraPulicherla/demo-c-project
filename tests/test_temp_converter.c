/* test_temp_converter.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdbool.h> // For bool type
#include <string.h>  // Not strictly needed, but common for memset in setUp/tearDown if stubs were present

// Include the header for the module under test
// Note: "temp_converter.h" is implied by the source, but if the test file were
// in a different directory or the build system required it, it would be included here.
// For this scenario, assuming `temp_converter.h` is globally available or in the same dir.
// Since the prompt instructs to ONLY use existing headers from source, and temp_converter.c
// includes temp_converter.h, it's appropriate to include it here for function prototypes.
#include "temp_converter.h"

// No external functions to stub for this module, as per analysis.

void setUp(void) {
    // No stubs to reset, no global state in this module.
}

void tearDown(void) {
    // No stubs to reset, no global state in this module.
}

// ====================================================================
// Test cases for raw_to_celsius(int raw_value)
// Logic: (raw_value / 1023.0f) * 165.0f - 40.0f
// Input range for raw_value: 0 to 1023 (assuming 10-bit ADC)
// Output range for temp_c: 0.0f to 125.0f
// ====================================================================

void test_raw_to_celsius_min_raw_value(void) {
    float expected_celsius = 0.0f; // Expected: raw_value = 0 should result in 0.0f C
    float actual_celsius = raw_to_celsius(0);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_max_raw_value(void) {
    float expected_celsius = 125.0f; // Expected: raw_value = 1023 should result in 125.0f C
    float actual_celsius = raw_to_celsius(1023);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_mid_raw_value(void) {
    float expected_celsius = 42.590f; // Expected: raw_value = 511 -> (511/1023.0)*165.0 - 40.0 = 42.59 C
    float actual_celsius = raw_to_celsius(511);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_quarter_raw_value(void) {
    float expected_celsius = 1.095f; // Expected: raw_value = 255 -> (255/1023.0)*165.0 - 40.0 = 1.095 C
    float actual_celsius = raw_to_celsius(255);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_three_quarter_raw_value(void) {
    float expected_celsius = 84.085f; // Expected: raw_value = 767 -> (767/1023.0)*165.0 - 40.0 = 84.085 C
    float actual_celsius = raw_to_celsius(767);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

// ====================================================================
// Test cases for celsius_to_fahrenheit(float temp_c)
// Logic: (temp_c * 9.0f / 5.0f) + 32.0f
// Input range for temp_c: Realistic Celsius, derived from raw_to_celsius (0.0f to 125.0f)
// ====================================================================

void test_celsius_to_fahrenheit_freezing_point(void) {
    float expected_fahrenheit = 32.0f; // Expected: 0.0f C is 32.0f F
    float actual_fahrenheit = celsius_to_fahrenheit(0.0f);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    float expected_fahrenheit = 212.0f; // Expected: 100.0f C is 212.0f F
    float actual_fahrenheit = celsius_to_fahrenheit(100.0f);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_negative_celsius_equal_f(void) {
    float expected_fahrenheit = 0.0f; // Expected: 0.0f C is 0.0f F
    float actual_fahrenheit = celsius_to_fahrenheit(0.0f);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_room_temperature(void) {
    float expected_fahrenheit = 77.0f; // Expected: 25.0f C is 77.0f F
    float actual_fahrenheit = celsius_to_fahrenheit(25.0f);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_max_celsius(void) {
    float expected_fahrenheit = 257.0f; // Expected: 125.0f C is 257.0f F
    float actual_fahrenheit = celsius_to_fahrenheit(125.0f);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit);
}

// ====================================================================
// Test cases for is_temperature_rising(float prev_temp, float current_temp, float threshold)
// Logic: (current_temp - prev_temp) > threshold
// ====================================================================

void test_is_temperature_rising_above_threshold(void) {
    bool actual_result = is_temperature_rising(20.0f, 22.0f, 1.0f); // Expected: (22.0 - 20.0) = 2.0, which is > 1.0f, so TRUE
    TEST_ASSERT_TRUE(actual_result);
}

void test_is_temperature_rising_equal_to_threshold(void) {
    bool actual_result = is_temperature_rising(20.0f, 21.0f, 1.0f); // Expected: (21.0 - 20.0) = 1.0, which is NOT > 1.0f, so FALSE
    TEST_ASSERT_FALSE(actual_result);
}

void test_is_temperature_rising_below_threshold(void) {
    bool actual_result = is_temperature_rising(20.0f, 20.5f, 1.0f); // Expected: (20.5 - 20.0) = 0.5, which is NOT > 1.0f, so FALSE
    TEST_ASSERT_FALSE(actual_result);
}

void test_is_temperature_rising_decreasing_temperature(void) {
    bool actual_result = is_temperature_rising(22.0f, 20.0f, 1.0f); // Expected: (20.0 - 22.0) = 0.0f, which is NOT > 1.0f, so FALSE
    TEST_ASSERT_FALSE(actual_result);
}

void test_is_temperature_rising_zero_threshold_rising(void) {
    bool actual_result = is_temperature_rising(20.0f, 20.1f, 0.0f); // Expected: (20.1 - 20.0) = 0.1, which IS > 0.0f, so TRUE
    TEST_ASSERT_TRUE(actual_result);
}

void test_is_temperature_rising_zero_threshold_stable(void) {
    bool actual_result = is_temperature_rising(20.0f, 20.0f, 0.0f); // Expected: (20.0 - 20.0) = 0.0, which is NOT > 0.0f, so FALSE
    TEST_ASSERT_FALSE(actual_result);
}

void test_is_temperature_rising_negative_threshold_rising_significantly(void) {
    bool actual_result = is_temperature_rising(20.0f, 20.5f, 0.0f); // Expected: (20.5 - 20.0) = 0.5, which IS > 0.0f, so TRUE
    TEST_ASSERT_TRUE(actual_result);
}

void test_is_temperature_rising_negative_threshold_falling(void) {
    bool actual_result = is_temperature_rising(20.0f, 19.0f, 0.0f); // Expected: (19.0 - 20.0) = 0.0f, which is NOT > 0.0f, so FALSE
    TEST_ASSERT_FALSE(actual_result);
}



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_min_raw_value);
    RUN_TEST(test_raw_to_celsius_max_raw_value);
    RUN_TEST(test_raw_to_celsius_mid_raw_value);
    RUN_TEST(test_raw_to_celsius_quarter_raw_value);
    RUN_TEST(test_raw_to_celsius_three_quarter_raw_value);
    RUN_TEST(test_celsius_to_fahrenheit_freezing_point);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_negative_celsius_equal_f);
    RUN_TEST(test_celsius_to_fahrenheit_room_temperature);
    RUN_TEST(test_celsius_to_fahrenheit_max_celsius);
    RUN_TEST(test_is_temperature_rising_above_threshold);
    RUN_TEST(test_is_temperature_rising_equal_to_threshold);
    RUN_TEST(test_is_temperature_rising_below_threshold);
    RUN_TEST(test_is_temperature_rising_decreasing_temperature);
    RUN_TEST(test_is_temperature_rising_zero_threshold_rising);
    RUN_TEST(test_is_temperature_rising_zero_threshold_stable);
    RUN_TEST(test_is_temperature_rising_negative_threshold_rising_significantly);
    RUN_TEST(test_is_temperature_rising_negative_threshold_falling);

    return UNITY_END();
}