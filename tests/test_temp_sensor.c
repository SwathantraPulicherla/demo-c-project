/* test_temp_sensor.c – Auto-generated Expert Unity Tests */

#include "unity.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h> // For memset

// Include the header for the module under test
// This brings in the declarations of the public API functions
#include "temp_sensor.h"

// ====================================================================
// External Function Declarations (from the module under test's includes)
// This is necessary to avoid compilation warnings if the stub doesn't perfectly match
// a declaration from an included header that the source file also uses.
// For example, temp_sensor.c includes temp_converter.h which declares raw_to_celsius.
// But we also need rand() which is in stdlib.h.
// It's safer to declare the functions we intend to stub as extern here.
extern int rand(void);
extern float raw_to_celsius(int raw_value);

// ====================================================================
// Stub Definitions for External Dependencies
// ONLY for `rand` and `raw_to_celsius` as specified and inferred.

// Stub control structure for raw_to_celsius
typedef struct {
    float return_value;
    bool was_called;
    uint32_t call_count;
    int last_raw_value;
} stub_raw_to_celsius_t;

static stub_raw_to_celsius_t stub_raw_to_celsius = {0};

// Stub implementation for raw_to_celsius
float raw_to_celsius(int raw_value) {
    stub_raw_to_celsius.was_called = true;
    stub_raw_to_celsius.call_count++;
    stub_raw_to_celsius.last_raw_value = raw_value;
    return stub_raw_to_celsius.return_value;
}

// Stub control structure for rand()
// This is critical for making read_temperature_raw() deterministic for testing.
typedef struct {
    int return_value;
    bool was_called;
    uint32_t call_count;
} stub_rand_t;

static stub_rand_t stub_rand = {0};

// Stub implementation for rand()
int rand(void) {
    stub_rand.was_called = true;
    stub_rand.call_count++;
    return stub_rand.return_value;
}

// ====================================================================
// SetUp and TearDown Functions for Test Isolation

void setUp(void) {
    // Reset all stub control structures to a known state before each test
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
    memset(&stub_rand, 0, sizeof(stub_rand));

    // Set default return values for stubs if needed for common scenarios
    // Otherwise, tests should explicitly set them.
    stub_raw_to_celsius.return_value = 0.0f; // Default to 0 C
    stub_rand.return_value = 0;             // Default to 0 raw value
}

void tearDown(void) {
    // Reset all stub control structures again after each test
    // This ensures complete isolation even if a test modified a stub and failed prematurely.
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
    memset(&stub_rand, 0, sizeof(stub_rand));
}

// ====================================================================
// Test Cases for validate_temperature_range

void test_validate_temperature_range_nominal_valid(void) {
    // Expected: 25.0f is within [0.0f, 125.0f] so it should be valid.
    TEST_ASSERT_TRUE(validate_temperature_range(25.0f));
}

void test_validate_temperature_range_lower_edge_valid(void) {
    // Expected: 0.0f is the exact lower bound and should be valid.
    TEST_ASSERT_TRUE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_lower_edge_invalid(void) {
    // Expected: 0.0f is just below the lower bound and should be invalid.
    TEST_ASSERT_FALSE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_upper_edge_valid(void) {
    // Expected: 125.0f is the exact upper bound and should be valid.
    TEST_ASSERT_TRUE(validate_temperature_range(125.0f));
}

void test_validate_temperature_range_upper_edge_invalid(void) {
    // Expected: 125.1f is just above the upper bound and should be invalid.
    TEST_ASSERT_FALSE(validate_temperature_range(125.1f));
}

void test_validate_temperature_range_mid_invalid_low(void) {
    // Expected: 0.0f is well below range and should be invalid.
    TEST_ASSERT_FALSE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_mid_invalid_high(void) {
    // Expected: 130.0f is well above range and should be invalid.
    TEST_ASSERT_FALSE(validate_temperature_range(130.0f));
}

// ====================================================================
// Test Cases for check_temperature_status

void test_check_temperature_status_critical_above_max(void) {
    // Expected: 120.1f is > 120.0f, so "CRITICAL".
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(120.1f));
}

void test_check_temperature_status_critical_at_max(void) {
    // Expected: 125.0f is > 120.0f, so "CRITICAL".
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(125.0f));
}

void test_check_temperature_status_hot_above_mid(void) {
    // Expected: 85.1f is > 85.0f and <= 120.0f, so "HOT".
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(85.1f));
}

void test_check_temperature_status_hot_at_edge(void) {
    // Expected: 120.0f is > 85.0f and NOT > 120.0f, so "HOT".
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(120.0f));
}

