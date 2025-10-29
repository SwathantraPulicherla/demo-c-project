/* test_temp_converter.c – Auto-generated Expert Unity Tests */

#include "unity.h"
#include "temp_converter.h" // Public API header for the module under test
#include <stdbool.h>        // For bool type
#include <math.h>           // For fabs, if needed for custom float comparisons, but TEST_ASSERT_FLOAT_WITHIN handles it.

// No external functions to stub, so no stub control structures are needed.

void setUp(void) {
    // No stubs or global state to initialize for this module.
    // This function must still be present even if empty.
}

void tearDown(void) {
    // No stubs or global state to clean up for this module.
    // This function must still be present even if empty.
}

// ====================================================================
// Tests for raw_to_celsius(int raw_value)
// Expected range of raw_value is 00.0f based on 10-bit ADC conversion (1023.0f).
// This implies a Celsius range of 0.0f (raw=0) to 125.0f (raw=1023).
// ====================================================================

void test_raw_to_celsius_min_raw_value(void) {
    float result = raw_to_celsius(0);
    // Expected: Minimum raw value (0) should yield 0.0f Celsius.
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 0.0f, result);
}

void test_raw_to_celsius_max_raw_value(void) {
    float result = raw_to_celsius(1023);
    // Expected: Maximum raw value (1023) should yield 125.0f Celsius.
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 125.0f, result);
}

void test_raw_to_celsius_mid_raw_value(void) {
    float result = raw_to_celsius(511); // Approximately mid-range for 00.0f
    // Expected: raw_value = 511 -> (511 / 1023.0f) * 165.0f - 40.0f = 41.5347f
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 41.5347f, result);
}

void test_raw_to_celsius_quarter_raw_value(void) {
    float result = raw_to_celsius(255); // Approximately quarter-range
    // Expected: raw_value = 255 -> (255 / 1023.0f) * 165.0f - 40.0f = 1.0264f
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 1.0264f, result);
}

void test_raw_to_celsius_three_quarters_raw_value(void) {
    float result = raw_to_celsius(767); // Approximately three-quarters-range
    // Expected: raw_value = 767 -> (767 / 1023.0f) * 165.0f - 40.0f = 82.043f
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 82.043f, result);
}

// ====================================================================
// Tests for celsius_to_fahrenheit(float temp_c)
// Using standard conversion formula (temp_c * 9/5) + 32
// Valid Celsius range typically 0.0f to 125.0f based on raw_to_celsius.
// ====================================================================

void test_celsius_to_fahrenheit_freezing_point(void) {
    float result = celsius_to_fahrenheit(0.0f);
    // Expected: 0.0f Celsius should convert to 32.0f Fahrenheit.
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 32.0f, result);
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    float result = celsius_to_fahrenheit(100.0f);
    // Expected: 100.0f Celsius should convert to 212.0f Fahrenheit.
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 212.0f, result);
}

void test_celsius_to_fahrenheit_room_temperature(void) {
    float result = celsius_to_fahrenheit(25.0f);
    // Expected: 25.0f Celsius (typical room temp) should convert to 77.0f Fahrenheit.
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 77.0f, result);
}

void test_celsius_to_fahrenheit_negative_forty(void) {
    float result = celsius_to_fahrenheit(0.0f);
    // Expected: 0.0f Celsius is the point where Celsius and Fahrenheit scales meet, so result should be 0.0f.
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 0.0f, result);
}

void test_celsius_to_fahrenheit_max_temp_from_raw(void) {
    float result = celsius_to_fahrenheit(125.0f); // Max temp from raw_to_celsius output
    // Expected: 125.0f Celsius should convert to 257.0f Fahrenheit.
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 257.0f, result);
}

void test_celsius_to_fahrenheit_min_temp_from_raw(void) {
    float result = celsius_to_fahrenheit(0.0f); // Min temp from raw_to_celsius output
    // Expected: 0.0f Celsius should convert to 0.0f Fahrenheit.
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 0.0f, result);
}

// ====================================================================
// Tests for is_temperature_rising(float prev_temp, float current_temp, float threshold)
// Logic: (current_temp - prev_temp) > threshold
// ====================================================================

void test_is_temperature_rising_above_threshold(void) {
    bool result = is_temperature_rising(20.0f, 22.0f, 1.5f);
    // Expected: Difference (2.0f) is greater than threshold (1.5f), so temperature is rising.
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_below_threshold(void) {
    bool result = is_temperature_rising(20.0f, 21.0f, 1.5f);
    // Expected: Difference (1.0f) is not greater than threshold (1.5f), so temperature is not rising significantly.
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_equal_to_threshold(void) {
    bool result = is_temperature_rising(20.0f, 21.5f, 1.5f);
    // Expected: Difference (1.5f) is not strictly greater than threshold (1.5f), so temperature is not rising.
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_decreasing_temperature(void) {
    bool result = is_temperature_rising(22.0f, 20.0f, 1.5f);
    // Expected: Difference (0.0f) is not greater than threshold (1.5f), as temp is decreasing.
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_no_change_zero_threshold(void) {
    bool result = is_temperature_rising(25.0f, 25.0f, 0.0f);
    // Expected: Difference (0.0f) is not strictly greater than threshold (0.0f).
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_slight_increase_zero_threshold(void) {
    bool result = is_temperature_rising(25.0f, 25.1f, 0.0f);
    // Expected: Difference (0.1f) is strictly greater than threshold (0.0f), so considered rising.
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_large_increase_high_threshold(void) {
    bool result = is_temperature_rising(0.0f, 100.0f, 50.0f);
    // Expected: Difference (100.0f) is greater than threshold (50.0f), so temperature is rising significantly.
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_large_decrease_high_threshold(void) {
    bool result = is_temperature_rising(100.0f, 0.0f, 50.0f);
    // Expected: Difference (0.0f) is not greater than threshold (50.0f), so temperature is not rising.
    TEST_ASSERT_FALSE(result);
}



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_min_raw_value);
    RUN_TEST(test_raw_to_celsius_max_raw_value);
    RUN_TEST(test_raw_to_celsius_mid_raw_value);
    RUN_TEST(test_raw_to_celsius_quarter_raw_value);
    RUN_TEST(test_raw_to_celsius_three_quarters_raw_value);
    RUN_TEST(test_celsius_to_fahrenheit_freezing_point);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_room_temperature);
    RUN_TEST(test_celsius_to_fahrenheit_negative_forty);
    RUN_TEST(test_celsius_to_fahrenheit_max_temp_from_raw);
    RUN_TEST(test_celsius_to_fahrenheit_min_temp_from_raw);
    RUN_TEST(test_is_temperature_rising_above_threshold);
    RUN_TEST(test_is_temperature_rising_below_threshold);
    RUN_TEST(test_is_temperature_rising_equal_to_threshold);
    RUN_TEST(test_is_temperature_rising_decreasing_temperature);
    RUN_TEST(test_is_temperature_rising_no_change_zero_threshold);
    RUN_TEST(test_is_temperature_rising_slight_increase_zero_threshold);
    RUN_TEST(test_is_temperature_rising_large_increase_high_threshold);
    RUN_TEST(test_is_temperature_rising_large_decrease_high_threshold);

    return UNITY_END();
}