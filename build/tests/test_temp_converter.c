#include "unity.h"
#include "temp_converter.h"
#include <stdbool.h>

// No stubs needed for this C file according to the instructions.

void setUp(void) {
    // No stubs to reset.
}

void tearDown(void) {
    // No stubs to reset.
}

// Test for raw_to_celsius function
void test_raw_to_celsius_min_value(void) {
    int raw_value = 0; // Minimum raw value
    float expected_celsius = -40.0f;
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_max_value(void) {
    int raw_value = 1023; // Maximum raw value
    float expected_celsius = 125.0f;
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_mid_value(void) {
    int raw_value = 511; // Mid-range raw value
    float expected_celsius = 42.42f; // (511 / 1023.0f) * 165.0f - 40.0f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_zero_raw(void) {
    int raw_value = 0;
    float expected_celsius = -40.0f;
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_specific_value(void) {
    int raw_value = 256;
    float expected_celsius = (256 / 1023.0f) * 165.0f - 40.0f; // Approx 1.05
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}


// Test for celsius_to_fahrenheit function
void test_celsius_to_fahrenheit_freezing_point(void) {
    float temp_c = 0.0f;
    float expected_f = 32.0f;
    float actual_f = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_f, actual_f);
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    float temp_c = 100.0f;
    float expected_f = 212.0f;
    float actual_f = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_f, actual_f);
}

void test_celsius_to_fahrenheit_negative_celsius(void) {
    float temp_c = -10.0f;
    float expected_f = 14.0f;
    float actual_f = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_f, actual_f);
}

void test_celsius_to_fahrenheit_room_temp(void) {
    float temp_c = 25.0f;
    float expected_f = 77.0f;
    float actual_f = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_f, actual_f);
}

void test_celsius_to_fahrenheit_absolute_zero(void) {
    float temp_c = -273.15f; // Absolute zero in Celsius
    float expected_f = -459.67f; // Absolute zero in Fahrenheit
    float actual_f = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_f, actual_f);
}


// Test for is_temperature_rising function
void test_is_temperature_rising_true(void) {
    float prev_temp = 20.0f;
    float current_temp = 22.0f;
    float threshold = 1.0f;
    TEST_ASSERT_TRUE(is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_false_below_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.5f;
    float threshold = 1.0f;
    TEST_ASSERT_FALSE(is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_false_equal_to_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 21.0f;
    float threshold = 1.0f;
    TEST_ASSERT_FALSE(is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_false_decreasing(void) {
    float prev_temp = 25.0f;
    float current_temp = 22.0f;
    float threshold = 1.0f;
    TEST_ASSERT_FALSE(is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_false_equal(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.0f;
    float threshold = 0.5f;
    TEST_ASSERT_FALSE(is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_zero_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.1f;
    float threshold = 0.0f;
    TEST_ASSERT_TRUE(is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_negative_threshold_rising(void) {
    float prev_temp = 20.0f;
    float current_temp = 21.0f;
    float threshold = -1.0f; // A negative threshold makes it easier to "rise"
    TEST_ASSERT_TRUE(is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_negative_threshold_falling(void) {
    float prev_temp = 21.0f;
    float current_temp = 20.0f;
    float threshold = -2.0f;
    TEST_ASSERT_TRUE(is_temperature_rising(prev_temp, current_temp, threshold)); // -1.0 > -2.0
}




int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_min_value);
    RUN_TEST(test_raw_to_celsius_max_value);
    RUN_TEST(test_raw_to_celsius_mid_value);
    RUN_TEST(test_raw_to_celsius_zero_raw);
    RUN_TEST(test_raw_to_celsius_specific_value);
    RUN_TEST(test_celsius_to_fahrenheit_freezing_point);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_negative_celsius);
    RUN_TEST(test_celsius_to_fahrenheit_room_temp);
    RUN_TEST(test_celsius_to_fahrenheit_absolute_zero);
    RUN_TEST(test_is_temperature_rising_true);
    RUN_TEST(test_is_temperature_rising_false_below_threshold);
    RUN_TEST(test_is_temperature_rising_false_equal_to_threshold);
    RUN_TEST(test_is_temperature_rising_false_decreasing);
    RUN_TEST(test_is_temperature_rising_false_equal);
    RUN_TEST(test_is_temperature_rising_zero_threshold);
    RUN_TEST(test_is_temperature_rising_negative_threshold_rising);
    RUN_TEST(test_is_temperature_rising_negative_threshold_falling);

    return UNITY_END();
}