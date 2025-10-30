/* test_temp_converter.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdbool.h> // For bool type

// Include the header for the module under test
// This header is necessary to get the function prototypes for the functions being tested.
#include "temp_converter.h" 

// No external functions to stub for this module as per prompt instructions.

// Define a common tolerance for float comparisons, particularly for temperatures
// A tolerance of 0.1f is appropriate for embedded temperature measurements.
#define TEMPERATURE_TOLERANCE 0.1f

/**
 * @brief Setup function for each test.
 *        Initializes any test-specific state or stubs.
 */
void setUp(void) {
    // No specific setup required as there are no stubs or global state in temp_converter.c
}

/**
 * @brief Teardown function for each test.
 *        Cleans up any test-specific state or stubs.
 */
void tearDown(void) {
    // No specific teardown required
}

// ====================================================================
// Tests for raw_to_celsius(int raw_value)
// Formula: (raw_value / 1023.0f) * 165.0f - 40.0f
// Assumed input raw_value range: 00.0f (e.g., from a 10-bit ADC)
// Calculated output Celsius range: 0.0f to 125.0f
// ====================================================================

/**
 * @brief Test raw_to_celsius with the minimum possible raw ADC value (0).
 *        Expected output: 0.0f Celsius.
 */
void test_raw_to_celsius_MinRawValue(void) {
    float result;
    // Input: ADC raw value at minimum (0)
    result = raw_to_celsius(0);
    // Expected: (0 / 1023.0f) * 165.0f - 40.0f = 0.0f
    TEST_ASSERT_FLOAT_WITHIN(TEMPERATURE_TOLERANCE, 0.0f, result); // Validate conversion at minimum ADC value
}

/**
 * @brief Test raw_to_celsius with the maximum possible raw ADC value (1023).
 *        Expected output: 125.0f Celsius.
 */
void test_raw_to_celsius_MaxRawValue(void) {
    float result;
    // Input: ADC raw value at maximum (1023)
    result = raw_to_celsius(1023);
    // Expected: (1023 / 1023.0f) * 165.0f - 40.0f = 165.0f - 40.0f = 125.0f
    TEST_ASSERT_FLOAT_WITHIN(TEMPERATURE_TOLERANCE, 125.0f, result); // Validate conversion at maximum ADC value
}

/**
 * @brief Test raw_to_celsius with a typical mid-range raw ADC value.
 *        Expected output: approximately 42.4175f Celsius.
 */
void test_raw_to_celsius_MidRangeRawValue(void) {
    float result;
    // Input: ADC raw value in mid-range (e.g., 511, slightly less than half of 1023)
    result = raw_to_celsius(511);
    // Expected: (511 / 1023.0f) * 165.0f - 40.0f = 0.499511f * 165.0f - 40.0f = 82.4193f - 40.0f = 42.4193f
    TEST_ASSERT_FLOAT_WITHIN(TEMPERATURE_TOLERANCE, 42.4193f, result); // Validate conversion for a typical mid-range ADC value
}

/**
 * @brief Test raw_to_celsius for a raw value that should result in 0 degrees Celsius.
 *        Expected output: 0.0f Celsius.
 */
void test_raw_to_celsius_SpecificZeroCelsius(void) {
    float result;
    // Input: Raw value calculated to produce approximately 0 degrees Celsius
    // Calculation: 0 = (raw / 1023.0f) * 165.0f - 40.0f => raw = (40.0f * 1023.0f) / 165.0f = 248.0f
    result = raw_to_celsius(248);
    // Expected: Approximately 0.0f Celsius
    TEST_ASSERT_FLOAT_WITHIN(TEMPERATURE_TOLERANCE, 0.0f, result); // Validate conversion to 0 degrees Celsius
}

/**
 * @brief Test raw_to_celsius for a raw value that should result in a negative Celsius temperature.
 *        Expected output: 0.0f Celsius.
 */
void test_raw_to_celsius_SpecificNegativeCelsius(void) {
    float result;
    // Input: Raw value for 0.0f degrees Celsius.
    // Calculation: 0.0f = (raw / 1023.0f) * 165.0f - 40.0f => raw = (30.0f * 1023.0f) / 165.0f = 186.0f
    result = raw_to_celsius(186);
    // Expected: Approximately 0.0f Celsius
    TEST_ASSERT_FLOAT_WITHIN(TEMPERATURE_TOLERANCE, 0.0f, result); // Validate conversion to a negative Celsius value
}

