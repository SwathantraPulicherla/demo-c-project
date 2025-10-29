/* test_temp_converter.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include "temp_converter.h" // Contains declarations for functions under test
#include <stdbool.h>      // For bool type
#include <string.h>       // Not strictly needed here, but good practice for embedded

// No external functions to stub, so no stub control structs needed.

void setUp(void) {
    // No specific setup required for these functions, as they are pure calculations
    // and have no external dependencies or state.
}

void tearDown(void) {
    // No specific cleanup required.
}

// ==============================================================================
// Tests for raw_to_celsius(int raw_value)
// Formula: (raw_value / 1023.0f) * 165.0f - 40.0f
// Input range: 00.0f (for 10-bit ADC)
// Output range: 0.0f to 125.0f
// ==============================================================================

void test_raw_to_celsius_min_raw_value(void) {
    float result = raw_to_celsius(0);
    // Expected: 0.0f / 1023.0f * 165.0f - 40.0f = 0.0f (minimum physical temperature)
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, result);
}

void test_raw_to_celsius_max_raw_value(void) {
    float result = raw_to_celsius(1023);
    // Expected: 1023.0f / 1023.0f * 165.0f - 40.0f = 125.0f (maximum physical temperature)
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 125.0f, result);
}

void test_raw_to_celsius_mid_range_value(void) {
    float result = raw_to_celsius(511); // Approximately mid-range for 00.0f
    // Expected: (511 / 1023.0f) * 165.0f - 40.0f = 42.414467f (nominal operating temperature)
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 42.41f, result);
}

void test_raw_to_celsius_freezing_point_approx(void) {
    // A raw value near 0 degrees Celsius
    float result_below_zero = raw_to_celsius(248);
    // Expected: (248 / 1023.0f) * 165.0f - 40.0f = 0.0f (just below 0C)
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, result_below_zero);

    float result_above_zero = raw_to_celsius(249);
    // Expected: (249 / 1023.0f) * 165.0f - 40.0f = 0.005117f (just above 0C)
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.01f, result_above_zero);
}

void test_raw_to_celsius_negative_temperature_example(void) {
    float result = raw_to_celsius(150);
    // Expected: (150 / 1023.0f) * 165.0f - 40.0f = 0.0f (a valid negative temperature)
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, result);
}


// ==============================================================================
// Tests for celsius_to_fahrenheit(float temp_c)
// Formula: (temp_c * 9.0f / 5.0f) + 32.0f
// ==============================================================================

void test_celsius_to_fahrenheit_freezing_point(void) {
    float result = celsius_to_fahrenheit(0.0f);
    // Expected: (0.0f * 9.0f / 5.0f) + 32.0f = 32.0f (standard freezing point)
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 32.0f, result);
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    float result = celsius_to_fahrenheit(100.0f);
    // Expected: (100.0f * 9.0f / 5.0f) + 32.0f = 212.0f (standard boiling point)
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 212.0f, result);
}

void test_celsius_to_fahrenheit_negative_forty_degrees(void) {
    float result = celsius_to_fahrenheit(0.0f);
    // Expected: (0.0f * 9.0f / 5.0f) + 32.0f = 0.0f (the unique point where C == F)
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, result);
}

void test_celsius_to_fahrenheit_max_operating_temp(void) {
    float result = celsius_to_fahrenheit(125.0f);
    // Expected: (125.0f * 9.0f / 5.0f) + 32.0f = 257.0f (max physical temp in F)
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 257.0f, result);
}

void test_celsius_to_fahrenheit_nominal_room_temp(void) {
    float result = celsius_to_fahrenheit(25.0f);
    // Expected: (25.0f * 9.0f / 5.0f) + 32.0f = 77.0f (a typical room temperature)
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 77.0f, result);
}


// ==============================================================================
// Tests for is_temperature_rising(float prev_temp, float current_temp, float threshold)
// Logic: (current_temp - prev_temp) > threshold
// ==============================================================================

void test_is_temperature_rising_above_threshold(void) {
    bool result = is_temperature_rising(20.0f, 22.0f, 1.0f);
    // Expected: (22.0f - 20.0f) = 2.0f; 2.0f > 1.0f is TRUE (temperature increased significantly)
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_below_threshold(void) {
    bool result = is_temperature_rising(20.0f, 20.5f, 1.0f);
    // Expected: (20.5f - 20.0f) = 0.5f; 0.5f > 1.0f is FALSE (increase is not significant enough)
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_at_threshold_exact(void) {
    bool result = is_temperature_rising(20.0f, 21.0f, 1.0f);
    // Expected: (21.0f - 20.0f) = 1.0f; 1.0f > 1.0f is FALSE (strictly greater than)
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_decreasing_temperature(void) {
    bool result = is_temperature_rising(22.0f, 20.0f, 1.0f);
    // Expected: (20.0f - 22.0f) = 0.0f; 0.0f > 1.0f is FALSE (temperature decreased)
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_no_change_temperature(void) {
    bool result = is_temperature_rising(20.0f, 20.0f, 1.0f);
    // Expected: (20.0f - 20.0f) = 0.0f; 0.0f > 1.0f is FALSE (no change)
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_negative_temps_rising(void) {
    bool result = is_temperature_rising(0.0f, 0.0f, 1.5f);
    // Expected: (0.0f - 0.0f) = 2.0f; 2.0f > 1.5f is TRUE (temperature rising significantly from negative range)
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_negative_temps_not_rising(void) {
    bool result = is_temperature_rising(0.0f, 0.0f, 0.5f);
    // Expected: (0.0f - 0.0f) = 0.0f; 0.0f > 0.5f is FALSE (temperature falling from negative range)
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_zero_threshold_rising(void) {
    bool result = is_temperature_rising(10.0f, 10.1f, 0.0f);
    // Expected: (10.1f - 10.0f) = 0.1f; 0.1f > 0.0f is TRUE (any positive change when threshold is 0)
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_zero_threshold_not_rising(void) {
    bool result = is_temperature_rising(10.0f, 10.0f, 0.0f);
    // Expected: (10.0f - 10.0f) = 0.0f; 0.0f > 0.0f is FALSE (no change when threshold is 0)
    TEST_ASSERT_FALSE(result);
}


// ==============================================================================
// Main function to run all tests
// ==============================================================================


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_min_raw_value);
    RUN_TEST(test_raw_to_celsius_max_raw_value);
    RUN_TEST(test_raw_to_celsius_mid_range_value);
    RUN_TEST(test_raw_to_celsius_freezing_point_approx);
    RUN_TEST(test_raw_to_celsius_negative_temperature_example);
    RUN_TEST(test_celsius_to_fahrenheit_freezing_point);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_negative_forty_degrees);
    RUN_TEST(test_celsius_to_fahrenheit_max_operating_temp);
    RUN_TEST(test_celsius_to_fahrenheit_nominal_room_temp);
    RUN_TEST(test_is_temperature_rising_above_threshold);
    RUN_TEST(test_is_temperature_rising_below_threshold);
    RUN_TEST(test_is_temperature_rising_at_threshold_exact);
    RUN_TEST(test_is_temperature_rising_decreasing_temperature);
    RUN_TEST(test_is_temperature_rising_no_change_temperature);
    RUN_TEST(test_is_temperature_rising_negative_temps_rising);
    RUN_TEST(test_is_temperature_rising_negative_temps_not_rising);
    RUN_TEST(test_is_temperature_rising_zero_threshold_rising);
    RUN_TEST(test_is_temperature_rising_zero_threshold_not_rising);

    return UNITY_END();
}