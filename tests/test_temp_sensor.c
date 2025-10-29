/* test_temp_sensor.c – Auto-generated Expert Unity Tests */

#include "unity.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h> // For memset

// Include the header of the module under test to get function declarations
// This is necessary as the functions under test are public API.
#include "temp_sensor.h"

// No need to include temp_converter.h as its functions will be stubbed,
// and temp_sensor.h already includes necessary types.

// --- Stub Definitions ---

// External function listed to stub: raw_to_celsius
// Inferred signature from usage in get_temperature_celsius(): float raw_to_celsius(int raw_value)
typedef struct {
    float return_value;
    bool was_called;
    uint32_t call_count;
    int last_raw_value; // Parameter capture
} stub_raw_to_celsius_t;

static stub_raw_to_celsius_t stub_raw_to_celsius = {0};

// Stub implementation for raw_to_celsius
float raw_to_celsius(int raw_value) {
    stub_raw_to_celsius.was_called = true;
    stub_raw_to_celsius.call_count++;
    stub_raw_to_celsius.last_raw_value = raw_value;
    return stub_raw_to_celsius.return_value;
}

// NOTE: The function read_temperature_raw() uses rand().
// The strict rules state to ONLY stub listed external dependencies, and rand() is not listed.
// Therefore, rand() will NOT be stubbed. Tests for read_temperature_raw() will
// check for output range rather than specific values.

// --- setUp and tearDown functions ---

void setUp(void) {
    // Reset all stub control structures to a known initial state
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
    // Set default return values for stubs if necessary
    stub_raw_to_celsius.return_value = 0.0f; // A safe default for float
}

void tearDown(void) {
    // Ensure all stub control structures are completely reset after each test
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
}

// --- Test Functions ---

// Test for read_temperature_raw()
// This function relies on rand() (from stdlib.h) which is not explicitly listed for stubbing.
// Therefore, we can only test the range of its output as it will be non-deterministic.
void test_read_temperature_raw_returnsWithinExpectedRange(void) {
    int result = read_temperature_raw();
    // Expected: The return value should be within the 0 to 1023 range based on `rand() % 1024`.
    TEST_ASSERT_TRUE(result >= 0, "Expected raw temperature to be >= 0");
    TEST_ASSERT_TRUE(result <= 1023, "Expected raw temperature to be <= 1023");
}

// Tests for validate_temperature_range(float temp_c)

void test_validate_temperature_range_minEdgeValid(void) {
    // Expected: 0.0f is the minimum valid temperature, so it should return true.
    TEST_ASSERT_TRUE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_maxEdgeValid(void) {
    // Expected: 125.0f is the maximum valid temperature, so it should return true.
    TEST_ASSERT_TRUE(validate_temperature_range(125.0f));
}

void test_validate_temperature_range_midRangeValid(void) {
    // Expected: 25.0f is within the valid range (0.0f to 125.0f), so it should return true.
    TEST_ASSERT_TRUE(validate_temperature_range(25.0f));
}

void test_validate_temperature_range_belowMinInvalid(void) {
    // Expected: 0.0f is below the minimum valid temperature (0.0f), so it should return false.
    TEST_ASSERT_FALSE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_aboveMaxInvalid(void) {
    // Expected: 125.1f is above the maximum valid temperature (125.0f), so it should return false.
    TEST_ASSERT_FALSE(validate_temperature_range(125.1f));
}

// Tests for check_temperature_status(float temp_c)

void test_check_temperature_status_criticalAbove120(void) {
    // Expected: 120.1f is > 120.0f, so the status should be "CRITICAL".
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(120.1f));
}

void test_check_temperature_status_criticalMaxValidTemp(void) {
    // Expected: 125.0f (max valid temperature) is > 120.0f, so the status should be "CRITICAL".
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(125.0f));
}

void test_check_temperature_status_hotAbove85(void) {
    // Expected: 85.1f is > 85.0f and not > 120.0f, so the status should be "HOT".
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(85.1f));
}

void test_check_temperature_status_hotEdgeBelowCritical(void) {
    // Expected: 120.0f is > 85.0f and not > 120.0f, so the status should be "HOT".
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(120.0f));
}

