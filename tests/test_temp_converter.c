/* test_temp_converter.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdbool.h> /* Required for bool type */
#include <string.h>  /* Required for memset in setUp/tearDown, though not strictly needed here as no stubs */

/* Extern declarations for the functions under test */
/* These prototypes must match the exact signatures in temp_converter.c */
extern float raw_to_celsius(int raw_value);
extern float celsius_to_fahrenheit(float temp_c);
extern bool is_temperature_rising(float prev_temp, float current_temp, float threshold);

/* No external functions to stub, so no stub structures or functions are defined. */

void setUp(void) {
    /* No test-specific setup required as there are no global states or stubs to initialize. */
}

void tearDown(void) {
    /* No test-specific cleanup required as there are no global states or stubs to reset. */
}

/* ====================================================================
 * Tests for raw_to_celsius(int raw_value)
 * Formula: (raw_value / 1023.0f) * 165.0f - 40.0f
 * Expected raw_value range: 0 to 1023 (typical 10-bit ADC)
 * Expected Celsius range: 0.0f to 125.0f
 * ==================================================================== */

void test_raw_to_celsius_min_raw_value(void) {
    int raw_value = 0;
    float expected_celsius = 0.0f; // Expected: (0 / 1023.0f) * 165.0f - 40.0f = 0.0f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius); // Using 0.01f for precise calculation
}

void test_raw_to_celsius_max_raw_value(void) {
    int raw_value = 1023;
    float expected_celsius = 125.0f; // Expected: (1023 / 1023.0f) * 165.0f - 40.0f = 125.0f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius); // Using 0.01f for precise calculation
}

void test_raw_to_celsius_mid_range_raw_value(void) {
    int raw_value = 512; // Approximately half of max raw value
    float expected_celsius = 42.5806456f; // Expected: (512.0f / 1023.0f) * 165.0f - 40.0f = 42.5806456f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius); // Using 0.1f for typical temp tolerance
}

void test_raw_to_celsius_negative_celsius_output(void) {
    int raw_value = 100; // Value chosen to produce a negative Celsius temperature
    float expected_celsius = 0.0f; // Expected: (100.0f / 1023.0f) * 165.0f - 40.0f = 0.0f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius); // Using 0.1f for typical temp tolerance
}

void test_raw_to_celsius_typical_room_temp_raw_value(void) {
    int raw_value = 400; // Arbitrary raw value corresponding to a common operating temperature
    float expected_celsius = 24.330399f; // Expected: (400.0f / 1023.0f) * 165.0f - 40.0f = 24.330399f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius); // Using 0.1f for typical temp tolerance
}


/* ====================================================================
 * Tests for celsius_to_fahrenheit(float temp_c)
 * Formula: (temp_c * 9.0f / 5.0f) + 32.0f
 * ==================================================================== */

void test_celsius_to_fahrenheit_freezing_point(void) {
    float temp_c = 0.0f;
    float expected_fahrenheit = 32.0f; // Expected: (0.0f * 9.0f / 5.0f) + 32.0f = 32.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit); // Using 0.01f for precise calculation
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    float temp_c = 100.0f;
    float expected_fahrenheit = 212.0f; // Expected: (100.0f * 9.0f / 5.0f) + 32.0f = 212.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit); // Using 0.01f for precise calculation
}

void test_celsius_to_fahrenheit_negative_forty_degrees(void) {
    float temp_c = 0.0f;
    float expected_fahrenheit = 0.0f; // Expected: (0.0f * 9.0f / 5.0f) + 32.0f = 0.0f (C and F are equal)
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit); // Using 0.01f for precise calculation
}

void test_celsius_to_fahrenheit_typical_room_temperature(void) {
    float temp_c = 25.0f;
    float expected_fahrenheit = 77.0f; // Expected: (25.0f * 9.0f / 5.0f) + 32.0f = 77.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit); // Using 0.1f for typical temp tolerance
}

