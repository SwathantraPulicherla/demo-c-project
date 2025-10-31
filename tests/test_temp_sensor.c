/* test_temp_sensor.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h> // For memset and strcmp
#include <stdlib.h> // Required for rand() used by read_temperature_raw()

// --- External Function Declarations for functions from temp_sensor.c ---
// These functions are defined in the source file and will be tested directly.
int read_temperature_raw(void);
bool validate_temperature_range(float temp_c);
const char* check_temperature_status(float temp_c);
float get_temperature_celsius(void);

// --- Stub for External Dependencies ---
// This struct controls the behavior of the raw_to_celsius stub.
// Signature inferred from `raw_to_celsius(raw)` where `raw` is an `int`.
typedef struct {
    float return_value;
    bool was_called;
    uint32_t call_count;
    int last_raw_val; // Capture the raw value passed to the stub
} stub_raw_to_celsius_t;

static stub_raw_to_celsius_t stub_raw_to_celsius = {0};

// Implementation of the external stub function: raw_to_celsius
float raw_to_celsius(int raw_val) {
    stub_raw_to_celsius.was_called = true;
    stub_raw_to_celsius.call_count++;
    stub_raw_to_celsius.last_raw_val = raw_val;
    return stub_raw_to_celsius.return_value;
}

// --- Placeholder for Redacted Strings ---
// These static const char* mimic the string literals that `check_temperature_status` would return.
static const char* STATUS_CRITICAL_HIGH = "CRITICAL_HIGH";
static const char* STATUS_WARNING_HIGH = "WARNING_HIGH";
static const char* STATUS_CRITICAL_LOW = "CRITICAL_LOW";
static const char* STATUS_NORMAL = "NORMAL";

// --- Test Setup and Teardown ---
void setUp(void) {
    // Reset all stub control structures to their default state before each test.
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
    // Set a realistic default return value for raw_to_celsius for scenarios
    // where it's called but not specifically configured by the test.
    stub_raw_to_celsius.return_value = 25.0f; // A nominal room temperature in Celsius.
}

void tearDown(void) {
    // Ensure all stub control structures are completely reset after each test.
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
}

// --- Test Cases for read_temperature_raw() ---
// This function uses `rand() % 1024`. Since `rand()` is not listed for stubbing,
// we test the range of the output as `read_temperature_raw` is an internal dependency.
void test_read_temperature_raw_returnsWithinExpectedRange(void) {
    int raw_val = read_temperature_raw();
    // Expected: The raw value should be within the range [0, 1023] based on `rand() % 1024`.
    TEST_ASSERT_TRUE(raw_val >= 0);
    TEST_ASSERT_TRUE(raw_val <= 1023);
}

// --- Test Cases for validate_temperature_range(float temp_c) ---
void test_validate_temperature_range_valid_midRange(void) {
    // Expected: 25.0f is within the valid range of 0.0f to 125.0f.
    TEST_ASSERT_TRUE(validate_temperature_range(25.0f));
}

void test_validate_temperature_range_valid_minEdge(void) {
    // Expected: 0.0f is the exact minimum allowed temperature, so it should be valid.
    TEST_ASSERT_TRUE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_valid_maxEdge(void) {
    // Expected: 125.0f is the exact maximum allowed temperature, so it should be valid.
    TEST_ASSERT_TRUE(validate_temperature_range(125.0f));
}

void test_validate_temperature_range_invalid_belowMin(void) {
    // Expected: 0.0f is just below the minimum valid temperature (0.0f), so it should be invalid.
    TEST_ASSERT_FALSE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_invalid_aboveMax(void) {
    // Expected: 125.1f is just above the maximum valid temperature (125.0f), so it should be invalid.
    TEST_ASSERT_FALSE(validate_temperature_range(125.1f));
}

// --- Test Cases for check_temperature_status(float temp_c) ---
void test_check_temperature_status_criticalHigh_aboveThreshold(void) {
    // Expected: 120.1f is greater than 120.0f, so the status should be CRITICAL_HIGH.
    TEST_ASSERT_EQUAL_STRING(STATUS_CRITICAL_HIGH, check_temperature_status(120.1f));
}

void test_check_temperature_status_criticalHigh_atMaxValidRange(void) {
    // Expected: 125.0f is greater than 120.0f (and max valid temp), so the status should be CRITICAL_HIGH.
    TEST_ASSERT_EQUAL_STRING(STATUS_CRITICAL_HIGH, check_temperature_status(125.0f));
}

void test_check_temperature_status_warningHigh_aboveThreshold(void) {
    // Expected: 85.1f is greater than 85.0f but not greater than 120.0f, so the status should be WARNING_HIGH.
    TEST_ASSERT_EQUAL_STRING(STATUS_WARNING_HIGH, check_temperature_status(85.1f));
}

void test_check_temperature_status_warningHigh_atUpperBranchEdge(void) {
    // Expected: 120.0f is greater than 85.0f but not greater than 120.0f, so the status should be WARNING_HIGH.
    TEST_ASSERT_EQUAL_STRING(STATUS_WARNING_HIGH, check_temperature_status(120.0f));
}

void test_check_temperature_status_criticalLow_belowThreshold(void) {
    // Expected: 0.0f is less than 0.0f, so the status should be CRITICAL_LOW.
    TEST_ASSERT_EQUAL_STRING(STATUS_CRITICAL_LOW, check_temperature_status(0.0f));
}

void test_check_temperature_status_criticalLow_atMinValidRange(void) {
    // Expected: 0.0f is less than 0.0f (and min valid temp), so the status should be CRITICAL_LOW.
    TEST_ASSERT_EQUAL_STRING(STATUS_CRITICAL_LOW, check_temperature_status(0.0f));
}

void test_check_temperature_status_normal_midRange(void) {
    // Expected: 25.0f does not meet critical high, warning high, or critical low conditions, so status is NORMAL.
    TEST_ASSERT_EQUAL_STRING(STATUS_NORMAL, check_temperature_status(25.0f));
}

void test_check_temperature_status_normal_atColdThreshold(void) {
    // Expected: 0.0f is not less than 0.0f, so it falls through to the NORMAL status.
    TEST_ASSERT_EQUAL_STRING(STATUS_NORMAL, check_temperature_status(0.0f));
}

void test_check_temperature_status_normal_atWarmThreshold(void) {
    // Expected: 85.0f is not greater than 85.0f, so it falls through to the NORMAL status.
    TEST_ASSERT_EQUAL_STRING(STATUS_NORMAL, check_temperature_status(85.0f));
}

// --- Test Cases for get_temperature_celsius() ---
void test_get_temperature_celsius_convertsRawValue(void) {
    // Configure the stub `raw_to_celsius` to return a specific Celsius value.
    float expected_celsius = 22.5f;
    stub_raw_to_celsius.return_value = expected_celsius;

    float actual_celsius = get_temperature_celsius();

    // Expected: `raw_to_celsius` should have been called exactly once.
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    // Expected: The parameter passed to `raw_to_celsius` should be within the 00.0f range from `read_temperature_raw`.
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_val >= 0);
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_val <= 1023);
    // Expected: The function `get_temperature_celsius` should return the value provided by the stub.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

void test_get_temperature_celsius_convertsAnotherRawValue(void) {
    // Configure the stub for a different scenario, e.g., a higher temperature.
    float expected_celsius = 98.7f;
    stub_raw_to_celsius.return_value = expected_celsius;

    float actual_celsius = get_temperature_celsius();

    // Expected: `raw_to_celsius` should have been called exactly once.
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    // Expected: The parameter passed to `raw_to_celsius` should be within the 00.0f range from `read_temperature_raw`.
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_val >= 0);
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_val <= 1023);
    // Expected: The function `get_temperature_celsius` should return the value provided by the stub.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

// --- Main Test Runner ---


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_read_temperature_raw_returnsWithinExpectedRange);
    RUN_TEST(test_validate_temperature_range_valid_midRange);
    RUN_TEST(test_validate_temperature_range_valid_minEdge);
    RUN_TEST(test_validate_temperature_range_valid_maxEdge);
    RUN_TEST(test_validate_temperature_range_invalid_belowMin);
    RUN_TEST(test_validate_temperature_range_invalid_aboveMax);
    RUN_TEST(test_check_temperature_status_criticalHigh_aboveThreshold);
    RUN_TEST(test_check_temperature_status_criticalHigh_atMaxValidRange);
    RUN_TEST(test_check_temperature_status_warningHigh_aboveThreshold);
    RUN_TEST(test_check_temperature_status_warningHigh_atUpperBranchEdge);
    RUN_TEST(test_check_temperature_status_criticalLow_belowThreshold);
    RUN_TEST(test_check_temperature_status_criticalLow_atMinValidRange);
    RUN_TEST(test_check_temperature_status_normal_midRange);
    RUN_TEST(test_check_temperature_status_normal_atColdThreshold);
    RUN_TEST(test_check_temperature_status_normal_atWarmThreshold);
    RUN_TEST(test_get_temperature_celsius_convertsRawValue);
    RUN_TEST(test_get_temperature_celsius_convertsAnotherRawValue);

    return UNITY_END();
}