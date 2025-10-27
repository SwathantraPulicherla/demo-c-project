#include "unity.h"
#include "temp_converter.h" // Include the header for the C file being tested

// No stub functions are required for this C file.

void setUp(void) {
    // This function is run before every test.
    // Initialize any common resources or reset stub states here.
    // No stubs to reset in this case.
}

void tearDown(void) {
    // This function is run after every test.
    // Clean up any common resources here.
    // No stub states to reset or resources to clean up in this case.
}

// --- Test Cases for raw_to_celsius ---

void test_raw_to_celsius_min_raw_value(void) {
    int raw_value = 0;
    float expected_celsius = -40.0f;
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_max_raw_value(void) {
    int raw_value = 1023;
    float expected_celsius = 125.0f;
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_mid_raw_value(void) {
    int raw_value = 512;
    // (512 / 1023.0f) * 165.0f - 40.0f = 0.5004887585532746 * 165 - 40 = 82.58064516 - 40 = 42.58064516
    float expected_celsius = 42.58f; 
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_low_range_raw_value(void) {
    int raw_value = 256;
    // (256 / 1023.0f) * 165.0f - 40.0f = 0.2502443792766373 * 165 - 40 = 41.29032258 - 40 = 1.29032258
    float expected_celsius = 1.29f;
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_high_range_raw_value(void) {
    int raw_value = 768;
    // (768 / 1023.0f) * 165.0f - 40.0f = 0.750733137829912 * 165 - 40 = 123.871995 - 40 = 83.871995
    float expected_celsius = 83.87f;
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

// --- Test Cases for celsius_to_fahrenheit ---

void test_celsius_to_fahrenheit_zero_celsius(void) {
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

void test_celsius_to_fahrenheit_freezing_point(void) {
    float temp_c = 0.0f;
    float expected_f = 32.0f;
    float actual_f = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_f, actual_f);
}

void test_celsius_to_fahrenheit_negative_forty(void) {
    float temp_c = -40.0f;
    float expected_f = -40.0f; // Where Celsius and Fahrenheit scales meet
    float actual_f = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_f, actual_f);
}

void test_celsius_to_fahrenheit_room_temperature(void) {
    float temp_c = 25.0f;
    float expected_f = 77.0f;
    float actual_f = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_f, actual_f);
}

void test_celsius_to_fahrenheit_cold_temperature(void) {
    float temp_c = -10.0f;
    float expected_f = 14.0f;
    float actual_f = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_f, actual_f);
}

// --- Test Cases for is_temperature_rising ---

void test_is_temperature_rising_true_significant_rise(void) {
    float prev_temp = 20.0f;
    float current_temp = 25.0f;
    float threshold = 2.0f;
    TEST_ASSERT_TRUE(is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_true_slight_rise_above_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 22.01f;
    float threshold = 2.0f;
    TEST_ASSERT_TRUE(is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_false_at_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 22.0f;
    float threshold = 2.0f;
    TEST_ASSERT_FALSE(is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_false_below_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 21.99f;
    float threshold = 2.0f;
    TEST_ASSERT_FALSE(is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_false_constant_temperature(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.0f;
    float threshold = 0.5f;
    TEST_ASSERT_FALSE(is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_false_falling_temperature(void) {
    float prev_temp = 25.0f;
    float current_temp = 20.0f;
    float threshold = 1.0f;
    TEST_ASSERT_FALSE(is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_false_falling_temperature_negative_threshold(void) {
    float prev_temp = 25.0f;
    float current_temp = 20.0f;
    float threshold = -10.0f; // A negative threshold means it's rising if it falls less than the negative threshold
    TEST_ASSERT_TRUE(is_temperature_rising(prev_temp, current_temp, threshold)); // -5.0 > -10.0 is true
}

void test_is_temperature_rising_false_with_zero_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.0f;
    float threshold = 0.0f;
    TEST_ASSERT_FALSE(is_temperature_rising(prev_temp, current_temp, threshold)); // 0.0 > 0.0 is false
}

void test_is_temperature_rising_true_with_zero_threshold_and_slight_rise(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.01f;
    float threshold = 0.0f;
    TEST_ASSERT_TRUE(is_temperature_rising(prev_temp, current_temp, threshold)); // 0.01 > 0.0 is true
}

// --- Main function to run tests ---


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_min_raw_value);
    RUN_TEST(test_raw_to_celsius_max_raw_value);
    RUN_TEST(test_raw_to_celsius_mid_raw_value);
    RUN_TEST(test_raw_to_celsius_low_range_raw_value);
    RUN_TEST(test_raw_to_celsius_high_range_raw_value);
    RUN_TEST(test_celsius_to_fahrenheit_zero_celsius);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_freezing_point);
    RUN_TEST(test_celsius_to_fahrenheit_negative_forty);
    RUN_TEST(test_celsius_to_fahrenheit_room_temperature);
    RUN_TEST(test_celsius_to_fahrenheit_cold_temperature);
    RUN_TEST(test_is_temperature_rising_true_significant_rise);
    RUN_TEST(test_is_temperature_rising_true_slight_rise_above_threshold);
    RUN_TEST(test_is_temperature_rising_false_at_threshold);
    RUN_TEST(test_is_temperature_rising_false_below_threshold);
    RUN_TEST(test_is_temperature_rising_false_constant_temperature);
    RUN_TEST(test_is_temperature_rising_false_falling_temperature);
    RUN_TEST(test_is_temperature_rising_false_falling_temperature_negative_threshold);
    RUN_TEST(test_is_temperature_rising_false_with_zero_threshold);
    RUN_TEST(test_is_temperature_rising_true_with_zero_threshold_and_slight_rise);

    return UNITY_END();
}