// ====================================================================
// Tests for celsius_to_fahrenheit(float temp_c)
// Formula: (temp_c * 9.0f / 5.0f) + 32.0f
// Expected input temp_c range: 0.0f to 125.0f (derived from raw_to_celsius function)
// ====================================================================

/**
 * @brief Test celsius_to_fahrenheit with the minimum valid Celsius temperature.
 *        Expected output: 0.0f Fahrenheit.
 */
void test_celsius_to_fahrenheit_MinCelsius(void) {
    float result;
    // Input: Minimum Celsius value (0.0f)
    result = celsius_to_fahrenheit(0.0f);
    // Expected: (0.0f * 9.0f / 5.0f) + 32.0f = 0.0f + 32.0f = 0.0f
    TEST_ASSERT_FLOAT_WITHIN(TEMPERATURE_TOLERANCE, 0.0f, result); // Validate conversion at minimum temperature (-40C is -40F)
}

/**
 * @brief Test celsius_to_fahrenheit with the maximum valid Celsius temperature.
 *        Expected output: 257.0f Fahrenheit.
 */
void test_celsius_to_fahrenheit_MaxCelsius(void) {
    float result;
    // Input: Maximum Celsius value (125.0f)
    result = celsius_to_fahrenheit(125.0f);
    // Expected: (125.0f * 9.0f / 5.0f) + 32.0f = 225.0f + 32.0f = 257.0f
    TEST_ASSERT_FLOAT_WITHIN(TEMPERATURE_TOLERANCE, 257.0f, result); // Validate conversion at maximum temperature
}

/**
 * @brief Test celsius_to_fahrenheit with 0 degrees Celsius.
 *        Expected output: 32.0f Fahrenheit.
 */
void test_celsius_to_fahrenheit_ZeroCelsius(void) {
    float result;
    // Input: Zero degrees Celsius (freezing point of water)
    result = celsius_to_fahrenheit(0.0f);
    // Expected: (0.0f * 9.0f / 5.0f) + 32.0f = 32.0f
    TEST_ASSERT_FLOAT_WITHIN(TEMPERATURE_TOLERANCE, 32.0f, result); // Validate conversion for 0 degrees Celsius
}

/**
 * @brief Test celsius_to_fahrenheit with a typical room temperature in Celsius.
 *        Expected output: 77.0f Fahrenheit.
 */
void test_celsius_to_fahrenheit_RoomTemperature(void) {
    float result;
    // Input: Typical room temperature (25.0f Celsius)
    result = celsius_to_fahrenheit(25.0f);
    // Expected: (25.0f * 9.0f / 5.0f) + 32.0f = 45.0f + 32.0f = 77.0f
    TEST_ASSERT_FLOAT_WITHIN(TEMPERATURE_TOLERANCE, 77.0f, result); // Validate conversion for a common room temperature
}

/**
 * @brief Test celsius_to_fahrenheit with a negative Celsius temperature.
 *        Expected output: 14.0f Fahrenheit.
 */
void test_celsius_to_fahrenheit_NegativeCelsius(void) {
    float result;
    // Input: Negative Celsius temperature (0.0f)
    result = celsius_to_fahrenheit(0.0f);
    // Expected: (0.0f * 9.0f / 5.0f) + 32.0f = 0.0f + 32.0f = 14.0f
    TEST_ASSERT_FLOAT_WITHIN(TEMPERATURE_TOLERANCE, 14.0f, result); // Validate conversion for a negative Celsius value
}

// ====================================================================
// Tests for is_temperature_rising(float prev_temp, float current_temp, float threshold)
// Logic: (current_temp - prev_temp) > threshold
// ====================================================================

/**
 * @brief Test is_temperature_rising when the temperature difference clearly exceeds the threshold.
 *        Expected output: true.
 */
void test_is_temperature_rising_IsRising(void) {
    bool result;
    // Input: Current temp significantly above previous temp, exceeding threshold
    result = is_temperature_rising(20.0f, 21.0f, 0.5f);
    // Expected: (21.0f - 20.0f) > 0.5f => 1.0f > 0.5f => TRUE
    TEST_ASSERT_TRUE(result); // Validate that temperature is rising when difference exceeds threshold
}

/**
 * @brief Test is_temperature_rising when the temperature difference exactly equals the threshold.
 *        Expected output: false (due to strict inequality `>`).
 */