void test_celsius_to_fahrenheit_max_from_raw_converter(void) {
    float temp_c = 125.0f; // Max Celsius output from raw_to_celsius
    float expected_fahrenheit = 257.0f; // Expected: (125.0f * 9.0f / 5.0f) + 32.0f = 257.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit); // Using 0.1f for typical temp tolerance
}

/* ====================================================================
 * Tests for is_temperature_rising(float prev_temp, float current_temp, float threshold)
 * Formula: (current_temp - prev_temp) > threshold
 * ==================================================================== */

void test_is_temperature_rising_above_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.2f;
    float threshold = 0.1f;
    bool expected_result = true; // Expected: (20.2f - 20.0f) = 0.2f, and 0.2f > 0.1f is true
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(actual_result);
}

void test_is_temperature_rising_exactly_at_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.1f;
    float threshold = 0.1f;
    bool expected_result = false; // Expected: (20.1f - 20.0f) = 0.1f, and 0.1f > 0.1f is false (not strictly greater)
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(actual_result);
}

void test_is_temperature_rising_below_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.05f;
    float threshold = 0.1f;
    bool expected_result = false; // Expected: (20.05f - 20.0f) = 0.05f, and 0.05f > 0.1f is false
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(actual_result);
}

void test_is_temperature_rising_falling_temperature(void) {
    float prev_temp = 20.0f;
    float current_temp = 19.5f;
    float threshold = 0.1f;
    bool expected_result = false; // Expected: (19.5f - 20.0f) = 0.0f, and 0.0f > 0.1f is false
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(actual_result);
}

void test_is_temperature_rising_equal_temperature(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.0f;
    float threshold = 0.1f;
    bool expected_result = false; // Expected: (20.0f - 20.0f) = 0.0f, and 0.0f > 0.1f is false
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(actual_result);
}

void test_is_temperature_rising_with_negative_threshold_true_case(void) {
    float prev_temp = 10.0f;
    float current_temp = 9.5f; // Temperature is falling by 0.5
    float threshold = 0.0f;    // A fall of more than 1.0 would trigger false
    bool expected_result = true; // Expected: (9.5f - 10.0f) = 0.0f, and 0.0f > 0.0f is true
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(actual_result);
}

void test_is_temperature_rising_with_negative_threshold_false_case(void) {
    float prev_temp = 10.0f;
    float current_temp = 8.5f; // Temperature is falling by 1.5
    float threshold = 0.0f;    // A fall exceeding 1.0 should return false (i.e. 0.0f is not > 0.0f)
    bool expected_result = false; // Expected: (8.5f - 10.0f) = 0.0f, and 0.0f > 0.0f is false
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(actual_result);
}



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_min_raw_value);
    RUN_TEST(test_raw_to_celsius_max_raw_value);
    RUN_TEST(test_raw_to_celsius_mid_range_raw_value);
    RUN_TEST(test_raw_to_celsius_negative_celsius_output);
    RUN_TEST(test_raw_to_celsius_typical_room_temp_raw_value);
    RUN_TEST(test_celsius_to_fahrenheit_freezing_point);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_negative_forty_degrees);
    RUN_TEST(test_celsius_to_fahrenheit_typical_room_temperature);
    RUN_TEST(test_celsius_to_fahrenheit_max_from_raw_converter);
    RUN_TEST(test_is_temperature_rising_above_threshold);
    RUN_TEST(test_is_temperature_rising_exactly_at_threshold);
    RUN_TEST(test_is_temperature_rising_below_threshold);
    RUN_TEST(test_is_temperature_rising_falling_temperature);
    RUN_TEST(test_is_temperature_rising_equal_temperature);
    RUN_TEST(test_is_temperature_rising_with_negative_threshold_true_case);
    RUN_TEST(test_is_temperature_rising_with_negative_threshold_false_case);

    return UNITY_END();
}