/* test_temp_sensor.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h> // For memset

// Source functions (assuming they are in temp_sensor.c and will be linked)
// Declared as extern here to satisfy compilation requirements for the test runner.
extern int read_temperature_raw();
extern bool validate_temperature_range(float temp_c);
extern const char* check_temperature_status(float temp_c);
extern float get_temperature_celsius();

// --- External Function Stubs ---
// Only for functions listed in "EXTERNAL FUNCTIONS TO STUB".
// Infer signature: float raw_to_celsius(int raw_val)
typedef struct {
    float return_value;
    bool was_called;
    uint32_t call_count;
    int last_raw_val; // Captured parameter, value will be non-deterministic due to rand()
} stub_raw_to_celsius_t;

static stub_raw_to_celsius_t stub_raw_to_celsius = {0};

float raw_to_celsius(int raw_val) {
    stub_raw_to_celsius.was_called = true;
    stub_raw_to_celsius.call_count++;
    stub_raw_to_celsius.last_raw_val = raw_val; // Capture the random raw_val
    return stub_raw_to_celsius.return_value;
}

// --- Test Setup and Teardown ---
void setUp(void) {
    // Reset all stubs to their default state before each test
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
    // Set default return values for stubs
    stub_raw_to_celsius.return_value = 0.0f; // A common default for float returns
}

void tearDown(void) {
    // Reset all stubs after each test to ensure isolation
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
}

// --- Test Cases for read_temperature_raw() ---
// This function relies on rand(), which is not listed for stubbing.
// Therefore, we can only test that its output is within the expected range,
// rather than an exact deterministic value.
void test_read_temperature_raw_returnsWithinExpectedRange(void) {
    int raw_val = read_temperature_raw();
    // Expected: The raw value should be within the 0 to 1023 range as per rand() % 1024 logic in source
    TEST_ASSERT_TRUE(raw_val >= 0);
    // Expected: The raw value should not exceed 1023
    TEST_ASSERT_TRUE(raw_val <= 1023);
}

void test_read_temperature_raw_multipleCallsStayWithinRange(void) {
    // Execute multiple times to ensure consistent range behavior over several calls
    for (int i = 0; i < 50; i++) {
        int raw_val = read_temperature_raw();
        // Expected: Each raw value should be within the 0 to 1023 range
        TEST_ASSERT_TRUE(raw_val >= 0);
        // Expected: Each raw value should not exceed 1023
        TEST_ASSERT_TRUE(raw_val <= 1023);
    }
}

// --- Test Cases for validate_temperature_range() ---
void test_validate_temperature_range_validMidRange(void) {
    float temp = 25.0f;
    bool result = validate_temperature_range(temp);
    // Expected: 25.0f is within [0.0f, 125.0f], so should return true
    TEST_ASSERT_TRUE(result);
}

void test_validate_temperature_range_validMinEdge(void) {
    float temp = 0.0f;
    bool result = validate_temperature_range(temp);
    // Expected: 0.0f is exactly the minimum valid temperature, so should return true
    TEST_ASSERT_TRUE(result);
}

void test_validate_temperature_range_validMaxEdge(void) {
    float temp = 125.0f;
    bool result = validate_temperature_range(temp);
    // Expected: 125.0f is exactly the maximum valid temperature, so should return true
    TEST_ASSERT_TRUE(result);
}

void test_validate_temperature_range_invalidBelowMin(void) {
    float temp = 0.0f;
    bool result = validate_temperature_range(temp);
    // Expected: 0.0f is below the minimum valid temperature of 0.0f, so should return false
    TEST_ASSERT_FALSE(result);
}

void test_validate_temperature_range_invalidAboveMax(void) {
    float temp = 125.1f;
    bool result = validate_temperature_range(temp);
    // Expected: 125.1f is above the maximum valid temperature of 125.0f, so should return false
    TEST_ASSERT_FALSE(result);
}

// --- Test Cases for check_temperature_status() ---
void test_check_temperature_status_criticalHotJustAbove(void) {
    float temp = 120.1f;
    const char* status = check_temperature_status(temp);
    // Expected: 120.1f is > 120.0f, triggering the CRITICAL_HOT branch
    TEST_ASSERT_EQUAL_STRING("[STRING REDACTED]", status);
}

void test_check_temperature_status_criticalHotHighValue(void) {
    float temp = 150.0f; // A high, but realistic hot temperature
    const char* status = check_temperature_status(temp);
    // Expected: 150.0f is > 120.0f, triggering the CRITICAL_HOT branch
    TEST_ASSERT_EQUAL_STRING("[STRING REDACTED]", status);
}

void test_check_temperature_status_warningHotJustAbove(void) {
    float temp = 85.1f;
    const char* status = check_temperature_status(temp);
    // Expected: 85.1f is > 85.0f and <= 120.0f, triggering the WARNING_HOT branch
    TEST_ASSERT_EQUAL_STRING("[STRING REDACTED]", status);
}

void test_check_temperature_status_warningHotJustBelowCritical(void) {
    float temp = 120.0f;
    const char* status = check_temperature_status(temp);
    // Expected: 120.0f is not > 120.0f but is > 85.0f, falling into the WARNING_HOT branch
    TEST_ASSERT_EQUAL_STRING("[STRING REDACTED]", status);
}

void test_check_temperature_status_coldJustBelow(void) {
    float temp = 0.0f;
    const char* status = check_temperature_status(temp);
    // Expected: 0.0f is < 0.0f, triggering the COLD branch
    TEST_ASSERT_EQUAL_STRING("[STRING REDACTED]", status);
}

void test_check_temperature_status_coldLowValue(void) {
    float temp = 0.0f; // A low, but realistic cold temperature
    const char* status = check_temperature_status(temp);
    // Expected: 0.0f is < 0.0f, triggering the COLD branch
    TEST_ASSERT_EQUAL_STRING("[STRING REDACTED]", status);
}

void test_check_temperature_status_normalMidRange(void) {
    float temp = 25.0f;
    const char* status = check_temperature_status(temp);
    // Expected: 25.0f is not > 120, not > 85, not < 0.0f, so falls into the NORMAL branch
    TEST_ASSERT_EQUAL_STRING("[STRING REDACTED]", status);
}

void test_check_temperature_status_normalColdEdge(void) {
    float temp = 0.0f;
    const char* status = check_temperature_status(temp);
    // Expected: 0.0f is not < 0.0f, so falls into the NORMAL branch
    TEST_ASSERT_EQUAL_STRING("[STRING REDACTED]", status);
}

void test_check_temperature_status_normalHotEdge(void) {
    float temp = 85.0f;
    const char* status = check_temperature_status(temp);
    // Expected: 85.0f is not > 85.0f, so falls into the NORMAL branch
    TEST_ASSERT_EQUAL_STRING("[STRING REDACTED]", status);
}

// --- Test Cases for get_temperature_celsius() ---
void test_get_temperature_celsius_returnsStubbedValueNormal(void) {
    // Configure the raw_to_celsius stub to return a specific, normal temperature value
    stub_raw_to_celsius.return_value = 25.5f;
    
    float result = get_temperature_celsius();
    
    // Expected: raw_to_celsius should have been called exactly once
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    // Expected: get_temperature_celsius should return the value provided by the stub
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 25.5f, result);
    // Note: stub_raw_to_celsius.last_raw_val cannot be asserted deterministically due to rand() in read_temperature_raw()
}

void test_get_temperature_celsius_returnsStubbedValueMinEdge(void) {
    // Configure stub to return minimum valid temperature
    stub_raw_to_celsius.return_value = 0.0f;
    
    float result = get_temperature_celsius();
    
    // Expected: raw_to_celsius should have been called
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    // Expected: get_temperature_celsius should return the stubbed minimum value
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, result);
}

void test_get_temperature_celsius_returnsStubbedValueMaxEdge(void) {
    // Configure stub to return maximum valid temperature
    stub_raw_to_celsius.return_value = 125.0f;
    
    float result = get_temperature_celsius();
    
    // Expected: raw_to_celsius should have been called
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    // Expected: get_temperature_celsius should return the stubbed maximum value
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 125.0f, result);
}

void test_get_temperature_celsius_returnsStubbedValueCold(void) {
    // Configure stub to return a cold temperature
    stub_raw_to_celsius.return_value = 0.0f;
    
    float result = get_temperature_celsius();
    
    // Expected: raw_to_celsius should have been called
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    // Expected: get_temperature_celsius should return the stubbed cold value
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, result);
}

// --- Main Unity Runner ---


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_read_temperature_raw_returnsWithinExpectedRange);
    RUN_TEST(test_read_temperature_raw_multipleCallsStayWithinRange);
    RUN_TEST(test_validate_temperature_range_validMidRange);
    RUN_TEST(test_validate_temperature_range_validMinEdge);
    RUN_TEST(test_validate_temperature_range_validMaxEdge);
    RUN_TEST(test_validate_temperature_range_invalidBelowMin);
    RUN_TEST(test_validate_temperature_range_invalidAboveMax);
    RUN_TEST(test_check_temperature_status_criticalHotJustAbove);
    RUN_TEST(test_check_temperature_status_criticalHotHighValue);
    RUN_TEST(test_check_temperature_status_warningHotJustAbove);
    RUN_TEST(test_check_temperature_status_warningHotJustBelowCritical);
    RUN_TEST(test_check_temperature_status_coldJustBelow);
    RUN_TEST(test_check_temperature_status_coldLowValue);
    RUN_TEST(test_check_temperature_status_normalMidRange);
    RUN_TEST(test_check_temperature_status_normalColdEdge);
    RUN_TEST(test_check_temperature_status_normalHotEdge);
    RUN_TEST(test_get_temperature_celsius_returnsStubbedValueNormal);
    RUN_TEST(test_get_temperature_celsius_returnsStubbedValueMinEdge);
    RUN_TEST(test_get_temperature_celsius_returnsStubbedValueMaxEdge);
    RUN_TEST(test_get_temperature_celsius_returnsStubbedValueCold);

    return UNITY_END();
}