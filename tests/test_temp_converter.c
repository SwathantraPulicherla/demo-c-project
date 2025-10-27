#include "unity.h"
#include "temp_converter.h" // Include the header file for the source code under test

// Define temperature tolerance for float comparisons
#define TEMP_TOLERANCE 0.1f

void setUp(void) {
    // No specific setup needed for these tests
}

void tearDown(void) {
    // No specific tear down needed for these tests
}

// --- Test Cases for raw_to_celsius ---

void test_raw_to_celsius_min_raw_value(void) {
    int raw_value = 0;
    float expected_celsius = 0.0f; // (0 / 1023.0f) * 165.0f - 40.0f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(TEMP_TOLERANCE, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_max_raw_value(void) {
    int raw_value = 1023;
    float expected_celsius = 125.0f; // (1023 / 1023.0f) * 165.0f - 40.0f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(TEMP_TOLERANCE, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_mid_range_raw_value(void) {
    // Corresponds to approx 42.4 C
    int raw_value = 511; 
    float expected_celsius = (511 / 1023.0f) * 165.0f - 40.0f;
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(TEMP_TOLERANCE, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_approx_freezing_point(void) {
    // Raw value for 0C: 1023 * (40/165) = ~248.0
    int raw_value = 248; 
    float expected_celsius = 0.0f;
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(TEMP_TOLERANCE, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_approx_room_temperature(void) {
    // Raw value for 25C: 1023 * (65/165) = ~402.7
    int raw_value = 403; 
    float expected_celsius = 25.01f; // (403 / 1023.0f) * 165.0f - 40.0f = 25.01f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(TEMP_TOLERANCE, expected_celsius, actual_celsius);
}


// --- Test Cases for celsius_to_fahrenheit ---

void test_celsius_to_fahrenheit_freezing_point(void) {
    float temp_c = 0.0f;
    float expected_fahrenheit = 32.0f; // (0.0f * 9.0f / 5.0f) + 32.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(TEMP_TOLERANCE, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    float temp_c = 100.0f;
    float expected_fahrenheit = 212.0f; // (100.0f * 9.0f / 5.0f) + 32.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(TEMP_TOLERANCE, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_room_temperature(void) {
    float temp_c = 25.0f;
    float expected_fahrenheit = 77.0f; // (25.0f * 9.0f / 5.0f) + 32.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(TEMP_TOLERANCE, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_min_operational_temp(void) {
    float temp_c = 0.0f;
    float expected_fahrenheit = 0.0f; // (0.0f * 9.0f / 5.0f) + 32.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(TEMP_TOLERANCE, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_max_operational_temp(void) {
    float temp_c = 125.0f;
    float expected_fahrenheit = 257.0f; // (125.0f * 9.0f / 5.0f) + 32.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(TEMP_TOLERANCE, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_negative_celsius(void) {
    float temp_c = 0.0f;
    float expected_fahrenheit = 14.0f; // (0.0f * 9.0f / 5.0f) + 32.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(TEMP_TOLERANCE, expected_fahrenheit, actual_fahrenheit);
}

// --- Test Cases for is_temperature_rising ---

void test_is_temperature_rising_true_clearly_rising(void) {
    float prev_temp = 20.0f;
    float current_temp = 25.0f;
    float threshold = 1.0f;
    TEST_ASSERT_TRUE(is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_false_stable(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.1f;
    float threshold = 1.0f;
    TEST_ASSERT_FALSE(is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_false_falling(void) {
    float prev_temp = 25.0f;
    float current_temp = 20.0f;
    float threshold = 1.0f;
    TEST_ASSERT_FALSE(is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_false_at_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 21.0f;
    float threshold = 1.0f;
    // (21.0f - 20.0f) = 1.0f, which is not > 1.0f
    TEST_ASSERT_FALSE(is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_true_just_above_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 21.01f;
    float threshold = 1.0f;
    // (21.01f - 20.0f) = 1.01f, which is > 1.0f
    TEST_ASSERT_TRUE(is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_zero_threshold_rising(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.01f;
    float threshold = 0.0f;
    // (20.01f - 20.0f) = 0.01f, which is > 0.0f
    TEST_ASSERT_TRUE(is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_zero_threshold_stable(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.0f;
    float threshold = 0.0f;
    // (20.0f - 20.0f) = 0.0f, which is not > 0.0f
    TEST_ASSERT_FALSE(is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_negative_threshold_with_rise(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.5f;
    float threshold = 0.0f;
    // (20.5f - 20.0f) = 0.5f, which is > 0.0f
    TEST_ASSERT_TRUE(is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_negative_threshold_with_fall(void) {
    float prev_temp = 20.0f;
    float current_temp = 19.5f;
    float threshold = 0.0f;
    // (19.5f - 20.0f) = 0.0f, which is > 0.0f
    TEST_ASSERT_TRUE(is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_negative_threshold_with_large_fall(void) {
    float prev_temp = 20.0f;
    float current_temp = 18.0f;
    float threshold = 0.0f;
    // (18.0f - 20.0f) = 0.0f, which is not > 0.0f
    TEST_ASSERT_FALSE(is_temperature_rising(prev_temp, current_temp, threshold));
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_min_raw_value);
    RUN_TEST(test_raw_to_celsius_max_raw_value);
    RUN_TEST(test_raw_to_celsius_mid_range_raw_value);
    RUN_TEST(test_raw_to_celsius_approx_freezing_point);
    RUN_TEST(test_raw_to_celsius_approx_room_temperature);
    RUN_TEST(test_celsius_to_fahrenheit_freezing_point);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_room_temperature);
    RUN_TEST(test_celsius_to_fahrenheit_min_operational_temp);
    RUN_TEST(test_celsius_to_fahrenheit_max_operational_temp);
    RUN_TEST(test_celsius_to_fahrenheit_negative_celsius);
    RUN_TEST(test_is_temperature_rising_true_clearly_rising);
    RUN_TEST(test_is_temperature_rising_false_stable);
    RUN_TEST(test_is_temperature_rising_false_falling);
    RUN_TEST(test_is_temperature_rising_false_at_threshold);
    RUN_TEST(test_is_temperature_rising_true_just_above_threshold);
    RUN_TEST(test_is_temperature_rising_zero_threshold_rising);
    RUN_TEST(test_is_temperature_rising_zero_threshold_stable);
    RUN_TEST(test_is_temperature_rising_negative_threshold_with_rise);
    RUN_TEST(test_is_temperature_rising_negative_threshold_with_fall);
    RUN_TEST(test_is_temperature_rising_negative_threshold_with_large_fall);

    return UNITY_END();
}