void test_check_temperature_status_normal_mid_range(void) {
    // Expected: 25.0f is not > 120.0f, not > 85.0f, and not < 0.0f, so "NORMAL".
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(25.0f));
}

void test_check_temperature_status_normal_at_hot_edge(void) {
    // Expected: 85.0f is not > 120.0f, not > 85.0f, and not < 0.0f, so "NORMAL".
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(85.0f));
}

void test_check_temperature_status_normal_at_cold_edge(void) {
    // Expected: 0.0f is not > 120.0f, not > 85.0f, and not < 0.0f, so "NORMAL".
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(0.0f));
}

void test_check_temperature_status_cold_below_min(void) {
    // Expected: 0.0f is < 0.0f, so "COLD".
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(0.0f));
}

void test_check_temperature_status_cold_at_min_valid(void) {
    // Expected: 0.0f is < 0.0f, so "COLD".
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(0.0f));
}

// ====================================================================
// Test Cases for get_temperature_celsius

void test_get_temperature_celsius_nominal_conversion(void) {
    // Configure stubs to simulate a specific scenario:
    // read_temperature_raw() (via rand()) returns 512.
    // raw_to_celsius() converts 512 to 25.0f.
    stub_rand.return_value = 512;
    stub_raw_to_celsius.return_value = 25.0f;

    // Call the function under test
    float result = get_temperature_celsius();

    // Expected: get_temperature_celsius() should return the value configured for raw_to_celsius.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 25.0f, result);
    // Expected: rand() should have been called once by read_temperature_raw().
    TEST_ASSERT_TRUE(stub_rand.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand.call_count);
    // Expected: raw_to_celsius() should have been called once with the raw value from rand().
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    TEST_ASSERT_EQUAL_INT(512, stub_raw_to_celsius.last_raw_value);
}

void test_get_temperature_celsius_min_raw_conversion(void) {
    // Configure stubs for minimum raw value (0) leading to minimum Celsius (0.0f).
    stub_rand.return_value = 0;
    stub_raw_to_celsius.return_value = 0.0f;

    float result = get_temperature_celsius();

    // Expected: Celsius conversion for raw 0 should be 0.0f.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, result);
    // Expected: rand() called once, raw_to_celsius() called once with raw 0.
    TEST_ASSERT_TRUE(stub_rand.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand.call_count);
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    TEST_ASSERT_EQUAL_INT(0, stub_raw_to_celsius.last_raw_value);
}

void test_get_temperature_celsius_max_raw_conversion(void) {
    // Configure stubs for maximum raw value (1023) leading to maximum Celsius (125.0f).
    stub_rand.return_value = 1023; // rand() % 1024 produces 00.0f
    stub_raw_to_celsius.return_value = 125.0f;

    float result = get_temperature_celsius();

    // Expected: Celsius conversion for raw 1023 should be 125.0f.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 125.0f, result);
    // Expected: rand() called once, raw_to_celsius() called once with raw 1023.
    TEST_ASSERT_TRUE(stub_rand.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand.call_count);
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    TEST_ASSERT_EQUAL_INT(1023, stub_raw_to_celsius.last_raw_value);
}

// ====================================================================
// Main function for running all tests



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_validate_temperature_range_nominal_valid);
    RUN_TEST(test_validate_temperature_range_lower_edge_valid);
    RUN_TEST(test_validate_temperature_range_lower_edge_invalid);
    RUN_TEST(test_validate_temperature_range_upper_edge_valid);
    RUN_TEST(test_validate_temperature_range_upper_edge_invalid);
    RUN_TEST(test_validate_temperature_range_mid_invalid_low);
    RUN_TEST(test_validate_temperature_range_mid_invalid_high);
    RUN_TEST(test_check_temperature_status_critical_above_max);
    RUN_TEST(test_check_temperature_status_critical_at_max);
    RUN_TEST(test_check_temperature_status_hot_above_mid);
    RUN_TEST(test_check_temperature_status_hot_at_edge);
    RUN_TEST(test_check_temperature_status_normal_mid_range);
    RUN_TEST(test_check_temperature_status_normal_at_hot_edge);
    RUN_TEST(test_check_temperature_status_normal_at_cold_edge);
    RUN_TEST(test_check_temperature_status_cold_below_min);
    RUN_TEST(test_check_temperature_status_cold_at_min_valid);
    RUN_TEST(test_get_temperature_celsius_nominal_conversion);
    RUN_TEST(test_get_temperature_celsius_min_raw_conversion);
    RUN_TEST(test_get_temperature_celsius_max_raw_conversion);

    return UNITY_END();
}