/* test_temp_sensor.c – Auto-generated Expert Unity Tests */

#include "unity.h"
#include <stdbool.h> // Required for bool type
#include <string.h>  // Required for memset
#include <stdint.h>  // Required for uint32_t

// --- External Stub Declarations and Implementations ---
// This custom 'rand' function takes precedence over the standard library's 'rand'
// if this test file is compiled before any module that uses the standard 'rand'
// and links to this one. This allows deterministic testing of `read_temperature_raw`.
typedef struct {
    int return_value;
    uint32_t call_count;
} stub_rand_t;
static stub_rand_t stub_rand_instance = {0};

// Stub implementation for rand()
int rand(void) {
    stub_rand_instance.call_count++;
    return stub_rand_instance.return_value;
}

// Stub for the external dependency raw_to_celsius
// Signature inferred from usage: float raw_to_celsius(int raw_value)
typedef struct {
    float return_value;
    uint32_t call_count;
    int last_raw_value;
} stub_raw_to_celsius_t;
static stub_raw_to_celsius_t stub_raw_to_celsius_instance = {0};

// Stub implementation for raw_to_celsius
float raw_to_celsius(int raw_value) {
    stub_raw_to_celsius_instance.call_count++;
    stub_raw_to_celsius_instance.last_raw_value = raw_value;
    return stub_raw_to_celsius_instance.return_value;
}

// --- Source Under Test Includes ---
// This include provides the declarations for the functions being tested.
#include "temp_sensor.h"

// --- setUp and tearDown Functions ---
void setUp(void) {
    // Completely reset all stub control structures before each test
    memset(&stub_rand_instance, 0, sizeof(stub_rand_t));
    memset(&stub_raw_to_celsius_instance, 0, sizeof(stub_raw_to_celsius_t));
}

void tearDown(void) {
    // Completely reset all stub control structures after each test
    // (Redundant for isolation, but good practice for safety against memory corruption)
    memset(&stub_rand_instance, 0, sizeof(stub_rand_t));
    memset(&stub_raw_to_celsius_instance, 0, sizeof(stub_raw_to_celsius_t));
}

// --- Test Cases for read_temperature_raw() ---

void test_read_temperature_raw_normal_mid_range(void) {
    // Configure rand() stub to return a mid-range value
    stub_rand_instance.return_value = 500;
    int result = read_temperature_raw();
    // Expected: The raw value should be 500 as 500 < 1024
    TEST_ASSERT_EQUAL_INT(500, result);
    // Expected: rand() should have been called exactly once
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand_instance.call_count);
}

void test_read_temperature_raw_min_edge(void) {
    // Configure rand() stub to return the minimum raw value (0)
    stub_rand_instance.return_value = 0;
    int result = read_temperature_raw();
    // Expected: The raw value should be 0
    TEST_ASSERT_EQUAL_INT(0, result);
    // Expected: rand() should have been called exactly once
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand_instance.call_count);
}

void test_read_temperature_raw_max_edge(void) {
    // Configure rand() stub to return the maximum raw value (1023) within the % 1024 operation
    stub_rand_instance.return_value = 1023;
    int result = read_temperature_raw();
    // Expected: The raw value should be 1023
    TEST_ASSERT_EQUAL_INT(1023, result);
    // Expected: rand() should have been called exactly once
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand_instance.call_count);
}

void test_read_temperature_raw_above_modulo_limit(void) {
    // Configure rand() stub to return a value that tests the modulo operation (e.g., 2000 % 1024 = 976)
    stub_rand_instance.return_value = 2000;
    int result = read_temperature_raw();
    // Expected: The raw value should be 976 due to the 'rand() % 1024' operation
    TEST_ASSERT_EQUAL_INT(976, result);
    // Expected: rand() should have been called exactly once
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand_instance.call_count);
}

