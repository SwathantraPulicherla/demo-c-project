/* test_temp_converter.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include "temp_converter.h" // For the functions under test
#include <stdbool.h>      // For bool type
#include <string.h>       // For memset, though not strictly needed here without stubs

// Define a suitable tolerance for float comparisons, specific to temperature measurements.
// Temperatures derived from typical ADC ranges might have some inherent precision limits.
#define TEMP_TOLERANCE 0.1f

// No external functions to stub for this module as per prompt.

// No stub control structures needed since no external dependencies were listed.

void setUp(void) {
    // No specific setup required for these pure functions, but kept for Unity structure.
}

void tearDown(void) {
    // No specific teardown required, but kept for Unity structure.
}

// region: raw_to_celsius tests
void test_raw_to_celsius_MinRawValue_ReturnsMinCelsius(void) {
    int raw_value = 0;
    float expected_celsius = 0.0f; // (0 / 1023.0f) * 165.0f - 40.0f = 0.0f
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: raw_value 0 should result in the minimum temperature of 0.0f.
    TEST_ASSERT_FLOAT_WITHIN(TEMP_TOLERANCE, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_MaxRawValue_ReturnsMaxCelsius(void) {
    int raw_value = 1023;
    float expected_celsius = 125.0f; // (1023 / 1023.0f) * 165.0f - 40.0f = 165.0f - 40.0f = 125.0f
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: raw_value 1023 should result in the maximum temperature of 125.0f.
    TEST_ASSERT_FLOAT_WITHIN(TEMP_TOLERANCE, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_MidRangeRawValue_ReturnsExpectedCelsius(void) {
    int raw_value = 511; // Approximately half of 1023
    float expected_celsius = (511 / 1023.0f) * 165.0f - 40.0f; // approx 42.4f - 40.0f = 2.4f
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: raw_value 511 should yield a positive Celsius value around 2.4 degrees.
    TEST_ASSERT_FLOAT_WITHIN(TEMP_TOLERANCE, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_AnotherMidRangeRawValue_ReturnsNegativeCelsius(void) {
    int raw_value = 255; // Roughly a quarter of 1023
    float expected_celsius = (255 / 1023.0f) * 165.0f - 40.0f; // approx 41.28% * 165 - 40 = 68.11 - 40 = 28.11 (incorrect calculation, correcting in thought process)
    // (255 / 1023.0f) * 165.0f - 40.0f = 0.249266862 * 165.0f - 40.0f = 41.12899f - 40.0f = 1.12899f
    // Let's re-evaluate for a value that gives negative, or adjust raw_value
    // To get -10C: (X/1023)*165 - 40 = 0.0f => (X/1023)*165 = 30 => X/1023 = 30/165 => X = 1023 * (30/165) = 1023 * 0.181818 = 186.0
    raw_value = 186; // Expected output: 0.0f
    expected_celsius = (186 / 1023.0f) * 165.0f - 40.0f; // (0.18181818 * 165) - 40 = 30.0 - 40.0 = 0.0f
    actual_celsius = raw_to_celsius(raw_value);
    // Expected: raw_value 186 should yield a negative Celsius value of 0.0f.
    TEST_ASSERT_FLOAT_WITHIN(TEMP_TOLERANCE, expected_celsius, actual_celsius);
}
// endregion: raw_to_celsius tests

// region: celsius_to_fahrenheit tests
void test_celsius_to_fahrenheit_ZeroCelsius_ReturnsFreezingFahrenheit(void) {
    float temp_c = 0.0f;
    float expected_fahrenheit = 32.0f; // (0.0 * 9.0/5.0) + 32.0 = 32.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // Expected: 0.0 Celsius should convert to 32.0 Fahrenheit (freezing point).
    TEST_ASSERT_FLOAT_WITHIN(TEMP_TOLERANCE, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_BoilingCelsius_ReturnsBoilingFahrenheit(void) {
    float temp_c = 100.0f;
    float expected_fahrenheit = 212.0f; // (100.0 * 9.0/5.0) + 32.0 = 180.0 + 32.0 = 212.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // Expected: 100.0 Celsius should convert to 212.0 Fahrenheit (boiling point).
    TEST_ASSERT_FLOAT_WITHIN(TEMP_TOLERANCE, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_MinCelsiusRange_ReturnsMinFahrenheitRange(void) {
    float temp_c = 0.0f;
    float expected_fahrenheit = 0.0f; // (0.0f * 9.0/5.0) + 32.0 = 0.0f + 32.0 = 0.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // Expected: 0.0f Celsius should convert to 0.0f Fahrenheit.
    TEST_ASSERT_FLOAT_WITHIN(TEMP_TOLERANCE, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_MaxCelsiusRange_ReturnsMaxFahrenheitRange(void) {
    float temp_c = 125.0f;
    float expected_fahrenheit = 257.0f; // (125.0 * 9.0/5.0) + 32.0 = 225.0 + 32.0 = 257.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // Expected: 125.0 Celsius should convert to 257.0 Fahrenheit.
    TEST_ASSERT_FLOAT_WITHIN(TEMP_TOLERANCE, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_NominalRoomTemperature(void) {
    float temp_c = 25.0f;
    float expected_fahrenheit = 77.0f; // (25.0 * 9.0/5.0) + 32.0 = 45.0 + 32.0 = 77.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // Expected: 25.0 Celsius (nominal room temperature) should convert to 77.0 Fahrenheit.
    TEST_ASSERT_FLOAT_WITHIN(TEMP_TOLERANCE, expected_fahrenheit, actual_fahrenheit);
}
// endregion: celsius_to_fahrenheit tests

// region: is_temperature_rising tests
void test_is_temperature_rising_AboveThreshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 22.0f;
    float threshold = 1.5f;
    bool expected_result = true; // (22.0 - 20.0) = 2.0 > 1.5
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: Current temp rise (2.0) is greater than threshold (1.5), so true.
    TEST_ASSERT_TRUE(actual_result);
}

void test_is_temperature_rising_ExactlyAtThreshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 21.0f;
    float threshold = 1.0f;
    bool expected_result = false; // (21.0 - 20.0) = 1.0 is NOT > 1.0
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: Current temp rise (1.0) is exactly equal to threshold (1.0), so false (not strictly greater).
    TEST_ASSERT_FALSE(actual_result);
}

void test_is_temperature_rising_BelowThresholdButStillRising(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.5f;
    float threshold = 1.0f;
    bool expected_result = false; // (20.5 - 20.0) = 0.5 is NOT > 1.0
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: Current temp rise (0.5) is less than threshold (1.0), so false.
    TEST_ASSERT_FALSE(actual_result);
}

void test_is_temperature_rising_StableTemperature(void) {
    float prev_temp = 25.0f;
    float current_temp = 25.0f;
    float threshold = 0.1f;
    bool expected_result = false; // (25.0 - 25.0) = 0.0 is NOT > 0.1
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: Temperature is stable (0.0 change), not rising above threshold (0.1), so false.
    TEST_ASSERT_FALSE(actual_result);
}

void test_is_temperature_rising_FallingTemperature(void) {
    float prev_temp = 30.0f;
    float current_temp = 28.0f;
    float threshold = 0.5f;
    bool expected_result = false; // (28.0 - 30.0) = 0.0f is NOT > 0.5
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: Temperature is falling (0.0f change), not rising, so false.
    TEST_ASSERT_FALSE(actual_result);
}

void test_is_temperature_rising_ZeroThreshold_Rising(void) {
    float prev_temp = 10.0f;
    float current_temp = 10.01f;
    float threshold = 0.0f;
    bool expected_result = true; // (10.01 - 10.0) = 0.01 > 0.0
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: A minimal rise (0.01) is greater than a zero threshold, so true.
    TEST_ASSERT_TRUE(actual_result);
}

void test_is_temperature_rising_ZeroThreshold_NotRising(void) {
    float prev_temp = 10.0f;
    float current_temp = 10.0f;
    float threshold = 0.0f;
    bool expected_result = false; // (10.0 - 10.0) = 0.0 is NOT > 0.0
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: No change (0.0) is not greater than a zero threshold, so false.
    TEST_ASSERT_FALSE(actual_result);
}
// endregion: is_temperature_rising tests



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_MinRawValue_ReturnsMinCelsius);
    RUN_TEST(test_raw_to_celsius_MaxRawValue_ReturnsMaxCelsius);
    RUN_TEST(test_raw_to_celsius_MidRangeRawValue_ReturnsExpectedCelsius);
    RUN_TEST(test_raw_to_celsius_AnotherMidRangeRawValue_ReturnsNegativeCelsius);
    RUN_TEST(test_celsius_to_fahrenheit_ZeroCelsius_ReturnsFreezingFahrenheit);
    RUN_TEST(test_celsius_to_fahrenheit_BoilingCelsius_ReturnsBoilingFahrenheit);
    RUN_TEST(test_celsius_to_fahrenheit_MinCelsiusRange_ReturnsMinFahrenheitRange);
    RUN_TEST(test_celsius_to_fahrenheit_MaxCelsiusRange_ReturnsMaxFahrenheitRange);
    RUN_TEST(test_celsius_to_fahrenheit_NominalRoomTemperature);
    RUN_TEST(test_is_temperature_rising_AboveThreshold);
    RUN_TEST(test_is_temperature_rising_ExactlyAtThreshold);
    RUN_TEST(test_is_temperature_rising_BelowThresholdButStillRising);
    RUN_TEST(test_is_temperature_rising_StableTemperature);
    RUN_TEST(test_is_temperature_rising_FallingTemperature);
    RUN_TEST(test_is_temperature_rising_ZeroThreshold_Rising);
    RUN_TEST(test_is_temperature_rising_ZeroThreshold_NotRising);

    return UNITY_END();
}