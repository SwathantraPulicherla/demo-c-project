/* test_temp_sensor.c – Auto-generated Expert Unity Tests */

#include "unity.h"
#include "temp_sensor.h" // For the functions under test
#include <stdbool.h>   // For bool type
#include <string.h>    // For memset and strcmp
#include <stdint.h>    // For uint32_t in stub structs

// Forward declarations for external dependencies that will be stubbed
extern int rand(void);
extern float raw_to_celsius(int raw_value);

// --- Stub Definitions for External Dependencies ---

// Stub for rand()
typedef struct {
    int return_value;
    uint32_t call_count;
} stub_rand_t;
static stub_rand_t stub_rand_control = {0};

int rand(void) {
    stub_rand_control.call_count++;
    return stub_rand_control.return_value;
}

// Stub for raw_to_celsius()
typedef struct {
    float return_value;
    bool was_called;
    uint32_t call_count;
    int last_raw_value;
} stub_raw_to_celsius_t;
static stub_raw_to_celsius_t stub_raw_to_celsius_control = {0};

float raw_to_celsius(int raw_value) {
    stub_raw_to_celsius_control.was_called = true;
    stub_raw_to_celsius_control.call_count++;
    stub_raw_to_celsius_control.last_raw_value = raw_value;
    return stub_raw_to_celsius_control.return_value;
}

// --- Test Setup and Teardown ---

void setUp(void) {
    // Reset all stub control structures before each test
    memset(&stub_rand_control, 0, sizeof(stub_rand_control));
    memset(&stub_raw_to_celsius_control, 0, sizeof(stub_raw_to_celsius_control));
}

void tearDown(void) {
    // Reset all stub control structures after each test
    memset(&stub_rand_control, 0, sizeof(stub_rand_control));
    memset(&stub_raw_to_celsius_control, 0, sizeof(stub_raw_to_celsius_control));
}

// --- Test Cases for validate_temperature_range ---

void test_validate_temperature_range_valid_min_edge(void) {
    bool result = validate_temperature_range(0.0f);
    // Expected: 0.0f is within the valid range [0.0f, 125.0f]
    TEST_ASSERT_TRUE(result);
}

void test_validate_temperature_range_valid_max_edge(void) {
    bool result = validate_temperature_range(125.0f);
    // Expected: 125.0f is within the valid range [0.0f, 125.0f]
    TEST_ASSERT_TRUE(result);
}

void test_validate_temperature_range_valid_mid_range(void) {
    bool result = validate_temperature_range(25.0f);
    // Expected: 25.0f is within the valid range [0.0f, 125.0f]
    TEST_ASSERT_TRUE(result);
}

void test_validate_temperature_range_invalid_below_min(void) {
    bool result = validate_temperature_range(0.0f);
    // Expected: 0.0f is below the minimum valid temperature of 0.0f
    TEST_ASSERT_FALSE(result);
}

void test_validate_temperature_range_invalid_above_max(void) {
    bool result = validate_temperature_range(125.1f);
    // Expected: 125.1f is above the maximum valid temperature of 125.0f
    TEST_ASSERT_FALSE(result);
}

// --- Test Cases for check_temperature_status ---

void test_check_temperature_status_critical_above_max_edge(void) {
    const char* status = check_temperature_status(120.1f);
    // Expected: 120.1f is greater than 120.0f, so status is CRITICAL
    TEST_ASSERT_EQUAL_STRING("CRITICAL", status);
}

void test_check_temperature_status_critical_far_above(void) {
    const char* status = check_temperature_status(150.0f);
    // Expected: 150.0f is greater than 120.0f, so status is CRITICAL
    TEST_ASSERT_EQUAL_STRING("CRITICAL", status);
}

void test_check_temperature_status_hot_max_edge(void) {
    const char* status = check_temperature_status(85.1f);
    // Expected: 85.1f is greater than 85.0f but not greater than 120.0f, so status is HOT
    TEST_ASSERT_EQUAL_STRING("HOT", status);
}

void test_check_temperature_status_hot_below_critical_threshold(void) {
    const char* status = check_temperature_status(110.0f);
    // Expected: 110.0f is greater than 85.0f but not greater than 120.0f, so status is HOT
    TEST_ASSERT_EQUAL_STRING("HOT", status);
}

void test_check_temperature_status_normal_above_cold_edge(void) {
    const char* status = check_temperature_status(0.0f);
    // Expected: 0.0f is not less than 0.0f and not in HOT/CRITICAL, so status is NORMAL
    TEST_ASSERT_EQUAL_STRING("NORMAL", status);
}