void test_read_temperature_raw_at_modulo_boundary(void) {
    // Configure rand() stub to return a value exactly at the modulo boundary (e.g., 1024 % 1024 = 0)
    stub_rand_instance.return_value = 1024;
    int result = read_temperature_raw();
    // Expected: The raw value should be 0 due to the 'rand() % 1024' operation
    TEST_ASSERT_EQUAL_INT(0, result);
    // Expected: rand() should have been called exactly once
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand_instance.call_count);
}

// --- Test Cases for validate_temperature_range() ---

void test_validate_temperature_range_valid_mid(void) {
    // Expected: 25.0f is within the valid range of [0.0f, 125.0f]
    TEST_ASSERT_TRUE(validate_temperature_range(25.0f));
}

void test_validate_temperature_range_valid_min_edge(void) {
    // Expected: 0.0f is precisely at the minimum valid edge
    TEST_ASSERT_TRUE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_invalid_below_min_edge(void) {
    // Expected: 0.0f is just below the minimum valid edge
    TEST_ASSERT_FALSE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_valid_max_edge(void) {
    // Expected: 125.0f is precisely at the maximum valid edge
    TEST_ASSERT_TRUE(validate_temperature_range(125.0f));
}

void test_validate_temperature_range_invalid_above_max_edge(void) {
    // Expected: 125.1f is just above the maximum valid edge
    TEST_ASSERT_FALSE(validate_temperature_range(125.1f));
}

void test_validate_temperature_range_invalid_far_below_min(void) {
    // Expected: 0.0f is significantly below the minimum valid range
    TEST_ASSERT_FALSE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_invalid_far_above_max(void) {
    // Expected: 200.0f is significantly above the maximum valid range
    TEST_ASSERT_FALSE(validate_temperature_range(200.0f));
}

// --- Test Cases for check_temperature_status() ---

void test_check_temperature_status_critical_above_120(void) {
    // Expected: 120.1f is greater than 120.0f, triggering "CRITICAL" status
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(120.1f));
}

void test_check_temperature_status_critical_max_valid_temp(void) {
    // Expected: 125.0f (maximum valid temperature) is greater than 120.0f, triggering "CRITICAL" status
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(125.0f));
}

void test_check_temperature_status_hot_above_85_lower_edge(void) {
    // Expected: 85.1f is greater than 85.0f but not greater than 120.0f, triggering "HOT" status
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(85.1f));
}

void test_check_temperature_status_hot_upper_edge_120(void) {
    // Expected: 120.0f is greater than 85.0f but not greater than 120.0f, triggering "HOT" status
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(120.0f));
}

void test_check_temperature_status_cold_below_neg10_upper_edge(void) {
    // Expected: 0.0f is less than 0.0f, triggering "COLD" status
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(0.0f));
}

void test_check_temperature_status_cold_min_valid_temp(void) {
    // Expected: 0.0f (minimum valid temperature) is less than 0.0f, triggering "COLD" status
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(0.0f));
}

void test_check_temperature_status_normal_neg10_lower_edge(void) {
    // Expected: 0.0f is not less than 0.0f, falling into the "NORMAL" range
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(0.0f));
}

void test_check_temperature_status_normal_zero(void) {
    // Expected: 0.0f is within the normal range [0.0f, 85.0f], triggering "NORMAL" status
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(0.0f));
}

void test_check_temperature_status_normal_mid_range(void) {
    // Expected: 25.0f is within the normal range [0.0f, 85.0f], triggering "NORMAL" status
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(25.0f));
}

void test_check_temperature_status_normal_85_upper_edge(void) {
    // Expected: 85.0f is not greater than 85.0f, falling into the "NORMAL" range
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(85.0f));
}

// --- Test Cases for get_temperature_celsius() ---