void test_is_temperature_rising_NotRising_EqualThreshold(void) {
    bool result;
    // Input: Current temp such that difference equals threshold
    result = is_temperature_rising(20.0f, 20.5f, 0.5f);
    // Expected: (20.5f - 20.0f) > 0.5f => 0.5f > 0.5f => FALSE (condition is strictly greater than)
    TEST_ASSERT_FALSE(result); // Validate that temperature is not rising when difference equals threshold
}

/**
 * @brief Test is_temperature_rising when the temperature difference is positive but below the threshold.
 *        Expected output: false.
 */
void test_is_temperature_rising_NotRising_BelowThreshold(void) {
    bool result;
    // Input: Current temp slightly above previous temp, but difference is below threshold
    result = is_temperature_rising(20.0f, 20.4f, 0.5f);
    // Expected: (20.4f - 20.0f) > 0.5f => 0.4f > 0.5f => FALSE
    TEST_ASSERT_FALSE(result); // Validate that temperature is not rising when difference is below threshold
}

/**
 * @brief Test is_temperature_rising when the temperature is falling.
 *        Expected output: false.
 */
void test_is_temperature_rising_FallingTemperature(void) {
    bool result;
    // Input: Current temp is below previous temp (temperature is falling)
    result = is_temperature_rising(25.0f, 24.0f, 0.5f);
    // Expected: (24.0f - 25.0f) > 0.5f => 0.0f > 0.5f => FALSE
    TEST_ASSERT_FALSE(result); // Validate that temperature is not rising when it is falling
}

/**
 * @brief Test is_temperature_rising when the temperature is perfectly stable.
 *        Expected output: false.
 */
void test_is_temperature_rising_StableTemperature(void) {
    bool result;
    // Input: Current temp is same as previous temp (temperature is stable)
    result = is_temperature_rising(22.0f, 22.0f, 0.1f);
    // Expected: (22.0f - 22.0f) > 0.1f => 0.0f > 0.1f => FALSE
    TEST_ASSERT_FALSE(result); // Validate that temperature is not rising when it is perfectly stable
}

/**
 * @brief Test is_temperature_rising with a zero threshold, and the temperature is rising.
 *        Expected output: true.
 */
void test_is_temperature_rising_ZeroThreshold_Rising(void) {
    bool result;
    // Input: Current temp slightly above previous, with zero threshold
    result = is_temperature_rising(10.0f, 10.01f, 0.0f);
    // Expected: (10.01f - 10.0f) > 0.0f => 0.01f > 0.0f => TRUE
    TEST_ASSERT_TRUE(result); // Validate rising with a zero threshold for any positive change
}

/**
 * @brief Test is_temperature_rising with a zero threshold, and the temperature is stable.
 *        Expected output: false.
 */
void test_is_temperature_rising_ZeroThreshold_NotRising(void) {
    bool result;
    // Input: Current temp same as previous, with zero threshold
    result = is_temperature_rising(10.0f, 10.0f, 0.0f);
    // Expected: (10.0f - 10.0f) > 0.0f => 0.0f > 0.0f => FALSE
    TEST_ASSERT_FALSE(result); // Validate not rising with a zero threshold when temperature is stable
}


// ====================================================================
// Main Unity Test Runner
// ====================================================================


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_MinRawValue);
    RUN_TEST(test_raw_to_celsius_MaxRawValue);
    RUN_TEST(test_raw_to_celsius_MidRangeRawValue);
    RUN_TEST(test_raw_to_celsius_SpecificZeroCelsius);
    RUN_TEST(test_raw_to_celsius_SpecificNegativeCelsius);
    RUN_TEST(test_celsius_to_fahrenheit_MinCelsius);
    RUN_TEST(test_celsius_to_fahrenheit_MaxCelsius);
    RUN_TEST(test_celsius_to_fahrenheit_ZeroCelsius);
    RUN_TEST(test_celsius_to_fahrenheit_RoomTemperature);
    RUN_TEST(test_celsius_to_fahrenheit_NegativeCelsius);
    RUN_TEST(test_is_temperature_rising_IsRising);
    RUN_TEST(test_is_temperature_rising_NotRising_EqualThreshold);
    RUN_TEST(test_is_temperature_rising_NotRising_BelowThreshold);
    RUN_TEST(test_is_temperature_rising_FallingTemperature);
    RUN_TEST(test_is_temperature_rising_StableTemperature);
    RUN_TEST(test_is_temperature_rising_ZeroThreshold_Rising);
    RUN_TEST(test_is_temperature_rising_ZeroThreshold_NotRising);

    return UNITY_END();
}