#include "unity.h"
#include "temp_sensor.h"
#include "temp_converter.h" // Needed for the stubbed function raw_to_celsius
#include <stdlib.h> // Needed for rand() in read_temperature_raw

// --- Stub Implementations for raw_to_celsius ---

// Static variables to control and inspect the stub behavior
static int raw_to_celsius_CalledCount;
static int raw_to_celsius_InputRawValue;
static float raw_to_celsius_Return;

// Stub function for raw_to_celsius
float raw_to_celsius(int raw_value) {
    raw_to_celsius_CalledCount++;
    raw_to_celsius_InputRawValue = raw_value; // Capture the input for verification
    return raw_to_celsius_Return;
}

// --- setUp and tearDown functions ---

void setUp(void) {
    // Reset stub state before each test
    raw_to_celsius_CalledCount = 0;
    raw_to_celsius_InputRawValue = 0;
    raw_to_celsius_Return = 0.0f;
    // Note: rand() behavior is not reset here as it's non-deterministic
    // and tests for read_temperature_raw only check range.
}

void tearDown(void) {
    // Reset stub state after each test to ensure test isolation
    raw_to_celsius_CalledCount = 0;
    raw_to_celsius_InputRawValue = 0;
    raw_to_celsius_Return = 0.0f;
}

// --- Test Cases for int read_temperature_raw ---

void test_read_temperature_raw_returns_within_valid_range(void) {
    // Since read_temperature_raw uses rand(), we can only assert that the return
    // value is within the expected range [0, 1023].
    // Run multiple times to increase confidence due to non-deterministic nature.
    for (int i = 0; i < 10; i++) {
        int raw_temp = read_temperature_raw();
        TEST_ASSERT_TRUE(raw_temp >= 0);
        TEST_ASSERT_TRUE(raw_temp <= 1023); // rand() % 1024 generates values from 0 to 1023
    }
}

// --- Test Cases for bool validate_temperature_range ---

void test_validate_temperature_range_valid_normal(void) {
    TEST_ASSERT_TRUE(validate_temperature_range(25.0f));
}

void test_validate_temperature_range_valid_min_edge(void) {
    TEST_ASSERT_TRUE(validate_temperature_range(-40.0f));
}

void test_validate_temperature_range_valid_max_edge(void) {
    TEST_ASSERT_TRUE(validate_temperature_range(125.0f));
}

void test_validate_temperature_range_invalid_below_min(void) {
    TEST_ASSERT_FALSE(validate_temperature_range(-40.1f));
}

void test_validate_temperature_range_invalid_above_max(void) {
    TEST_ASSERT_FALSE(validate_temperature_range(125.1f));
}

void test_validate_temperature_range_invalid_far_below_min(void) {
    TEST_ASSERT_FALSE(validate_temperature_range(-100.0f));
}

void test_validate_temperature_range_invalid_far_above_max(void) {
    TEST_ASSERT_FALSE(validate_temperature_range(200.0f));
}

// --- Test Cases for const char* check_temperature_status (covering else if branches) ---

void test_check_temperature_status_critical_above_120(void) {
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(120.01f)); // Just above 120
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(125.0f));  // Max valid, still critical
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(150.0f));
}

void test_check_temperature_status_hot_between_85_and_120_inclusive(void) {
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(85.0f));   // Lower edge for HOT (>= 85)
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(100.0f));  // Normal HOT range
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(120.0f));  // Upper edge for HOT (<= 120, because not > 120)
}

void test_check_temperature_status_cold_below_minus10(void) {
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(-10.1f)); // Just below -10
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(-25.0f));
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(-40.0f)); // Min valid, still cold
}

void test_check_temperature_status_normal_between_minus10_and_85(void) {
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(-10.0f)); // Lower edge for NORMAL (>= -10)
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(0.0f));
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(25.0f));
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(84.9f)); // Upper edge for NORMAL (< 85)
}

// --- Test Cases for float get_temperature_celsius ---

void test_get_temperature_celsius_calls_dependencies_and_converts(void) {
    // Arrange: Configure stub return value
    raw_to_celsius_Return = 50.5f;

    // Act: Call the function under test
    float result = get_temperature_celsius();

    // Assert: Verify stub interaction and final result
    TEST_ASSERT_EQUAL(1, raw_to_celsius_CalledCount);
    // The raw value input to the stub should be within the expected range of read_temperature_raw
    TEST_ASSERT_TRUE(raw_to_celsius_InputRawValue >= 0);
    TEST_ASSERT_TRUE(raw_to_celsius_InputRawValue <= 1023);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 50.5f, result);
}

void test_get_temperature_celsius_returns_different_value_with_different_stub_return(void) {
    // Arrange: Configure stub return value for a different scenario
    raw_to_celsius_Return = -15.0f;

    // Act: Call the function under test
    float result = get_temperature_celsius();

    // Assert: Verify stub interaction and final result
    TEST_ASSERT_EQUAL(1, raw_to_celsius_CalledCount);
    TEST_ASSERT_TRUE(raw_to_celsius_InputRawValue >= 0);
    TEST_ASSERT_TRUE(raw_to_celsius_InputRawValue <= 1023);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, -15.0f, result);
}

// --- Main function for running tests ---



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_read_temperature_raw_returns_within_valid_range);
    RUN_TEST(test_validate_temperature_range_valid_normal);
    RUN_TEST(test_validate_temperature_range_valid_min_edge);
    RUN_TEST(test_validate_temperature_range_valid_max_edge);
    RUN_TEST(test_validate_temperature_range_invalid_below_min);
    RUN_TEST(test_validate_temperature_range_invalid_above_max);
    RUN_TEST(test_validate_temperature_range_invalid_far_below_min);
    RUN_TEST(test_validate_temperature_range_invalid_far_above_max);
    RUN_TEST(test_check_temperature_status_critical_above_120);
    RUN_TEST(test_check_temperature_status_hot_between_85_and_120_inclusive);
    RUN_TEST(test_check_temperature_status_cold_below_minus10);
    RUN_TEST(test_check_temperature_status_normal_between_minus10_and_85);
    RUN_TEST(test_get_temperature_celsius_calls_dependencies_and_converts);
    RUN_TEST(test_get_temperature_celsius_returns_different_value_with_different_stub_return);

    return UNITY_END();
}