void test_get_temperature_celsius_normal_flow(void) {
    // Configure stubs: rand() returns a mid-range raw value (500), which raw_to_celsius converts to 25.0f
    stub_rand_instance.return_value = 500;
    stub_raw_to_celsius_instance.return_value = 25.0f;

    float result = get_temperature_celsius();

    // Expected: read_temperature_raw() (which calls our stubbed rand()) should have been called once
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand_instance.call_count);
    // Expected: raw_to_celsius() should have been called once
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius_instance.call_count);
    // Expected: raw_to_celsius() should have received the raw value 500
    TEST_ASSERT_EQUAL_INT(500, stub_raw_to_celsius_instance.last_raw_value);
    // Expected: The final temperature should be 25.0f with a tolerance of 0.1f
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 25.0f, result);
}

void test_get_temperature_celsius_min_raw_to_min_celsius(void) {
    // Configure stubs: rand() returns the minimum raw value (0), which raw_to_celsius converts to 0.0f
    stub_rand_instance.return_value = 0;
    stub_raw_to_celsius_instance.return_value = 0.0f;

    float result = get_temperature_celsius();

    // Expected: read_temperature_raw() (via rand()) should have been called once
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand_instance.call_count);
    // Expected: raw_to_celsius() should have been called once
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius_instance.call_count);
    // Expected: raw_to_celsius() should have received the raw value 0
    TEST_ASSERT_EQUAL_INT(0, stub_raw_to_celsius_instance.last_raw_value);
    // Expected: The final temperature should be 0.0f with a tolerance of 0.1f
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, result);
}

void test_get_temperature_celsius_max_raw_to_max_celsius(void) {
    // Configure stubs: rand() returns the maximum raw value (1023), which raw_to_celsius converts to 125.0f
    stub_rand_instance.return_value = 1023;
    stub_raw_to_celsius_instance.return_value = 125.0f;

    float result = get_temperature_celsius();

    // Expected: read_temperature_raw() (via rand()) should have been called once
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand_instance.call_count);
    // Expected: raw_to_celsius() should have been called once
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius_instance.call_count);
    // Expected: raw_to_celsius() should have received the raw value 1023
    TEST_ASSERT_EQUAL_INT(1023, stub_raw_to_celsius_instance.last_raw_value);
    // Expected: The final temperature should be 125.0f with a tolerance of 0.1f
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 125.0f, result);
}

// --- Main Test Runner ---


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_read_temperature_raw_normal_mid_range);
    RUN_TEST(test_read_temperature_raw_min_edge);
    RUN_TEST(test_read_temperature_raw_max_edge);
    RUN_TEST(test_read_temperature_raw_above_modulo_limit);
    RUN_TEST(test_read_temperature_raw_at_modulo_boundary);
    RUN_TEST(test_validate_temperature_range_valid_mid);
    RUN_TEST(test_validate_temperature_range_valid_min_edge);
    RUN_TEST(test_validate_temperature_range_invalid_below_min_edge);
    RUN_TEST(test_validate_temperature_range_valid_max_edge);
    RUN_TEST(test_validate_temperature_range_invalid_above_max_edge);
    RUN_TEST(test_validate_temperature_range_invalid_far_below_min);
    RUN_TEST(test_validate_temperature_range_invalid_far_above_max);
    RUN_TEST(test_check_temperature_status_critical_above_120);
    RUN_TEST(test_check_temperature_status_critical_max_valid_temp);
    RUN_TEST(test_check_temperature_status_hot_above_85_lower_edge);
    RUN_TEST(test_check_temperature_status_hot_upper_edge_120);
    RUN_TEST(test_check_temperature_status_cold_below_neg10_upper_edge);
    RUN_TEST(test_check_temperature_status_cold_min_valid_temp);
    RUN_TEST(test_check_temperature_status_normal_neg10_lower_edge);
    RUN_TEST(test_check_temperature_status_normal_zero);
    RUN_TEST(test_check_temperature_status_normal_mid_range);
    RUN_TEST(test_check_temperature_status_normal_85_upper_edge);
    RUN_TEST(test_get_temperature_celsius_normal_flow);
    RUN_TEST(test_get_temperature_celsius_min_raw_to_min_celsius);
    RUN_TEST(test_get_temperature_celsius_max_raw_to_max_celsius);

    return UNITY_END();
}