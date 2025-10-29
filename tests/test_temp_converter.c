/* test_temp_converter.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdbool.h>    // For bool type
#include "temp_converter.h" // Prototypes for functions under test. Necessary.

// No external functions were listed for stubbing, so no stub structures or functions are needed.

void setUp(void) {
    // No stubs or global states to initialize for this module's functions.
}

void tearDown(void) {
    // No stubs or global states to clean up for this module's functions.
}

// ====================================================================================
// Test Cases for raw_to_celsius(int raw_value)
// Formula: (raw_value / 1023.0f) * 165.0f - 40.0f
// Realistic input range for raw_value: 00.0f (assuming a 10-bit ADC).
// Expected output Celsius range for 00.0f raw values: 0.0f to 125.0f.
// ====================================================================================

void test_raw_to_celsius_min_raw_value(void) {
    float result = raw_to_celsius(0);
    // Expected: A raw value of 0 should convert to the minimum temperature of 0.0f.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, result);
}

void test_raw_to_celsius_max_raw_value(void) {
    float result = raw_to_celsius(1023);
    // Expected: A raw value of 1023 should convert to the maximum temperature of 125.0f.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 125.0f, result);
}

void test_raw_to_celsius_mid_range_raw_value(void) {
    // Using a mid-range raw value (e.g., 511, approximately half of 1023).
    float result = raw_to_celsius(511);
    // Expected: (511 / 1023.0f) * 165.0f - 40.0f = 42.41935f.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 42.41935f, result);
}

void test_raw_to_celsius_nominal_ambient_raw_value(void) {
    // Calculate raw_value that corresponds to a nominal ambient temperature like 20.0f C.
    // 20.0f = (raw / 1023.0f) * 165.0f - 40.0f  =>  60.0f = (raw / 1023.0f) * 165.0f
    // raw = (60.0f * 1023.0f) / 165.0f = 372.0f.
    float result = raw_to_celsius(372);
    // Expected: A raw value of 372 should convert approximately to 20.0f Celsius.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 20.0f, result);
}

// ====================================================================================
// Test Cases for celsius_to_fahrenheit(float temp_c)
// Formula: (temp_c * 9.0f / 5.0f) + 32.0f
// Input temp_c range from raw_to_celsius: 0.0f to 125.0f.
// ====================================================================================

void test_celsius_to_fahrenheit_freezing_point(void) {
    float result = celsius_to_fahrenheit(0.0f);
    // Expected: 0.0f Celsius (water freezing point) should convert to 32.0f Fahrenheit.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 32.0f, result);
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    float result = celsius_to_fahrenheit(100.0f);
    // Expected: 100.0f Celsius (water boiling point) should convert to 212.0f Fahrenheit.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 212.0f, result);
}

void test_celsius_to_fahrenheit_human_body_temperature(void) {
    float result = celsius_to_fahrenheit(37.0f);
    // Expected: 37.0f Celsius (average human body temp) should convert to 98.6f Fahrenheit.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 98.6f, result);
}

void test_celsius_to_fahrenheit_min_celsius_range_equality_point(void) {
    float result = celsius_to_fahrenheit(0.0f);
    // Expected: 0.0f Celsius is the unique point where C and F scales are equal, converting to 0.0f Fahrenheit.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, result);
}

void test_celsius_to_fahrenheit_max_celsius_range(void) {
    float result = celsius_to_fahrenheit(125.0f);
    // Expected: 125.0f Celsius (the maximum output from raw_to_celsius) should convert to 257.0f Fahrenheit.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 257.0f, result);
}

// ====================================================================================
// Test Cases for is_temperature_rising(float prev_temp, float current_temp, float threshold)
// Logic: (current_temp - prev_temp) > threshold
// ====================================================================================

void test_is_temperature_rising_above_threshold(void) {
    bool result = is_temperature_rising(20.0f, 22.0f, 1.0f);
    // Expected: The temperature difference (2.0f) is greater than the threshold (1.0f), so result is true.
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_equal_to_threshold(void) {
    bool result = is_temperature_rising(20.0f, 21.0f, 1.0f);
    // Expected: The temperature difference (1.0f) is NOT greater than the threshold (1.0f), so result is false.
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_below_threshold(void) {
    bool result = is_temperature_rising(20.0f, 20.5f, 1.0f);
    // Expected: The temperature difference (0.5f) is not greater than the threshold (1.0f), so result is false.
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_with_negative_temps_and_rising(void) {
    bool result = is_temperature_rising(0.0f, 0.0f, 1.0f);
    // Expected: The temperature difference (0.0f - (0.0f) = 5.0f) is greater than the threshold (1.0f), so true.
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_with_negative_temps_and_falling(void) {
    bool result = is_temperature_rising(0.0f, 0.0f, 1.0f);
    // Expected: The temperature difference (0.0f - (0.0f) = 0.0f) is not greater than the threshold (1.0f), so false.
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_with_zero_threshold_and_rising(void) {
    bool result = is_temperature_rising(20.0f, 20.1f, 0.0f);
    // Expected: The temperature difference (0.1f) is greater than the threshold (0.0f), so true.
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_with_zero_threshold_and_no_change(void) {
    bool result = is_temperature_rising(20.0f, 20.0f, 0.0f);
    // Expected: The temperature difference (0.0f) is not greater than the threshold (0.0f), so false.
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_with_significant_fall(void) {
    bool result = is_temperature_rising(50.0f, 20.0f, 5.0f);
    // Expected: The temperature difference (0.0f) is not greater than the threshold (5.0f), so false.
    TEST_ASSERT_FALSE(result);
}

// ====================================================================================
// Main Test Runner
// ====================================================================================



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_min_raw_value);
    RUN_TEST(test_raw_to_celsius_max_raw_value);
    RUN_TEST(test_raw_to_celsius_mid_range_raw_value);
    RUN_TEST(test_raw_to_celsius_nominal_ambient_raw_value);
    RUN_TEST(test_celsius_to_fahrenheit_freezing_point);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_human_body_temperature);
    RUN_TEST(test_celsius_to_fahrenheit_min_celsius_range_equality_point);
    RUN_TEST(test_celsius_to_fahrenheit_max_celsius_range);
    RUN_TEST(test_is_temperature_rising_above_threshold);
    RUN_TEST(test_is_temperature_rising_equal_to_threshold);
    RUN_TEST(test_is_temperature_rising_below_threshold);
    RUN_TEST(test_is_temperature_rising_with_negative_temps_and_rising);
    RUN_TEST(test_is_temperature_rising_with_negative_temps_and_falling);
    RUN_TEST(test_is_temperature_rising_with_zero_threshold_and_rising);
    RUN_TEST(test_is_temperature_rising_with_zero_threshold_and_no_change);
    RUN_TEST(test_is_temperature_rising_with_significant_fall);

    return UNITY_END();
}