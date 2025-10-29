/* test_temp_converter.c – Auto-generated Expert Unity Tests */

#include "unity.h"
#include "temp_converter.h" // Include the header of the module under test
#include <stdbool.h>        // For bool type

// No external functions to stub as per prompt, so no stub control structures or implementations are needed.

void setUp(void) {
    // No specific setup needed for this module, as there is no global state or external dependencies to mock.
}

void tearDown(void) {
    // No specific tear down needed for this module, as there is no global state or external dependencies to clean up.
}

// --- Test cases for raw_to_celsius ---

void test_raw_to_celsius_MinRawValue(void) {
    int raw_value = 0;
    float expected_celsius = 0.0f;
    float actual_celsius;

    actual_celsius = raw_to_celsius(raw_value);

    // Expected: 0 raw value converts to 0.0f Celsius as per formula (0/1023)*165 - 40.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_MaxRawValue(void) {
    int raw_value = 1023;
    float expected_celsius = 125.0f;
    float actual_celsius;

    actual_celsius = raw_to_celsius(raw_value);

    // Expected: 1023 raw value converts to 125.0f Celsius as per formula (1023/1023)*165 - 40.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_MidRangeRawValue(void) {
    int raw_value = 511; // Approximately mid-range for a 10-bit ADC (00.0f)
    float expected_celsius = 42.41935f; // (511 / 1023.0f) * 165.0f - 40.0f
    float actual_celsius;

    actual_celsius = raw_to_celsius(raw_value);

    // Expected: 511 raw value converts to approximately 42.42f Celsius based on formula.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_QuarterRangeRawValue(void) {
    int raw_value = 256; // Approximately quarter-range
    float expected_celsius = 0.997067f; // (256 / 1023.0f) * 165.0f - 40.0f
    float actual_celsius;

    actual_celsius = raw_to_celsius(raw_value);

    // Expected: 256 raw value converts to approximately 1.0f Celsius.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_ThreeQuarterRangeRawValue(void) {
    int raw_value = 768; // Approximately three-quarter-range
    float expected_celsius = 83.842629f; // (768 / 1023.0f) * 165.0f - 40.0f
    float actual_celsius;

    actual_celsius = raw_to_celsius(raw_value);

    // Expected: 768 raw value converts to approximately 83.84f Celsius.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

// --- Test cases for celsius_to_fahrenheit ---

void test_celsius_to_fahrenheit_MinCelsius(void) {
    float temp_c = 0.0f; // Minimum valid Celsius temperature from raw_to_celsius range
    float expected_fahrenheit = 0.0f; // (0.0f * 9/5) + 32 = 0.0f
    float actual_fahrenheit;

    actual_fahrenheit = celsius_to_fahrenheit(temp_c);

    // Expected: 0.0f Celsius is 0.0f Fahrenheit.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_MaxCelsius(void) {
    float temp_c = 125.0f; // Maximum valid Celsius temperature from raw_to_celsius range
    float expected_fahrenheit = 257.0f; // (125 * 9/5) + 32 = 257
    float actual_fahrenheit;

    actual_fahrenheit = celsius_to_fahrenheit(temp_c);

    // Expected: 125.0f Celsius is 257.0f Fahrenheit.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_FreezingPoint(void) {
    float temp_c = 0.0f;
    float expected_fahrenheit = 32.0f; // (0 * 9/5) + 32 = 32
    float actual_fahrenheit;

    actual_fahrenheit = celsius_to_fahrenheit(temp_c);

    // Expected: 0.0f Celsius is 32.0f Fahrenheit (water freezing point).
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_BoilingPoint(void) {
    float temp_c = 100.0f;
    float expected_fahrenheit = 212.0f; // (100 * 9/5) + 32 = 212
    float actual_fahrenheit;

    actual_fahrenheit = celsius_to_fahrenheit(temp_c);

    // Expected: 100.0f Celsius is 212.0f Fahrenheit (water boiling point).
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_RoomTemp(void) {
    float temp_c = 25.0f;
    float expected_fahrenheit = 77.0f; // (25 * 9/5) + 32 = 77
    float actual_fahrenheit;

    actual_fahrenheit = celsius_to_fahrenheit(temp_c);

    // Expected: 25.0f Celsius is 77.0f Fahrenheit (typical room temperature).
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit);
}

// --- Test cases for is_temperature_rising ---

void test_is_temperature_rising_TrueRising(void) {
    float prev_temp = 20.0f;
    float current_temp = 21.0f;
    float threshold = 0.5f; // A typical small threshold for detecting change
    bool actual_result;

    actual_result = is_temperature_rising(prev_temp, current_temp, threshold);

    // Expected: Temperature difference (1.0f) is greater than threshold (0.5f), so it's rising.
    TEST_ASSERT_TRUE(actual_result);
}

void test_is_temperature_rising_FalseNotRisingBelowThreshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.4f;
    float threshold = 0.5f;
    bool actual_result;

    actual_result = is_temperature_rising(prev_temp, current_temp, threshold);

    // Expected: Temperature difference (0.4f) is not greater than threshold (0.5f), so not rising significantly.
    TEST_ASSERT_FALSE(actual_result);
}

void test_is_temperature_rising_FalseNotRisingExactlyThreshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.5f;
    float threshold = 0.5f;
    bool actual_result;

    actual_result = is_temperature_rising(prev_temp, current_temp, threshold);

    // Expected: Temperature difference (0.5f) is not strictly greater than threshold (0.5f), so not rising.
    TEST_ASSERT_FALSE(actual_result);
}

void test_is_temperature_rising_FalseFalling(void) {
    float prev_temp = 20.0f;
    float current_temp = 19.0f;
    float threshold = 0.5f;
    bool actual_result;

    actual_result = is_temperature_rising(prev_temp, current_temp, threshold);

    // Expected: Temperature difference (0.0f) is not greater than threshold (0.5f), as temperature is falling.
    TEST_ASSERT_FALSE(actual_result);
}

void test_is_temperature_rising_FalseZeroDifference(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.0f;
    float threshold = 0.5f;
    bool actual_result;

    actual_result = is_temperature_rising(prev_temp, current_temp, threshold);

    // Expected: Temperature difference (0.0f) is not greater than threshold (0.5f), no change.
    TEST_ASSERT_FALSE(actual_result);
}



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_MinRawValue);
    RUN_TEST(test_raw_to_celsius_MaxRawValue);
    RUN_TEST(test_raw_to_celsius_MidRangeRawValue);
    RUN_TEST(test_raw_to_celsius_QuarterRangeRawValue);
    RUN_TEST(test_raw_to_celsius_ThreeQuarterRangeRawValue);
    RUN_TEST(test_celsius_to_fahrenheit_MinCelsius);
    RUN_TEST(test_celsius_to_fahrenheit_MaxCelsius);
    RUN_TEST(test_celsius_to_fahrenheit_FreezingPoint);
    RUN_TEST(test_celsius_to_fahrenheit_BoilingPoint);
    RUN_TEST(test_celsius_to_fahrenheit_RoomTemp);
    RUN_TEST(test_is_temperature_rising_TrueRising);
    RUN_TEST(test_is_temperature_rising_FalseNotRisingBelowThreshold);
    RUN_TEST(test_is_temperature_rising_FalseNotRisingExactlyThreshold);
    RUN_TEST(test_is_temperature_rising_FalseFalling);
    RUN_TEST(test_is_temperature_rising_FalseZeroDifference);

    return UNITY_END();
}