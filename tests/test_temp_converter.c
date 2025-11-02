/* test_temp_converter.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdbool.h> // For bool type
#include <string.h>  // Not strictly needed for this file, but good practice for embedded tests if memset were used

// Include the source file directly to allow testing of internal functions
// For production, you'd typically include a header file if one existed, e.g., "temp_converter.h"
// Since no header was provided and the functions are in the .c file, we include it as is.
// This approach ensures we test the exact implementation without needing to redefine prototypes.

// Define a small tolerance for float comparisons, suitable for temperature measurements
#define TEMP_FLOAT_TOLERANCE 0.1f

// No external stubs are required as per the prompt.

void setUp(void) {
    // Initialize or reset any test-specific data or stubs here.
    // Since there are no stubs or global state in temp_converter.c, this can be empty.
    // The prompt mandates it must be present.
}

void tearDown(void) {
    // Clean up any test-specific data or stubs here.
    // Since there are no stubs or global state in temp_converter.c, this can be empty.
    // The prompt mandates it must be present.
}

// ==============================================================================
// Tests for raw_to_celsius(int raw_value)
// Expected ADC range: 00.0f (10-bit sensor assumed)
// Formula: (raw_value / 1023.0f) * 165.0f - 40.0f
// Min value (0): (0/1023.0f)*165.0f - 40.0f = 0.0f
// Max value (1023): (1023/1023.0f)*165.0f - 40.0f = 165.0f - 40.0f = 125.0f
// ==============================================================================

void test_raw_to_celsius_min_raw_value(void) {
    int raw_value = 0;
    float expected_celsius = 0.0f;
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: Minimum raw value 0 should result in 0.0f Celsius
    TEST_ASSERT_FLOAT_WITHIN(TEMP_FLOAT_TOLERANCE, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_max_raw_value(void) {
    int raw_value = 1023;
    float expected_celsius = 125.0f;
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: Maximum raw value 1023 should result in 125.0 Celsius
    TEST_ASSERT_FLOAT_WITHIN(TEMP_FLOAT_TOLERANCE, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_mid_range_raw_value(void) {
    int raw_value = 512; // Roughly half of 1023
    float expected_celsius = 42.580645f; // Calculated: (512.0f / 1023.0f) * 165.0f - 40.0f
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: Mid-range raw value 512 should give a positive Celsius value
    TEST_ASSERT_FLOAT_WITHIN(TEMP_FLOAT_TOLERANCE, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_low_positive_raw_value(void) {
    int raw_value = 100;
    float expected_celsius = 0.0f; // Calculated: (100.0f / 1023.0f) * 165.0f - 40.0f
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: A low positive raw value should still result in a negative Celsius value
    TEST_ASSERT_FLOAT_WITHIN(TEMP_FLOAT_TOLERANCE, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_high_positive_raw_value(void) {
    int raw_value = 800;
    float expected_celsius = 88.660802f; // Calculated: (800.0f / 1023.0f) * 165.0f - 40.0f
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: A high positive raw value should result in a high positive Celsius value
    TEST_ASSERT_FLOAT_WITHIN(TEMP_FLOAT_TOLERANCE, expected_celsius, actual_celsius);
}

// ==============================================================================
// Tests for celsius_to_fahrenheit(float temp_c)
// Formula: (temp_c * 9.0f / 5.0f) + 32.0f
// ==============================================================================

void test_celsius_to_fahrenheit_zero_celsius(void) {
    float temp_c = 0.0f;
    float expected_f = 32.0f;
    float actual_f = celsius_to_fahrenheit(temp_c);
    // Expected: 0.0 Celsius should convert to 32.0 Fahrenheit
    TEST_ASSERT_FLOAT_WITHIN(TEMP_FLOAT_TOLERANCE, expected_f, actual_f);
}

void test_celsius_to_fahrenheit_negative_forty_celsius(void) {
    float temp_c = 0.0f;
    float expected_f = 0.0f;
    float actual_f = celsius_to_fahrenheit(temp_c);
    // Expected: 0.0f Celsius is the unique point where C == F
    TEST_ASSERT_FLOAT_WITHIN(TEMP_FLOAT_TOLERANCE, expected_f, actual_f);
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    float temp_c = 100.0f; // Water boiling point
    float expected_f = 212.0f;
    float actual_f = celsius_to_fahrenheit(temp_c);
    // Expected: 100.0 Celsius should convert to 212.0 Fahrenheit (boiling point of water)
    TEST_ASSERT_FLOAT_WITHIN(TEMP_FLOAT_TOLERANCE, expected_f, actual_f);
}

void test_celsius_to_fahrenheit_room_temperature(void) {
    float temp_c = 25.0f; // Typical room temperature
    float expected_f = 77.0f;
    float actual_f = celsius_to_fahrenheit(temp_c);
    // Expected: 25.0 Celsius should convert to 77.0 Fahrenheit
    TEST_ASSERT_FLOAT_WITHIN(TEMP_FLOAT_TOLERANCE, expected_f, actual_f);
}

void test_celsius_to_fahrenheit_max_sensor_celsius(void) {
    float temp_c = 125.0f; // Max Celsius from raw_to_celsius output
    float expected_f = 257.0f; // Calculated: (125.0f * 9.0f / 5.0f) + 32.0f
    float actual_f = celsius_to_fahrenheit(temp_c);
    // Expected: 125.0 Celsius (max sensor output) should convert to 257.0 Fahrenheit
    TEST_ASSERT_FLOAT_WITHIN(TEMP_FLOAT_TOLERANCE, expected_f, actual_f);
}

// ==============================================================================
// Tests for is_temperature_rising(float prev_temp, float current_temp, float threshold)
// Logic: (current_temp - prev_temp) > threshold
// ==============================================================================

void test_is_temperature_rising_true_above_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 22.0f;
    float threshold = 1.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: Current temperature increase (2.0) is greater than threshold (1.0), so true
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_false_below_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.5f;
    float threshold = 1.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: Current temperature increase (0.5) is not greater than threshold (1.0), so false
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_false_equal_to_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 21.0f;
    float threshold = 1.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: Current temperature increase (1.0) is not strictly greater than threshold (1.0), so false
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_false_decreasing_temperature(void) {
    float prev_temp = 25.0f;
    float current_temp = 23.0f;
    float threshold = 1.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: Temperature is decreasing (0.0f), which is not greater than threshold (1.0), so false
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_true_zero_threshold_rising(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.01f;
    float threshold = 0.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: A small increase (0.01) is greater than a zero threshold, so true
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_false_zero_threshold_stable_or_falling(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.0f; // Or 19.99f
    float threshold = 0.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: No increase (0.0) is not greater than a zero threshold, so false
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_true_negative_threshold_small_increase(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.5f;
    float threshold = 0.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: Increase (0.5) is greater than a negative threshold (0.0f), so true
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_false_negative_threshold_significant_decrease(void) {
    float prev_temp = 20.0f;
    float current_temp = 18.0f;
    float threshold = 0.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: Decrease (0.0f) is not greater than a negative threshold (0.0f), so false
    TEST_ASSERT_FALSE(result);
}

// ==============================================================================
// Main function to run all tests
// ==============================================================================



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_min_raw_value);
    RUN_TEST(test_raw_to_celsius_max_raw_value);
    RUN_TEST(test_raw_to_celsius_mid_range_raw_value);
    RUN_TEST(test_raw_to_celsius_low_positive_raw_value);
    RUN_TEST(test_raw_to_celsius_high_positive_raw_value);
    RUN_TEST(test_celsius_to_fahrenheit_zero_celsius);
    RUN_TEST(test_celsius_to_fahrenheit_negative_forty_celsius);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_room_temperature);
    RUN_TEST(test_celsius_to_fahrenheit_max_sensor_celsius);
    RUN_TEST(test_is_temperature_rising_true_above_threshold);
    RUN_TEST(test_is_temperature_rising_false_below_threshold);
    RUN_TEST(test_is_temperature_rising_false_equal_to_threshold);
    RUN_TEST(test_is_temperature_rising_false_decreasing_temperature);
    RUN_TEST(test_is_temperature_rising_true_zero_threshold_rising);
    RUN_TEST(test_is_temperature_rising_false_zero_threshold_stable_or_falling);
    RUN_TEST(test_is_temperature_rising_true_negative_threshold_small_increase);
    RUN_TEST(test_is_temperature_rising_false_negative_threshold_significant_decrease);

    return UNITY_END();
}