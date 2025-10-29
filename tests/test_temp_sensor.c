/* test_temp_sensor.c – Auto-generated Expert Unity Tests */

#include "unity.h"
#include <stdbool.h> // For bool type
#include <stdint.h>  // For uint32_t in stub struct
#include <string.h>  // For memset

// Include the header of the module under test to get function prototypes
#include "temp_sensor.h"

// --- External Function Stubs ---
// Signature inferred from `get_temperature_celsius`: float raw_to_celsius(int raw_value)
typedef struct {
    float return_value;
    bool was_called;
    uint32_t call_count;
    int last_raw_value;
} stub_raw_to_celsius_t;

static stub_raw_to_celsius_t stub_raw_to_celsius = {0};

float raw_to_celsius(int raw_value) {
    stub_raw_to_celsius.was_called = true;
    stub_raw_to_celsius.call_count++;
    stub_raw_to_celsius.last_raw_value = raw_value;
    return stub_raw_to_celsius.return_value;
}

// --- Test Fixture Setup/Teardown ---
void setUp(void) {
    // Reset all stub control structures before each test
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
}

void tearDown(void) {
    // Clean up all stub control structures after each test
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
}

// --- Tests for read_temperature_raw() ---
void test_read_temperature_raw_returnsWithinValidRange(void) {
    int raw_value = read_temperature_raw();
    // Expected: The raw value should be within the 0 to 1023 range, based on rand() % 1024
    TEST_ASSERT_GREATER_THAN_EQUAL_INT(0, raw_value);
    // Expected: The raw value should be within the 0 to 1023 range, based on rand() % 1024
    TEST_ASSERT_LESS_THAN_EQUAL_INT(1023, raw_value);
}

void test_read_temperature_raw_multipleCallsStayWithinRange(void) {
    // Verify multiple calls consistently return values within the specified range
    for (int i = 0; i < 5; i++) {
        int raw_value = read_temperature_raw();
        // Expected: Each raw value should be within 0 to 1023 for every call
        TEST_ASSERT_GREATER_THAN_EQUAL_INT(0, raw_value);
        // Expected: Each raw value should be within 0 to 1023 for every call
        TEST_ASSERT_LESS_THAN_EQUAL_INT(1023, raw_value);
    }
}

// --- Tests for validate_temperature_range() ---
void test_validate_temperature_range_minValidEdge(void) {
    // Expected: 0.0f is valid as per temp_c >= 0.0f
    TEST_ASSERT_TRUE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_minInvalidBelowEdge(void) {
    // Expected: 0.0f is invalid as it's less than 0.0f
    TEST_ASSERT_FALSE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_maxValidEdge(void) {
    // Expected: 125.0f is valid as per temp_c <= 125.0f
    TEST_ASSERT_TRUE(validate_temperature_range(125.0f));
}

void test_validate_temperature_range_maxInvalidAboveEdge(void) {
    // Expected: 125.1f is invalid as it's greater than 125.0f
    TEST_ASSERT_FALSE(validate_temperature_range(125.1f));
}

void test_validate_temperature_range_nominalValid(void) {
    // Expected: 25.0f is valid as it's well within the 0.0f to 125.0f range
    TEST_ASSERT_TRUE(validate_temperature_range(25.0f));
}

// --- Tests for check_temperature_status() ---
void test_check_temperature_status_criticalAboveThreshold(void) {
    // Expected: 120.1f is "CRITICAL" as per temp_c > 120.0f
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(120.1f));
}

void test_check_temperature_status_criticalAtMaxValidTemp(void) {
    // Expected: 125.0f (max valid temperature) is "CRITICAL" as per temp_c > 120.0f
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(125.0f));
}

void test_check_temperature_status_hotJustAboveThreshold(void) {
    // Expected: 85.1f is "HOT" as per temp_c > 85.0f and not > 120.0f
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(85.1f));
}

void test_check_temperature_status_hotAtCriticalLowerEdge(void) {
    // Expected: 120.0f is "HOT" as per temp_c > 85.0f and not > 120.0f (inclusive)
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(120.0f));
}

