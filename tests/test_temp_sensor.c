#include "unity.h"
#include "temp_sensor.h"
#include "temp_converter.h" // Required for the stubbed function
#include <stdlib.h> // Required for rand() and srand()

// --- Stub Implementations ---

// Stub variables for raw_to_celsius
static int raw_to_celsius_CallCount;
static float raw_to_celsius_Return;
static int raw_to_celsius_LastRaw;

// Stub function definition for raw_to_celsius
float raw_to_celsius(int raw) {
    raw_to_celsius_CallCount++;
    raw_to_celsius_LastRaw = raw; // Store the last raw value passed
    return raw_to_celsius_Return;
}

// Helper function to configure the stub's return value
void set_raw_to_celsius_return(float value) {
    raw_to_celsius_Return = value;
}

// Helper function to get the stub's call count
int get_raw_to_celsius_call_count(void) {
    return raw_to_celsius_CallCount;
}

// Helper function to get the last raw value passed to the stub
int get_raw_to_celsius_last_raw(void) {
    return raw_to_celsius_LastRaw;
}

// Function to reset all stub states
void reset_raw_to_celsius_stub(void) {
    raw_to_celsius_CallCount = 0;
    raw_to_celsius_Return = 0.0f; // Default return value
    raw_to_celsius_LastRaw = 0;
}

// --- Test Setup and Teardown ---

void setUp(void) {
    // Initialize or reset any mocks/stubs before each test
    reset_raw_to_celsius_stub();
    // Seed rand for predictable behavior of read_temperature_raw()
    // For unit tests, it's often useful to have deterministic pseudo-random numbers.
    srand(1);
}

void tearDown(void) {
    // Clean up after each test, reset stub state again
    reset_raw_to_celsius_stub();
}

// --- Test Cases for read_temperature_raw ---

void test_read_temperature_raw_returns_within_valid_range(void) {
    int raw_temp = read_temperature_raw();
    TEST_ASSERT_TRUE_MESSAGE(raw_temp >= 0, "Raw temperature should be non-negative");
    TEST_ASSERT_TRUE_MESSAGE(raw_temp < 1024, "Raw temperature should be less than 1024");
}

void test_read_temperature_raw_returns_different_values(void) {
    int raw_temp1 = read_temperature_raw();
    int raw_temp2 = read_temperature_raw();
    // Due to srand(1) in setUp, this sequence is deterministic.
    // For srand(1), the first call to rand() usually gives 16807, second 282475249.
    // % 1024 will make them different in most cases.
    TEST_ASSERT_NOT_EQUAL_MESSAGE(raw_temp1, raw_temp2, "Consecutive raw reads should ideally differ");
}

// --- Test Cases for validate_temperature_range ---

void test_validate_temperature_range_valid_normal(void) {
    TEST_ASSERT_TRUE(validate_temperature_range(25.0f));
    TEST_ASSERT_TRUE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_valid_min_edge(void) {
    TEST_ASSERT_TRUE(validate_temperature_range(-40.0f));
    TEST_ASSERT_TRUE(validate_temperature_range(-39.99f));
}

void test_validate_temperature_range_valid_max_edge(void) {
    TEST_ASSERT_TRUE(validate_temperature_range(125.0f));
    TEST_ASSERT_TRUE(validate_temperature_range(124.99f));
}

void test_validate_temperature_range_invalid_too_low(void) {
    TEST_ASSERT_FALSE(validate_temperature_range(-40.01f));
    TEST_ASSERT_FALSE(validate_temperature_range(-50.0f));
}

void test_validate_temperature_range_invalid_too_high(void) {
    TEST_ASSERT_FALSE(validate_temperature_range(125.01f));
    TEST_ASSERT_FALSE(validate_temperature_range(150.0f));
}

// --- Test Cases for check_temperature_status ---

void test_check_temperature_status_critical_above_120(void) {
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(120.01f));
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(125.0f));
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(200.0f));
}

void test_check_temperature_status_hot_above_85_below_or_equal_120(void) {
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(85.01f));
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(120.0f));
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(100.0f));
}

void test_check_temperature_status_cold_below_minus_10(void) {
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(-10.01f));
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(-40.0f));
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(-50.0f));
}

void test_check_temperature_status_normal_in_range(void) {
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(-10.0f));
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(0.0f));
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(25.0f));
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(85.0f));
}

// --- Test Cases for get_temperature_celsius ---

void test_get_temperature_celsius_calls_raw_and_converter(void) {
    // Configure the stub to return a specific Celsius value
    set_raw_to_celsius_return(25.5f);

    float result = get_temperature_celsius();

    // Verify raw_to_celsius was called once
    TEST_ASSERT_EQUAL(1, get_raw_to_celsius_call_count());

    // Verify the returned value matches the stub's configured return
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 25.5f, result);

    // Further checks: read_temperature_raw is not stubbed, so it uses rand().
    // We can't predict the exact raw value passed, but we know it should be in range.
    int last_raw_val = get_raw_to_celsius_last_raw();
    TEST_ASSERT_TRUE_MESSAGE(last_raw_val >= 0, "Raw value passed to stub should be non-negative");
    TEST_ASSERT_TRUE_MESSAGE(last_raw_val < 1024, "Raw value passed to stub should be less than 1024");
}

void test_get_temperature_celsius_different_raw_to_celsius_outputs(void) {
    set_raw_to_celsius_return(100.0f);
    float result1 = get_temperature_celsius();
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 100.0f, result1);
    TEST_ASSERT_EQUAL(1, get_raw_to_celsius_call_count()); // First call

    set_raw_to_celsius_return(-5.0f); // Change stub behavior
    float result2 = get_temperature_celsius();
    TEST_ASSERT_FLOAT_WITHIN(0.01f, -5.0f, result2);
    TEST_ASSERT_EQUAL(2, get_raw_to_celsius_call_count()); // Second call
}

// --- Main Test Runner ---



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_read_temperature_raw_returns_within_valid_range);
    RUN_TEST(test_read_temperature_raw_returns_different_values);
    RUN_TEST(test_validate_temperature_range_valid_normal);
    RUN_TEST(test_validate_temperature_range_valid_min_edge);
    RUN_TEST(test_validate_temperature_range_valid_max_edge);
    RUN_TEST(test_validate_temperature_range_invalid_too_low);
    RUN_TEST(test_validate_temperature_range_invalid_too_high);
    RUN_TEST(test_check_temperature_status_critical_above_120);
    RUN_TEST(test_check_temperature_status_hot_above_85_below_or_equal_120);
    RUN_TEST(test_check_temperature_status_cold_below_minus_10);
    RUN_TEST(test_check_temperature_status_normal_in_range);
    RUN_TEST(test_get_temperature_celsius_calls_raw_and_converter);
    RUN_TEST(test_get_temperature_celsius_different_raw_to_celsius_outputs);

    return UNITY_END();
}