void test_check_temperature_status_normal_below_hot_edge(void) {
    const char* status = check_temperature_status(85.0f);
    // Expected: 85.0f is not greater than 85.0f and not less than 0.0f, so status is NORMAL
    TEST_ASSERT_EQUAL_STRING("NORMAL", status);
}

void test_check_temperature_status_normal_mid_range(void) {
    const char* status = check_temperature_status(25.0f);
    // Expected: 25.0f is not in HOT/CRITICAL/COLD ranges, so status is NORMAL
    TEST_ASSERT_EQUAL_STRING("NORMAL", status);
}

void test_check_temperature_status_cold_min_edge(void) {
    const char* status = check_temperature_status(0.0f);
    // Expected: 0.0f is less than 0.0f, so status is COLD
    TEST_ASSERT_EQUAL_STRING("COLD", status);
}

void test_check_temperature_status_cold_far_below(void) {
    const char* status = check_temperature_status(0.0f);
    // Expected: 0.0f is less than 0.0f, so status is COLD
    TEST_ASSERT_EQUAL_STRING("COLD", status);
}

// --- Test Cases for get_temperature_celsius ---

void test_get_temperature_celsius_nominal(void) {
    // Configure stubs for a nominal scenario
    stub_rand_control.return_value = 512; // Simulate a mid-range raw value (00.0f)
    stub_raw_to_celsius_control.return_value = 25.0f; // Simulate conversion to a nominal Celsius value

    float result = get_temperature_celsius();

    // Expected: rand() was called once to get the raw value
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand_control.call_count);
    // Expected: raw_to_celsius() was called once with the raw value from rand()
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius_control.call_count);
    TEST_ASSERT_EQUAL_INT(512, stub_raw_to_celsius_control.last_raw_value);
    // Expected: The function returns the Celsius value provided by the stub
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 25.0f, result);
}

void test_get_temperature_celsius_min_raw_input(void) {
    // Configure stubs for the minimum possible raw value
    stub_rand_control.return_value = 0; // Smallest raw value from rand() % 1024
    stub_raw_to_celsius_control.return_value = 0.0f; // Example min Celsius output

    float result = get_temperature_celsius();

    // Expected: rand() was called once
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand_control.call_count);
    // Expected: raw_to_celsius() was called once with the minimum raw value
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius_control.call_count);
    TEST_ASSERT_EQUAL_INT(0, stub_raw_to_celsius_control.last_raw_value);
    // Expected: The function returns the Celsius value for the min raw
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, result);
}

void test_get_temperature_celsius_max_raw_input(void) {
    // Configure stubs for the maximum possible raw value
    stub_rand_control.return_value = 1023; // Largest raw value from rand() % 1024
    stub_raw_to_celsius_control.return_value = 125.0f; // Example max Celsius output

    float result = get_temperature_celsius();

    // Expected: rand() was called once
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand_control.call_count);
    // Expected: raw_to_celsius() was called once with the maximum raw value
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius_control.call_count);
    TEST_ASSERT_EQUAL_INT(1023, stub_raw_to_celsius_control.last_raw_value);
    // Expected: The function returns the Celsius value for the max raw
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 125.0f, result);
}

// --- Main Test Runner ---



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_validate_temperature_range_valid_min_edge);
    RUN_TEST(test_validate_temperature_range_valid_max_edge);
    RUN_TEST(test_validate_temperature_range_valid_mid_range);
    RUN_TEST(test_validate_temperature_range_invalid_below_min);
    RUN_TEST(test_validate_temperature_range_invalid_above_max);
    RUN_TEST(test_check_temperature_status_critical_above_max_edge);
    RUN_TEST(test_check_temperature_status_critical_far_above);
    RUN_TEST(test_check_temperature_status_hot_max_edge);
    RUN_TEST(test_check_temperature_status_hot_below_critical_threshold);
    RUN_TEST(test_check_temperature_status_normal_above_cold_edge);
    RUN_TEST(test_check_temperature_status_normal_below_hot_edge);
    RUN_TEST(test_check_temperature_status_normal_mid_range);
    RUN_TEST(test_check_temperature_status_cold_min_edge);
    RUN_TEST(test_check_temperature_status_cold_far_below);
    RUN_TEST(test_get_temperature_celsius_nominal);
    RUN_TEST(test_get_temperature_celsius_min_raw_input);
    RUN_TEST(test_get_temperature_celsius_max_raw_input);

    return UNITY_END();
}