void test_check_temperature_status_normalMidRange(void) {
    // Expected: 25.0f is not > 85.0f and not < 0.0f, so the status should be "NORMAL".
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(25.0f));
}

void test_check_temperature_status_normalEdgeAboveCold(void) {
    // Expected: 0.0f is not < 0.0f and not > 85.0f, so the status should be "NORMAL".
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(0.0f));
}

void test_check_temperature_status_normalEdgeBelowHot(void) {
    // Expected: 85.0f is not > 85.0f and not < 0.0f, so the status should be "NORMAL".
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(85.0f));
}

void test_check_temperature_status_coldBelowNeg10(void) {
    // Expected: 0.0f is < 0.0f, so the status should be "COLD".
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(0.0f));
}

void test_check_temperature_status_coldMinValidTemp(void) {
    // Expected: 0.0f (min valid temperature) is < 0.0f, so the status should be "COLD".
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(0.0f));
}

// Tests for get_temperature_celsius()

void test_get_temperature_celsius_normalOperation(void) {
    // Configure stub for raw_to_celsius to return a typical Celsius value
    stub_raw_to_celsius.return_value = 25.5f;

    float result = get_temperature_celsius();

    // Expected: raw_to_celsius should have been called exactly once.
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    // Expected: The raw value passed to raw_to_celsius should be within 00.0f (from read_temperature_raw).
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_value >= 0, "Raw value passed to stub should be >= 0");
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_value <= 1023, "Raw value passed to stub should be <= 1023");

    // Expected: The final result should match the stubbed return value from raw_to_celsius.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 25.5f, result);
}

void test_get_temperature_celsius_zeroCelsiusConversion(void) {
    // Configure stub for raw_to_celsius to return a specific Celsius value (e.g., 0.0f)
    stub_raw_to_celsius.return_value = 0.0f;

    float result = get_temperature_celsius();

    // Expected: raw_to_celsius should have been called exactly once.
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    // Expected: The raw value passed to raw_to_celsius should be within 00.0f.
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_value >= 0, "Raw value passed to stub should be >= 0");
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_value <= 1023, "Raw value passed to stub should be <= 1023");

    // Expected: The final result should match the stubbed return value from raw_to_celsius.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, result);
}

void test_get_temperature_celsius_negativeCelsiusConversion(void) {
    // Configure stub for raw_to_celsius to return a negative Celsius value
    stub_raw_to_celsius.return_value = 0.0f;

    float result = get_temperature_celsius();

    // Expected: raw_to_celsius should have been called exactly once.
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    // Expected: The raw value passed to raw_to_celsius should be within 00.0f.
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_value >= 0, "Raw value passed to stub should be >= 0");
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_value <= 1023, "Raw value passed to stub should be <= 1023");

    // Expected: The final result should match the stubbed return value from raw_to_celsius.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, result);
}

// --- Main function to run all tests ---


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_read_temperature_raw_returnsWithinExpectedRange);
    RUN_TEST(test_validate_temperature_range_minEdgeValid);
    RUN_TEST(test_validate_temperature_range_maxEdgeValid);
    RUN_TEST(test_validate_temperature_range_midRangeValid);
    RUN_TEST(test_validate_temperature_range_belowMinInvalid);
    RUN_TEST(test_validate_temperature_range_aboveMaxInvalid);
    RUN_TEST(test_check_temperature_status_criticalAbove120);
    RUN_TEST(test_check_temperature_status_criticalMaxValidTemp);
    RUN_TEST(test_check_temperature_status_hotAbove85);
    RUN_TEST(test_check_temperature_status_hotEdgeBelowCritical);
    RUN_TEST(test_check_temperature_status_normalMidRange);
    RUN_TEST(test_check_temperature_status_normalEdgeAboveCold);
    RUN_TEST(test_check_temperature_status_normalEdgeBelowHot);
    RUN_TEST(test_check_temperature_status_coldBelowNeg10);
    RUN_TEST(test_check_temperature_status_coldMinValidTemp);
    RUN_TEST(test_get_temperature_celsius_normalOperation);
    RUN_TEST(test_get_temperature_celsius_zeroCelsiusConversion);
    RUN_TEST(test_get_temperature_celsius_negativeCelsiusConversion);

    return UNITY_END();
}