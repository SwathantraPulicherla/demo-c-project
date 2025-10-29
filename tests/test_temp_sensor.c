/* test_temp_sensor.c – Auto-generated Expert Unity Tests */

#include "unity.h"
#include "temp_sensor.h" // For declarations of functions under test
#include <stdbool.h>
#include <stdint.h>
#include <string.h>  // For memset

// Define the external functions that need to be stubbed
// The original temp_converter.h would define raw_to_celsius.
// For testing, we provide a stub here.

// --- STUB for raw_to_celsius ---
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

// --- STUB for rand() ---
// This is done to make read_temperature_raw deterministic.
// We declare extern to allow overriding the standard library rand() for this compilation unit.
extern int rand(void); // Declare extern to prevent conflicts if stdlib.h is included implicitly elsewhere.

typedef struct {
    int return_value;
    bool was_called;
    uint32_t call_count;
} stub_rand_t;

static stub_rand_t stub_rand = {0};

int rand(void) {
    stub_rand.was_called = true;
    stub_rand.call_count++;
    return stub_rand.return_value;
}

// --- Test Fixture Setup & Teardown ---
void setUp(void) {
    // Reset all stub control structures
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
    memset(&stub_rand, 0, sizeof(stub_rand));
}

void tearDown(void) {
    // Reset all stub control structures (redundant but good practice for isolation)
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
    memset(&stub_rand, 0, sizeof(stub_rand));
}

// --- Tests for read_temperature_raw() ---

void test_read_temperature_raw_returns_value_from_rand_modulo_1024(void) {
    stub_rand.return_value = 500; // Simulate rand() returning 500
    // Expected: 500 % 1024 = 500
    TEST_ASSERT_EQUAL_INT(500, read_temperature_raw());
    // Expected: rand() should have been called once
    TEST_ASSERT_TRUE(stub_rand.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand.call_count);
}

void test_read_temperature_raw_returns_zero_when_rand_is_multiple_of_1024(void) {
    stub_rand.return_value = 1024; // Simulate rand() returning 1024
    // Expected: 1024 % 1024 = 0
    TEST_ASSERT_EQUAL_INT(0, read_temperature_raw());
    // Expected: rand() should have been called once
    TEST_ASSERT_TRUE(stub_rand.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand.call_count);
}

void test_read_temperature_raw_returns_max_value_from_range(void) {
    stub_rand.return_value = 1023; // Simulate rand() returning 1023
    // Expected: 1023 % 1024 = 1023 (max value from rand() % 1024)
    TEST_ASSERT_EQUAL_INT(1023, read_temperature_raw());
    // Expected: rand() should have been called once
    TEST_ASSERT_TRUE(stub_rand.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand.call_count);
}

// --- Tests for validate_temperature_range() ---

void test_validate_temperature_range_min_edge_valid(void) {
    float temp_c = 0.0f;
    // Expected: 0.0f is within [0.0f, 125.0f]
    TEST_ASSERT_TRUE(validate_temperature_range(temp_c));
}

void test_validate_temperature_range_max_edge_valid(void) {
    float temp_c = 125.0f;
    // Expected: 125.0f is within [0.0f, 125.0f]
    TEST_ASSERT_TRUE(validate_temperature_range(temp_c));
}

void test_validate_temperature_range_mid_range_valid(void) {
    float temp_c = 25.0f;
    // Expected: 25.0f is within [0.0f, 125.0f]
    TEST_ASSERT_TRUE(validate_temperature_range(temp_c));
}

void test_validate_temperature_range_just_below_min_invalid(void) {
    float temp_c = 0.0f;
    // Expected: 0.0f is outside [0.0f, 125.0f]
    TEST_ASSERT_FALSE(validate_temperature_range(temp_c));
}

void test_validate_temperature_range_just_above_max_invalid(void) {
    float temp_c = 125.1f;
    // Expected: 125.1f is outside [0.0f, 125.0f]
    TEST_ASSERT_FALSE(validate_temperature_range(temp_c));
}

void test_validate_temperature_range_far_below_min_invalid(void) {
    float temp_c = 0.0f;
    // Expected: 0.0f is outside [0.0f, 125.0f]
    TEST_ASSERT_FALSE(validate_temperature_range(temp_c));
}

void test_validate_temperature_range_far_above_max_invalid(void) {
    float temp_c = 200.0f;
    // Expected: 200.0f is outside [0.0f, 125.0f]
    TEST_ASSERT_FALSE(validate_temperature_range(temp_c));
}

// --- Tests for check_temperature_status() ---

void test_check_temperature_status_critical_above_threshold(void) {
    float temp_c = 120.1f;
    // Expected: 120.1f is > 120.0f, so status is "CRITICAL"
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(temp_c));
}

void test_check_temperature_status_critical_far_above_threshold(void) {
    float temp_c = 150.0f;
    // Expected: 150.0f is > 120.0f, so status is "CRITICAL"
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(temp_c));
}

