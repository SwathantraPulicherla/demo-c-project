#include "unity.h"
#include "temp_sensor.h" // For functions under test
#include <stdbool.h>     // For bool type in stubs
#include <stdint.h>      // For uint32_t in stubs
#include <string.h>      // For memset

// --- Stub Declarations and Control Structures ---

// Stub for rand() from stdlib.h, used by read_temperature_raw()
// This function signature is from <stdlib.h>
int rand(void); 
typedef struct {
    int return_value;
    bool was_called;
    uint32_t call_count;
} stub_rand_t;
static stub_rand_t stub_rand;

// Stub for raw_to_celsius, assumed to be declared in temp_converter.h based on usage
// Prototype: float raw_to_celsius(int raw); (This prototype is assumed from temp_converter.h)
float raw_to_celsius(int raw);
typedef struct {
    float return_value;
    bool was_called;
    uint32_t call_count;
    int captured_raw; // Capture the argument passed to raw_to_celsius
} stub_raw_to_celsius_t;
static stub_raw_to_celsius_t stub_raw_to_celsius;

// --- Stub Implementations ---

// Override the standard library rand() for deterministic testing
int rand(void) {
    stub_rand.was_called = true;
    stub_rand.call_count++;
    return stub_rand.return_value;
}

// Stub for raw_to_celsius function
float raw_to_celsius(int raw) {
    stub_raw_to_celsius.was_called = true;
    stub_raw_to_celsius.call_count++;
    stub_raw_to_celsius.captured_raw = raw;
    return stub_raw_to_celsius.return_value;
}

// --- Test Setup and Teardown ---

void setUp(void) {
    // Reset all stubs before each test
    memset(&stub_rand, 0, sizeof(stub_rand));
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));

    // Set default return values for stubs if needed, or configure in individual tests
    stub_rand.return_value = 0; // Default to 0, actual value set per test
    stub_raw_to_celsius.return_value = 0.0f; // Default to 0.0f
}

void tearDown(void) {
    // Ensure all stubs are fully reset after each test
    memset(&stub_rand, 0, sizeof(stub_rand));
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
}

// --- Test Cases for read_temperature_raw ---

void test_read_temperature_raw_returns_stubbed_value_modulo_1024(void) {
    stub_rand.return_value = 500; // Configure rand() to return 500
    // Expected: read_temperature_raw returns 500 % 1024 = 500
    TEST_ASSERT_EQUAL_INT(500, read_temperature_raw());
    // Expected: rand() was called once
    TEST_ASSERT_TRUE(stub_rand.was_called);
    // Expected: rand() was called once
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand.call_count);
}

void test_read_temperature_raw_returns_zero_for_zero_rand(void) {
    stub_rand.return_value = 0; // Configure rand() to return 0
    // Expected: read_temperature_raw returns 0 % 1024 = 0
    TEST_ASSERT_EQUAL_INT(0, read_temperature_raw());
    // Expected: rand() was called once
    TEST_ASSERT_TRUE(stub_rand.was_called);
}

void test_read_temperature_raw_returns_max_value_for_large_rand(void) {
    stub_rand.return_value = 1023; // Configure rand() to return 1023 (max before modulo)
    // Expected: read_temperature_raw returns 1023 % 1024 = 1023
    TEST_ASSERT_EQUAL_INT(1023, read_temperature_raw());
}

void test_read_temperature_raw_returns_value_just_over_modulo_boundary(void) {
    stub_rand.return_value = 1024; // Configure rand() to return 1024
    // Expected: read_temperature_raw returns 1024 % 1024 = 0
    TEST_ASSERT_EQUAL_INT(0, read_temperature_raw());
}

// --- Test Cases for validate_temperature_range ---

void test_validate_temperature_range_nominal_valid(void) {
    // Expected: 25.0f is within range [0.0f, 125]
    TEST_ASSERT_TRUE(validate_temperature_range(25.0f));
}

void test_validate_temperature_range_min_edge_valid(void) {
    // Expected: 0.0f is within range [0.0f, 125]
    TEST_ASSERT_TRUE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_max_edge_valid(void) {
    // Expected: 125.0f is within range [0.0f, 125]
    TEST_ASSERT_TRUE(validate_temperature_range(125.0f));
}

void test_validate_temperature_range_below_min_invalid(void) {
    // Expected: 0.0f is below min range
    TEST_ASSERT_FALSE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_above_max_invalid(void) {
    // Expected: 125.1f is above max range
    TEST_ASSERT_FALSE(validate_temperature_range(125.1f));
}

// --- Test Cases for check_temperature_status ---

void test_check_temperature_status_critical_above_threshold(void) {
    // Expected: 120.1f is above 120.0f, so status is CRITICAL
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(120.1f));
}

void test_check_temperature_status_hot_below_critical_above_hot(void) {
    // Expected: 120.0f is not strictly above 120.0f, but is above 85.0f, so status is HOT
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(120.0f));
}

void test_check_temperature_status_hot_above_threshold(void) {
    // Expected: 90.0f is above 85.0f, so status is HOT
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(90.0f));
}

void test_check_temperature_status_hot_edge_lower(void) {
    // Expected: 85.1f is above 85.0f, so status is HOT
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(85.1f));
}

