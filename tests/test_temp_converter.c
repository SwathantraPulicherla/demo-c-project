#include "unity.h"
#include "temp_converter.h"

// Temperature tolerance for floating point comparisons
#define TEMP_TOLERANCE 0.1f

void setUp(void) {
    // No setup needed for these stateless functions
}

void tearDown(void) {
    // No teardown needed
}

//================================================================================================
// Tests for raw_to_celsius
//================================================================================================

void test_raw_to_celsius_MinRawValue_ReturnsMinTemp(void) {
    // The minimum raw value (0) should correspond to the minimum temperature (0.0f°C)
    float expected_temp = 0.0f;
    float actual_temp = raw_to_celsius(0);
    TEST_ASSERT_FLOAT_WITHIN(TEMP_TOLERANCE, expected_temp, actual_temp);
}

void test_raw_to_celsius_MaxRawValue_ReturnsMaxTemp(void) {
    // The maximum raw value (1023 for a 10-bit ADC) should correspond to the maximum temperature (125°C)
    float expected_temp = 125.0f;
    float actual_temp = raw_to_celsius(1023);
    TEST_ASSERT_FLOAT_WITHIN(TEMP_TOLERANCE, expected_temp, actual_temp);
}

void test_raw_to_celsius_MidRangeRawValue_ReturnsCorrectTemp(void) {
    // A raw value of 403 corresponds to approximately 25°C (room temperature)
    // (25 + 40) * 1023 / 165 = 403
    float expected_temp = 25.0f;
    float actual_temp = raw_to_celsius(403);
    TEST_ASSERT_FLOAT_WITHIN(TEMP_TOLERANCE, expected_temp, actual_temp);
}

void test_raw_to_celsius_RawValueForFreezing_ReturnsZeroCelsius(void) {
    // A raw value of 248 corresponds to approximately 0°C
    // (0 + 40) * 1023 / 165 = 248
    float expected_temp = 0.0f;
    float actual_temp = raw_to_celsius(248);
    TEST_ASSERT_FLOAT_WITHIN(TEMP_TOLERANCE, expected_temp, actual_temp);
}

void test_raw_to_celsius_RawValueForBoiling_Returns100Celsius(void) {
    // A raw value of 867 corresponds to approximately 100°C
    // (100 + 40) * 1023 / 165 = 867
    float expected_temp = 100.0f;
    float actual_temp = raw_to_celsius(867);
    TEST_ASSERT_FLOAT_WITHIN(TEMP_TOLERANCE, expected_temp, actual_temp);
}

//================================================================================================
// Tests for celsius_to_fahrenheit
//================================================================================================

void test_celsius_to_fahrenheit_FreezingPoint(void) {
    // 0°C should be 32°F
    float expected_temp_f = 32.0f;
    float actual_temp_f = celsius_to_fahrenheit(0.0f);
    TEST_ASSERT_FLOAT_WITHIN(TEMP_TOLERANCE, expected_temp_f, actual_temp_f);
}

void test_celsius_to_fahrenheit_BoilingPoint(void) {
    // 100°C should be 212°F
    float expected_temp_f = 212.0f;
    float actual_temp_f = celsius_to_fahrenheit(100.0f);
    TEST_ASSERT_FLOAT_WITHIN(TEMP_TOLERANCE, expected_temp_f, actual_temp_f);
}

void test_celsius_to_fahrenheit_RoomTemperature(void) {
    // 25°C should be 77°F
    float expected_temp_f = 77.0f;
    float actual_temp_f = celsius_to_fahrenheit(25.0f);
    TEST_ASSERT_FLOAT_WITHIN(TEMP_TOLERANCE, expected_temp_f, actual_temp_f);
}

void test_celsius_to_fahrenheit_SensorMinTemperature(void) {
    // 0.0f°C should be 0.0f°F
    float expected_temp_f = 0.0f;
    float actual_temp_f = celsius_to_fahrenheit(0.0f);
    TEST_ASSERT_FLOAT_WITHIN(TEMP_TOLERANCE, expected_temp_f, actual_temp_f);
}

void test_celsius_to_fahrenheit_SensorMaxTemperature(void) {
    // 125°C should be 257°F
    float expected_temp_f = 257.0f;
    float actual_temp_f = celsius_to_fahrenheit(125.0f);
    TEST_ASSERT_FLOAT_WITHIN(TEMP_TOLERANCE, expected_temp_f, actual_temp_f);
}

void test_celsius_to_fahrenheit_NegativeTemperature(void) {
    // 0.0f°C should be 14°F
    float expected_temp_f = 14.0f;
    float actual_temp_f = celsius_to_fahrenheit(0.0f);
    TEST_ASSERT_FLOAT_WITHIN(TEMP_TOLERANCE, expected_temp_f, actual_temp_f);
}