void test_check_temperature_status_hot_just_above_threshold(void) {
    float temp_c = 85.1f;
    // Expected: 85.1f is > 85.0f and not > 120.0f, so status is "HOT"
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(temp_c));
}

void test_check_temperature_status_hot_at_critical_boundary(void) {
    float temp_c = 120.0f;
    // Expected: 120.0f is > 85.0f but not > 120.0f, so status is "HOT"
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(temp_c));
}

void test_check_temperature_status_normal_at_cold_boundary(void) {
    float temp_c = 0.0f;
    // Expected: 0.0f is not < 0.0f and not > 85.0f, so status is "NORMAL"
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(temp_c));
}

void test_check_temperature_status_normal_mid_range(void) {
    float temp_c = 25.0f;
    // Expected: 25.0f is not < 0.0f and not > 85.0f, so status is "NORMAL"
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(temp_c));
}

void test_check_temperature_status_normal_at_hot_boundary(void) {
    float temp_c = 85.0f;
    // Expected: 85.0f is not < 0.0f and not > 85.0f, so status is "NORMAL"
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(temp_c));
}

void test_check_temperature_status_cold_just_below_threshold(void) {
    float temp_c = 0.0f;
    // Expected: 0.0f is < 0.0f, so status is "COLD"
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(temp_c));
}

void test_check_temperature_status_cold_far_below_threshold(void) {
    float temp_c = 0.0f;
    // Expected: 0.0f is < 0.0f, so status is "COLD"
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(temp_c));
}

// --- Tests for get_temperature_celsius() ---

void test_get_temperature_celsius_successful_conversion(void) {
    stub_rand.return_value = 512; // Simulate raw ADC read of 512
    stub_raw_to_celsius.return_value = 25.5f; // Simulate conversion to 25.5 Celsius

    float result = get_temperature_celsius();

    // Expected: read_temperature_raw() calls rand() internally. raw_to_celsius() receives raw value.
    TEST_ASSERT_TRUE(stub_rand.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand.call_count);
    // Expected: raw_to_celsius should have been called once
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    // Expected: The raw value passed to raw_to_celsius should be rand_value % 1024
    TEST_ASSERT_EQUAL_INT(512 % 1024, stub_raw_to_celsius.last_raw_value);
    // Expected: The function should return the value from raw_to_celsius
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 25.5f, result);
}

void test_get_temperature_celsius_at_min_raw_value(void) {
    stub_rand.return_value = 0; // Simulate raw ADC read of 0
    stub_raw_to_celsius.return_value = 0.0f; // Simulate conversion to 0.0f Celsius

    float result = get_temperature_celsius();

    // Expected: raw_to_celsius should have been called with 0
    TEST_ASSERT_EQUAL_INT(0, stub_raw_to_celsius.last_raw_value);
    // Expected: Function returns 0.0f
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, result);
}

void test_get_temperature_celsius_at_max_raw_value(void) {
    stub_rand.return_value = 1023; // Simulate raw ADC read of 1023
    stub_raw_to_celsius.return_value = 125.0f; // Simulate conversion to 125.0 Celsius

    float result = get_temperature_celsius();

    // Expected: raw_to_celsius should have been called with 1023
    TEST_ASSERT_EQUAL_INT(1023, stub_raw_to_celsius.last_raw_value);
    // Expected: Function returns 125.0f
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 125.0f, result);
}

// --- Main Unity Test Runner ---


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_read_temperature_raw_returns_value_from_rand_modulo_1024);
    RUN_TEST(test_read_temperature_raw_returns_zero_when_rand_is_multiple_of_1024);
    RUN_TEST(test_read_temperature_raw_returns_max_value_from_range);
    RUN_TEST(test_validate_temperature_range_min_edge_valid);
    RUN_TEST(test_validate_temperature_range_max_edge_valid);
    RUN_TEST(test_validate_temperature_range_mid_range_valid);
    RUN_TEST(test_validate_temperature_range_just_below_min_invalid);
    RUN_TEST(test_validate_temperature_range_just_above_max_invalid);
    RUN_TEST(test_validate_temperature_range_far_below_min_invalid);
    RUN_TEST(test_validate_temperature_range_far_above_max_invalid);
    RUN_TEST(test_check_temperature_status_critical_above_threshold);
    RUN_TEST(test_check_temperature_status_critical_far_above_threshold);
    RUN_TEST(test_check_temperature_status_hot_just_above_threshold);
    RUN_TEST(test_check_temperature_status_hot_at_critical_boundary);
    RUN_TEST(test_check_temperature_status_normal_at_cold_boundary);
    RUN_TEST(test_check_temperature_status_normal_mid_range);
    RUN_TEST(test_check_temperature_status_normal_at_hot_boundary);
    RUN_TEST(test_check_temperature_status_cold_just_below_threshold);
    RUN_TEST(test_check_temperature_status_cold_far_below_threshold);
    RUN_TEST(test_get_temperature_celsius_successful_conversion);
    RUN_TEST(test_get_temperature_celsius_at_min_raw_value);
    RUN_TEST(test_get_temperature_celsius_at_max_raw_value);

    return UNITY_END();
}