void test_check_temperature_status_normal_below_hot_above_cold(void) {
    // Expected: 85.0f is not above 85.0f, and not below 0.0f, so status is NORMAL
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(85.0f));
}

void test_check_temperature_status_normal_mid_range(void) {
    // Expected: 25.0f is between 0.0f and 85.0f, so status is NORMAL
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(25.0f));
}

void test_check_temperature_status_normal_below_cold_threshold(void) {
    // Expected: 0.0f is not strictly below 0.0f, so status is NORMAL
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(0.0f));
}

void test_check_temperature_status_cold_below_threshold(void) {
    // Expected: 0.0f is below 0.0f, so status is COLD
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(0.0f));
}

void test_check_temperature_status_cold_min_valid_temp(void) {
    // Expected: 0.0f is below 0.0f, so status is COLD (using realistic min temp)
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(0.0f));
}

// --- Test Cases for get_temperature_celsius ---

void test_get_temperature_celsius_calls_stubs_and_returns_converted_value(void) {
    stub_rand.return_value = 512; // read_temperature_raw will return 512
    stub_raw_to_celsius.return_value = 25.0f; // raw_to_celsius will return 25.0f for this test

    // Expected: get_temperature_celsius returns 25.0f within 0.1f tolerance
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 25.0f, get_temperature_celsius());

    // Expected: rand() was called once
    TEST_ASSERT_TRUE(stub_rand.was_called);
    // Expected: rand() was called once
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand.call_count);

    // Expected: raw_to_celsius was called once
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    // Expected: raw_to_celsius was called once
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    // Expected: raw_to_celsius was called with the value from read_temperature_raw
    TEST_ASSERT_EQUAL_INT(512, stub_raw_to_celsius.captured_raw);
}

void test_get_temperature_celsius_handles_min_raw_value(void) {
    stub_rand.return_value = 0; // read_temperature_raw will return 0
    stub_raw_to_celsius.return_value = 0.0f; // raw_to_celsius converts 0 raw to 0.0f0C (realistic min temp)

    // Expected: get_temperature_celsius returns 0.0f within 0.1f tolerance
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, get_temperature_celsius());

    // Expected: raw_to_celsius was called with 0
    TEST_ASSERT_EQUAL_INT(0, stub_raw_to_celsius.captured_raw);
}

void test_get_temperature_celsius_handles_max_raw_value(void) {
    stub_rand.return_value = 1023; // read_temperature_raw will return 1023
    stub_raw_to_celsius.return_value = 125.0f; // raw_to_celsius converts 1023 raw to 125.0C (realistic max temp)

    // Expected: get_temperature_celsius returns 125.0f within 0.1f tolerance
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 125.0f, get_temperature_celsius());

    // Expected: raw_to_celsius was called with 1023
    TEST_ASSERT_EQUAL_INT(1023, stub_raw_to_celsius.captured_raw);
}

void test_get_temperature_celsius_realistic_mid_range(void) {
    stub_rand.return_value = 400; // Simulate a realistic raw reading
    stub_raw_to_celsius.return_value = 18.5f; // Simulate its conversion

    // Expected: get_temperature_celsius returns 18.5f within 0.1f tolerance
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 18.5f, get_temperature_celsius());

    // Expected: raw_to_celsius was called with 400
    TEST_ASSERT_EQUAL_INT(400, stub_raw_to_celsius.captured_raw);
}

// --- Main Test Runner ---



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_read_temperature_raw_returns_stubbed_value_modulo_1024);
    RUN_TEST(test_read_temperature_raw_returns_zero_for_zero_rand);
    RUN_TEST(test_read_temperature_raw_returns_max_value_for_large_rand);
    RUN_TEST(test_read_temperature_raw_returns_value_just_over_modulo_boundary);
    RUN_TEST(test_validate_temperature_range_nominal_valid);
    RUN_TEST(test_validate_temperature_range_min_edge_valid);
    RUN_TEST(test_validate_temperature_range_max_edge_valid);
    RUN_TEST(test_validate_temperature_range_below_min_invalid);
    RUN_TEST(test_validate_temperature_range_above_max_invalid);
    RUN_TEST(test_check_temperature_status_critical_above_threshold);
    RUN_TEST(test_check_temperature_status_hot_below_critical_above_hot);
    RUN_TEST(test_check_temperature_status_hot_above_threshold);
    RUN_TEST(test_check_temperature_status_hot_edge_lower);
    RUN_TEST(test_check_temperature_status_normal_below_hot_above_cold);
    RUN_TEST(test_check_temperature_status_normal_mid_range);
    RUN_TEST(test_check_temperature_status_normal_below_cold_threshold);
    RUN_TEST(test_check_temperature_status_cold_below_threshold);
    RUN_TEST(test_check_temperature_status_cold_min_valid_temp);
    RUN_TEST(test_get_temperature_celsius_calls_stubs_and_returns_converted_value);
    RUN_TEST(test_get_temperature_celsius_handles_min_raw_value);
    RUN_TEST(test_get_temperature_celsius_handles_max_raw_value);
    RUN_TEST(test_get_temperature_celsius_realistic_mid_range);

    return UNITY_END();
}