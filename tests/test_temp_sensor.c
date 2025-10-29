/* test_temp_sensor.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>      // Required for `rand` prototype if defining it.
#include "temp_sensor.h" // Assumed to declare functions from temp_sensor.c

// --- Mock for external dependency: raw_to_celsius ---
// Signature inferred from usage: float raw_to_celsius(int raw_value)
typedef struct {
    float return_value;
    bool was_called;
    uint32_t call_count;
    int last_raw_value;
} stub_raw_to_celsius_t;
static stub_raw_to_celsius_t stub_raw_to_celsius_data = {0};

float raw_to_celsius(int raw_value) {
    stub_raw_to_celsius_data.was_called = true;
    stub_raw_to_celsius_data.call_count++;
    stub_raw_to_celsius_data.last_raw_value = raw_value;
    return stub_raw_to_celsius_data.return_value;
}

// --- Mock for non-deterministic function: rand() ---
// Rule: "For non-deterministic (e.g., rand-based): Stub to make deterministic"
// This definition of rand() is provided to override the standard library's rand()
// during linking for the test build (e.g., using `--wrap=rand` linker flag).
typedef struct {
    int return_value;
    bool was_called;
    uint32_t call_count;
} stub_rand_t;
static stub_rand_t stub_rand_data = {0};

int rand(void) {
    stub_rand_data.was_called = true;
    stub_rand_data.call_count++;
    return stub_rand_data.return_value;
}

void setUp(void) {
    // Reset all stubs to ensure complete test isolation
    memset(&stub_raw_to_celsius_data, 0, sizeof(stub_raw_to_celsius_data));
    memset(&stub_rand_data, 0, sizeof(stub_rand_data));
}

void tearDown(void) {
    // Reset all stubs (mandated for complete cleanup, even if redundant after setUp)
    memset(&stub_raw_to_celsius_data, 0, sizeof(stub_raw_to_celsius_data));
    memset(&stub_rand_data, 0, sizeof(stub_rand_data));
}

// --- Tests for read_temperature_raw() ---
// This function calls rand() % 1024. We control rand() via stub_rand_data.
void test_read_temperature_raw_returns_min_value(void) {
    stub_rand_data.return_value = 0; // Configure rand to return 0
    int raw_temp = read_temperature_raw();
    // Expected: raw temperature should be 0, as per 0 % 1024
    TEST_ASSERT_EQUAL_INT(0, raw_temp);
    // Expected: rand() was called once
    TEST_ASSERT_TRUE(stub_rand_data.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand_data.call_count);
}

void test_read_temperature_raw_returns_max_value(void) {
    stub_rand_data.return_value = 1023; // Configure rand to return 1023
    int raw_temp = read_temperature_raw();
    // Expected: raw temperature should be 1023, as per 1023 % 1024
    TEST_ASSERT_EQUAL_INT(1023, raw_temp);
    // Expected: rand() was called once
    TEST_ASSERT_TRUE(stub_rand_data.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand_data.call_count);
}

void test_read_temperature_raw_returns_mid_value(void) {
    stub_rand_data.return_value = 512; // Configure rand to return 512
    int raw_temp = read_temperature_raw();
    // Expected: raw temperature should be 512, as per 512 % 1024
    TEST_ASSERT_EQUAL_INT(512, raw_temp);
    // Expected: rand() was called once
    TEST_ASSERT_TRUE(stub_rand_data.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand_data.call_count);
}

// --- Tests for validate_temperature_range(float temp_c) ---
void test_validate_temperature_range_valid_mid_range(void) {
    // Expected: 25.0f is within the valid range [0.0f, 125.0f]
    TEST_ASSERT_TRUE(validate_temperature_range(25.0f));
}

void test_validate_temperature_range_valid_min_edge(void) {
    // Expected: 0.0f is at the lower boundary, which is inclusive
    TEST_ASSERT_TRUE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_valid_max_edge(void) {
    // Expected: 125.0f is at the upper boundary, which is inclusive
    TEST_ASSERT_TRUE(validate_temperature_range(125.0f));
}

void test_validate_temperature_range_invalid_below_min(void) {
    // Expected: 0.0f is just below the lower boundary 0.0f, so it should be invalid
    TEST_ASSERT_FALSE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_invalid_above_max(void) {
    // Expected: 125.1f is just above the upper boundary 125.0f, so it should be invalid
    TEST_ASSERT_FALSE(validate_temperature_range(125.1f));
}

// --- Tests for check_temperature_status(float temp_c) ---
void test_check_temperature_status_critical_just_above_120(void) {
    // Expected: 120.001f is > 120.0f, thus "CRITICAL"
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(120.001f));
}

void test_check_temperature_status_normal_at_120_edge(void) {
    // Expected: 120.0f is NOT > 120.0f, thus falls to next 'else if' which is also not met, and ends up "NORMAL"
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(120.0f));
}

void test_check_temperature_status_hot_just_above_85(void) {
    // Expected: 85.001f is > 85.0f but not > 120.0f, thus "HOT"
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(85.001f));
}

void test_check_temperature_status_normal_at_85_edge(void) {
    // Expected: 85.0f is NOT > 85.0f and NOT > 120.0f, thus falls to next 'else if', then "NORMAL"
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(85.0f));
}

void test_check_temperature_status_normal_mid_range(void) {
    // Expected: 25.0f is not > 120.0f, not > 85.0f, not < 0.0f, thus "NORMAL"
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(25.0f));
}

void test_check_temperature_status_normal_at_minus_10_edge(void) {
    // Expected: 0.0f is not > 120.0f, not > 85.0f, not < 0.0f, thus "NORMAL"
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(0.0f));
}

void test_check_temperature_status_cold_just_below_minus_10(void) {
    // Expected: 0.0f is < 0.0f, thus "COLD"
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(0.0f));
}

void test_check_temperature_status_cold_extreme_min_valid(void) {
    // Expected: 0.0f is < 0.0f, thus "COLD"
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(0.0f));
}

// --- Tests for get_temperature_celsius() ---
void test_get_temperature_celsius_normal_raw_to_normal_celsius(void) {
    // Configure rand() stub to return a mid-range value for raw temp
    stub_rand_data.return_value = 500; // read_temperature_raw() will return 500 % 1024 = 500
    // Configure raw_to_celsius stub for the expected raw input
    stub_raw_to_celsius_data.return_value = 25.5f; // Expected Celsius for 500 raw

    float result = get_temperature_celsius();

    // Expected: read_temperature_raw() (via rand()) called once
    TEST_ASSERT_TRUE(stub_rand_data.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand_data.call_count);
    // Expected: raw_to_celsius() called once with raw value (500 % 1024 = 500)
    TEST_ASSERT_TRUE(stub_raw_to_celsius_data.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius_data.call_count);
    TEST_ASSERT_EQUAL_INT(500 % 1024, stub_raw_to_celsius_data.last_raw_value); // Parameter passed was 500
    // Expected: Result is the stubbed Celsius value with 0.1f tolerance for temperature
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 25.5f, result);
}

void test_get_temperature_celsius_min_raw_to_min_celsius(void) {
    // Configure rand() stub to return a value that results in minimum raw temp
    stub_rand_data.return_value = 0; // read_temperature_raw() will return 0 % 1024 = 0
    // Configure raw_to_celsius stub for the expected raw input
    stub_raw_to_celsius_data.return_value = 0.0f; // Expected Celsius for 0 raw

    float result = get_temperature_celsius();

    // Expected: read_temperature_raw() (via rand()) called once
    TEST_ASSERT_TRUE(stub_rand_data.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand_data.call_count);
    // Expected: raw_to_celsius() called once with raw value 0
    TEST_ASSERT_TRUE(stub_raw_to_celsius_data.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius_data.call_count);
    TEST_ASSERT_EQUAL_INT(0, stub_raw_to_celsius_data.last_raw_value);
    // Expected: Result is the stubbed Celsius value with 0.1f tolerance for temperature
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, result);
}

void test_get_temperature_celsius_max_raw_to_max_celsius(void) {
    // Configure rand() stub to return a value that results in maximum raw temp
    stub_rand_data.return_value = 1023; // read_temperature_raw() will return 1023 % 1024 = 1023
    // Configure raw_to_celsius stub for the expected raw input
    stub_raw_to_celsius_data.return_value = 125.0f; // Expected Celsius for 1023 raw

    float result = get_temperature_celsius();

    // Expected: read_temperature_raw() (via rand()) called once
    TEST_ASSERT_TRUE(stub_rand_data.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand_data.call_count);
    // Expected: raw_to_celsius() called once with raw value 1023
    TEST_ASSERT_TRUE(stub_raw_to_celsius_data.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius_data.call_count);
    TEST_ASSERT_EQUAL_INT(1023, stub_raw_to_celsius_data.last_raw_value);
    // Expected: Result is the stubbed Celsius value with 0.1f tolerance for temperature
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 125.0f, result);
}


// --- Main Test Runner ---


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_read_temperature_raw_returns_min_value);
    RUN_TEST(test_read_temperature_raw_returns_max_value);
    RUN_TEST(test_read_temperature_raw_returns_mid_value);
    RUN_TEST(test_validate_temperature_range_valid_mid_range);
    RUN_TEST(test_validate_temperature_range_valid_min_edge);
    RUN_TEST(test_validate_temperature_range_valid_max_edge);
    RUN_TEST(test_validate_temperature_range_invalid_below_min);
    RUN_TEST(test_validate_temperature_range_invalid_above_max);
    RUN_TEST(test_check_temperature_status_critical_just_above_120);
    RUN_TEST(test_check_temperature_status_normal_at_120_edge);
    RUN_TEST(test_check_temperature_status_hot_just_above_85);
    RUN_TEST(test_check_temperature_status_normal_at_85_edge);
    RUN_TEST(test_check_temperature_status_normal_mid_range);
    RUN_TEST(test_check_temperature_status_normal_at_minus_10_edge);
    RUN_TEST(test_check_temperature_status_cold_just_below_minus_10);
    RUN_TEST(test_check_temperature_status_cold_extreme_min_valid);
    RUN_TEST(test_get_temperature_celsius_normal_raw_to_normal_celsius);
    RUN_TEST(test_get_temperature_celsius_min_raw_to_min_celsius);
    RUN_TEST(test_get_temperature_celsius_max_raw_to_max_celsius);

    return UNITY_END();
}