void test_check_temperature_status_coldBelowThreshold(void) {
    // Expected: 0.0f is "COLD" as per temp_c < 0.0f
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(0.0f));
}

void test_check_temperature_status_coldAtMinValidTemp(void) {
    // Expected: 0.0f (min valid temperature) is "COLD" as per temp_c < 0.0f
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(0.0f));
}

void test_check_temperature_status_normalMidRange(void) {
    // Expected: 25.0f is "NORMAL" as it's within the range [0.0f, 85.0f]
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(25.0f));
}

void test_check_temperature_status_normalLowerEdge(void) {
    // Expected: 0.0f is "NORMAL" as it's not < 0.0f
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(0.0f));
}

void test_check_temperature_status_normalUpperEdge(void) {
    // Expected: 85.0f is "NORMAL" as it's not > 85.0f
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(85.0f));
}

// --- Tests for get_temperature_celsius() ---
void test_get_temperature_celsius_basicFlow(void) {
    // Configure the stub to return a specific Celsius value
    float expected_celsius = 25.5f;
    stub_raw_to_celsius.return_value = expected_celsius;

    float actual_celsius = get_temperature_celsius();

    // Expected: raw_to_celsius should have been called once
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    // Expected: raw_to_celsius should have been called exactly one time
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    // Expected: The raw value passed to raw_to_celsius should be within 0 and 1023
    TEST_ASSERT_GREATER_THAN_EQUAL_INT(0, stub_raw_to_celsius.last_raw_value);
    // Expected: The raw value passed to raw_to_celsius should be within 0 and 1023
    TEST_ASSERT_LESS_THAN_EQUAL_INT(1023, stub_raw_to_celsius.last_raw_value);
    // Expected: The function should return the value provided by the stubbed raw_to_celsius
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

void test_get_temperature_celsius_anotherValueScenario(void) {
    // Configure the stub to return a different Celsius value
    float expected_celsius = 95.0f;
    stub_raw_to_celsius.return_value = expected_celsius;

    float actual_celsius = get_temperature_celsius();

    // Expected: raw_to_celsius should have been called once
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    // Expected: raw_to_celsius should have been called exactly one time
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    // Expected: The raw value passed to raw_to_celsius should be within 0 and 1023
    TEST_ASSERT_GREATER_THAN_EQUAL_INT(0, stub_raw_to_celsius.last_raw_value);
    // Expected: The raw value passed to raw_to_celsius should be within 0 and 1023
    TEST_ASSERT_LESS_THAN_EQUAL_INT(1023, stub_raw_to_celsius.last_raw_value);
    // Expected: The function should return the value provided by the stubbed raw_to_celsius
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

// --- Main Test Runner ---


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_read_temperature_raw_returnsWithinValidRange);
    RUN_TEST(test_read_temperature_raw_multipleCallsStayWithinRange);
    RUN_TEST(test_validate_temperature_range_minValidEdge);
    RUN_TEST(test_validate_temperature_range_minInvalidBelowEdge);
    RUN_TEST(test_validate_temperature_range_maxValidEdge);
    RUN_TEST(test_validate_temperature_range_maxInvalidAboveEdge);
    RUN_TEST(test_validate_temperature_range_nominalValid);
    RUN_TEST(test_check_temperature_status_criticalAboveThreshold);
    RUN_TEST(test_check_temperature_status_criticalAtMaxValidTemp);
    RUN_TEST(test_check_temperature_status_hotJustAboveThreshold);
    RUN_TEST(test_check_temperature_status_hotAtCriticalLowerEdge);
    RUN_TEST(test_check_temperature_status_coldBelowThreshold);
    RUN_TEST(test_check_temperature_status_coldAtMinValidTemp);
    RUN_TEST(test_check_temperature_status_normalMidRange);
    RUN_TEST(test_check_temperature_status_normalLowerEdge);
    RUN_TEST(test_check_temperature_status_normalUpperEdge);
    RUN_TEST(test_get_temperature_celsius_basicFlow);
    RUN_TEST(test_get_temperature_celsius_anotherValueScenario);

    return UNITY_END();
}