//================================================================================================
// Tests for is_temperature_rising
//================================================================================================

void test_is_temperature_rising_TempIsRisingAboveThreshold_ReturnsTrue(void) {
    // Change of +1.0 is greater than threshold of 0.5
    TEST_ASSERT_TRUE(is_temperature_rising(20.0f, 21.0f, 0.5f));
}

void test_is_temperature_rising_TempIsRisingBelowThreshold_ReturnsFalse(void) {
    // Change of +0.4 is not greater than threshold of 0.5
    TEST_ASSERT_FALSE(is_temperature_rising(20.0f, 20.4f, 0.5f));
}

void test_is_temperature_rising_TempIsRisingExactlyAtThreshold_ReturnsFalse(void) {
    // Change of +0.5 is not strictly greater than threshold of 0.5
    TEST_ASSERT_FALSE(is_temperature_rising(20.0f, 20.5f, 0.5f));
}

void test_is_temperature_rising_TempIsStable_ReturnsFalse(void) {
    // Change of 0.0 is not greater than threshold of 0.1
    TEST_ASSERT_FALSE(is_temperature_rising(25.0f, 25.0f, 0.1f));
}

void test_is_temperature_rising_TempIsFalling_ReturnsFalse(void) {
    // Negative change is not greater than positive threshold
    TEST_ASSERT_FALSE(is_temperature_rising(25.0f, 24.0f, 0.1f));
}

void test_is_temperature_rising_ZeroThresholdAndRising_ReturnsTrue(void) {
    // A small positive change is greater than a zero threshold
    TEST_ASSERT_TRUE(is_temperature_rising(20.0f, 20.1f, 0.0f));
}

void test_is_temperature_rising_ZeroThresholdAndStable_ReturnsFalse(void) {
    // Zero change is not greater than a zero threshold
    TEST_ASSERT_FALSE(is_temperature_rising(20.0f, 20.0f, 0.0f));
}

void test_is_temperature_rising_NegativeTempsRising_ReturnsTrue(void) {
    // Change from 0.0f to 0.0f is a rise of 1.0, which is > 0.5
    TEST_ASSERT_TRUE(is_temperature_rising(0.0f, 0.0f, 0.5f));
}

void test_is_temperature_rising_NegativeTempsFalling_ReturnsFalse(void) {
    // Change from 0.0f to 0.0f is a fall of 1.0, which is not > 0.5
    TEST_ASSERT_FALSE(is_temperature_rising(0.0f, 0.0f, 0.5f));
}

void test_is_temperature_rising_NegativeThresholdAndStable_ReturnsTrue(void) {
    // A stable temperature (change of 0.0) is greater than a negative threshold
    TEST_ASSERT_TRUE(is_temperature_rising(15.0f, 15.0f, 0.0f));
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_MinRawValue_ReturnsMinTemp);
    RUN_TEST(test_raw_to_celsius_MaxRawValue_ReturnsMaxTemp);
    RUN_TEST(test_raw_to_celsius_MidRangeRawValue_ReturnsCorrectTemp);
    RUN_TEST(test_raw_to_celsius_RawValueForFreezing_ReturnsZeroCelsius);
    RUN_TEST(test_raw_to_celsius_RawValueForBoiling_Returns100Celsius);
    RUN_TEST(test_celsius_to_fahrenheit_FreezingPoint);
    RUN_TEST(test_celsius_to_fahrenheit_BoilingPoint);
    RUN_TEST(test_celsius_to_fahrenheit_RoomTemperature);
    RUN_TEST(test_celsius_to_fahrenheit_SensorMinTemperature);
    RUN_TEST(test_celsius_to_fahrenheit_SensorMaxTemperature);
    RUN_TEST(test_celsius_to_fahrenheit_NegativeTemperature);
    RUN_TEST(test_is_temperature_rising_TempIsRisingAboveThreshold_ReturnsTrue);
    RUN_TEST(test_is_temperature_rising_TempIsRisingBelowThreshold_ReturnsFalse);
    RUN_TEST(test_is_temperature_rising_TempIsRisingExactlyAtThreshold_ReturnsFalse);
    RUN_TEST(test_is_temperature_rising_TempIsStable_ReturnsFalse);
    RUN_TEST(test_is_temperature_rising_TempIsFalling_ReturnsFalse);
    RUN_TEST(test_is_temperature_rising_ZeroThresholdAndRising_ReturnsTrue);
    RUN_TEST(test_is_temperature_rising_ZeroThresholdAndStable_ReturnsFalse);
    RUN_TEST(test_is_temperature_rising_NegativeTempsRising_ReturnsTrue);
    RUN_TEST(test_is_temperature_rising_NegativeTempsFalling_ReturnsFalse);
    RUN_TEST(test_is_temperature_rising_NegativeThresholdAndStable_ReturnsTrue);

    return UNITY_END();
}