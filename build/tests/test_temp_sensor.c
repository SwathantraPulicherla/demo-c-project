/* test_temp_sensor.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include "temp_sensor.h" // Contains declarations for functions under test
#include <stdbool.h>     // For bool type
#include <stdint.h>      // For uint32_t in stub structures
#include <string.h>      // For memset in setUp/tearDown

// --- Mock/Stub for External Dependencies ---

// Stub for raw_to_celsius (declared in temp_converter.h, external to temp_sensor.c)
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

// Stub for rand() (from stdlib.h, external dependency to read_temperature_raw)
// This is necessary to make read_temperature_raw() deterministic for testing.
// A real build system would link this mock before the standard library's rand().
typedef struct {
    int return_value;
    bool was_called;
    uint32_t call_count;
} stub_rand_t;
static stub_rand_t stub_rand = {0};

// Extern declaration for rand() as we are providing a local stub.
extern int rand(void);
int rand(void) {
    stub_rand.was_called = true;
    stub_rand.call_count++;
    return stub_rand.return_value;
}

// --- Unity Test Framework Setup and Teardown ---

void setUp(void) {
    // Reset all stubs to a known state before each test
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius_t));
    memset(&stub_rand, 0, sizeof(stub_rand_t));
}

void tearDown(void) {
    // Ensure all stubs are reset after each test
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius_t));
    memset(&stub_rand, 0, sizeof(stub_rand_t));
}

// --- Test Cases for read_temperature_raw() ---

void test_read_temperature_raw_returns_zero_when_rand_is_zero(void) {
    stub_rand.return_value = 0; // Configure rand() to return 0
    int result = read_temperature_raw();
    // Expected: read_temperature_raw() should call rand() and return its value modulo 1024 (0 % 1024 = 0)
    TEST_ASSERT_TRUE(stub_rand.was_called);
    TEST_ASSERT_EQUAL_INT(1, stub_rand.call_count);
    TEST_ASSERT_EQUAL_INT(0, result);
}

void test_read_temperature_raw_returns_max_when_rand_is_max_modulo(void) {
    stub_rand.return_value = 1023; // Configure rand() to return 1023
    int result = read_temperature_raw();
    // Expected: read_temperature_raw() should call rand() and return its value modulo 1024 (1023 % 1024 = 1023)
    TEST_ASSERT_TRUE(stub_rand.was_called);
    TEST_ASSERT_EQUAL_INT(1, stub_rand.call_count);
    TEST_ASSERT_EQUAL_INT(1023, result);
}

void test_read_temperature_raw_returns_mid_range(void) {
    stub_rand.return_value = 500; // Configure rand() to return 500
    int result = read_temperature_raw();
    // Expected: read_temperature_raw() should call rand() and return its value modulo 1024 (500 % 1024 = 500)
    TEST_ASSERT_TRUE(stub_rand.was_called);
    TEST_ASSERT_EQUAL_INT(1, stub_rand.call_count);
    TEST_ASSERT_EQUAL_INT(500, result);
}

void test_read_temperature_raw_returns_wrapped_value_over_max(void) {
    stub_rand.return_value = 1024; // Configure rand() to return 1024, which should wrap to 0
    int result = read_temperature_raw();
    // Expected: read_temperature_raw() should call rand() and return its value modulo 1024 (1024 % 1024 = 0)
    TEST_ASSERT_TRUE(stub_rand.was_called);
    TEST_ASSERT_EQUAL_INT(1, stub_rand.call_count);
    TEST_ASSERT_EQUAL_INT(0, result);
}

// --- Test Cases for validate_temperature_range() ---

void test_validate_temperature_range_min_valid_edge(void) {
    // Expected: 0.0f is valid, so true
    TEST_ASSERT_TRUE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_min_invalid_edge(void) {
    // Expected: 0.0f is below min range, so false
    TEST_ASSERT_FALSE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_max_valid_edge(void) {
    // Expected: 125.0f is valid, so true
    TEST_ASSERT_TRUE(validate_temperature_range(125.0f));
}

void test_validate_temperature_range_max_invalid_edge(void) {
    // Expected: 125.1f is above max range, so false
    TEST_ASSERT_FALSE(validate_temperature_range(125.1f));
}

void test_validate_temperature_range_mid_valid(void) {
    // Expected: 25.0f is within range, so true
    TEST_ASSERT_TRUE(validate_temperature_range(25.0f));
}

void test_validate_temperature_range_out_of_range_low(void) {
    // Expected: 0.0f is below min range, so false
    TEST_ASSERT_FALSE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_out_of_range_high(void) {
    // Expected: 150.0f is above max range, so false
    TEST_ASSERT_FALSE(validate_temperature_range(150.0f));
}

// --- Test Cases for check_temperature_status() ---

void test_check_temperature_status_critical_high_edge(void) {
    // Expected: 120.1f is > 120.0f, so "CRITICAL"
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(120.1f));
}

void test_check_temperature_status_critical_max_valid_temp(void) {
    // Expected: 125.0f is > 120.0f, so "CRITICAL"
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(125.0f));
}

void test_check_temperature_status_hot_edge_below_critical(void) {
    // Expected: 120.0f is not > 120.0f, but is > 85.0f, so "HOT"
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(120.0f));
}

void test_check_temperature_status_hot_mid_range(void) {
    // Expected: 100.0f is not > 120.0f, but is > 85.0f, so "HOT"
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(100.0f));
}

void test_check_temperature_status_hot_min_edge(void) {
    // Expected: 85.1f is not > 120.0f, but is > 85.0f, so "HOT"
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(85.1f));
}

void test_check_temperature_status_cold_edge(void) {
    // Expected: 0.0f is < 0.0f, so "COLD"
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(0.0f));
}

void test_check_temperature_status_cold_mid_range(void) {
    // Expected: 0.0f is < 0.0f, so "COLD"
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(0.0f));
}

void test_check_temperature_status_cold_min_valid_temp(void) {
    // Expected: 0.0f is < 0.0f, so "COLD"
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(0.0f));
}

void test_check_temperature_status_normal_edge_above_cold(void) {
    // Expected: 0.0f is not < 0.0f, not > 85.0f, not > 120.0f, so "NORMAL"
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(0.0f));
}

void test_check_temperature_status_normal_edge_below_hot(void) {
    // Expected: 85.0f is not > 85.0f, not > 120.0f, so "NORMAL"
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(85.0f));
}

void test_check_temperature_status_normal_mid_range_zero(void) {
    // Expected: 0.0f falls into the "NORMAL" range
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(0.0f));
}

void test_check_temperature_status_normal_mid_range_positive(void) {
    // Expected: 25.0f falls into the "NORMAL" range
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(25.0f));
}

// --- Test Cases for get_temperature_celsius() ---

void test_get_temperature_celsius_normal_raw_conversion(void) {
    stub_rand.return_value = 500;             // raw = 500
    stub_raw_to_celsius.return_value = 25.0f; // raw_to_celsius(500) returns 25.0f

    float result = get_temperature_celsius();

    // Expected: read_temperature_raw() (via stub_rand) was called
    TEST_ASSERT_TRUE(stub_rand.was_called);
    TEST_ASSERT_EQUAL_INT(1, stub_rand.call_count);
    // Expected: raw_to_celsius() was called with the value from read_temperature_raw()
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    TEST_ASSERT_EQUAL_INT(1, stub_raw_to_celsius.call_count);
    TEST_ASSERT_EQUAL_INT(500, stub_raw_to_celsius.last_raw_value);
    // Expected: get_temperature_celsius() returns the value from raw_to_celsius()
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 25.0f, result);
}

void test_get_temperature_celsius_min_raw_conversion(void) {
    stub_rand.return_value = 0;               // raw = 0
    stub_raw_to_celsius.return_value = 0.0f; // raw_to_celsius(0) returns 0.0f

    float result = get_temperature_celsius();

    // Expected: raw_to_celsius() was called with 0
    TEST_ASSERT_EQUAL_INT(0, stub_raw_to_celsius.last_raw_value);
    // Expected: get_temperature_celsius() returns 0.0f
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, result);
}

void test_get_temperature_celsius_max_raw_conversion(void) {
    stub_rand.return_value = 1023;            // raw = 1023
    stub_raw_to_celsius.return_value = 125.0f; // raw_to_celsius(1023) returns 125.0f

    float result = get_temperature_celsius();

    // Expected: raw_to_celsius() was called with 1023
    TEST_ASSERT_EQUAL_INT(1023, stub_raw_to_celsius.last_raw_value);
    // Expected: get_temperature_celsius() returns 125.0f
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 125.0f, result);
}

// --- Main Test Runner ---


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_read_temperature_raw_returns_zero_when_rand_is_zero);
    RUN_TEST(test_read_temperature_raw_returns_max_when_rand_is_max_modulo);
    RUN_TEST(test_read_temperature_raw_returns_mid_range);
    RUN_TEST(test_read_temperature_raw_returns_wrapped_value_over_max);
    RUN_TEST(test_validate_temperature_range_min_valid_edge);
    RUN_TEST(test_validate_temperature_range_min_invalid_edge);
    RUN_TEST(test_validate_temperature_range_max_valid_edge);
    RUN_TEST(test_validate_temperature_range_max_invalid_edge);
    RUN_TEST(test_validate_temperature_range_mid_valid);
    RUN_TEST(test_validate_temperature_range_out_of_range_low);
    RUN_TEST(test_validate_temperature_range_out_of_range_high);
    RUN_TEST(test_check_temperature_status_critical_high_edge);
    RUN_TEST(test_check_temperature_status_critical_max_valid_temp);
    RUN_TEST(test_check_temperature_status_hot_edge_below_critical);
    RUN_TEST(test_check_temperature_status_hot_mid_range);
    RUN_TEST(test_check_temperature_status_hot_min_edge);
    RUN_TEST(test_check_temperature_status_cold_edge);
    RUN_TEST(test_check_temperature_status_cold_mid_range);
    RUN_TEST(test_check_temperature_status_cold_min_valid_temp);
    RUN_TEST(test_check_temperature_status_normal_edge_above_cold);
    RUN_TEST(test_check_temperature_status_normal_edge_below_hot);
    RUN_TEST(test_check_temperature_status_normal_mid_range_zero);
    RUN_TEST(test_check_temperature_status_normal_mid_range_positive);
    RUN_TEST(test_get_temperature_celsius_normal_raw_conversion);
    RUN_TEST(test_get_temperature_celsius_min_raw_conversion);
    RUN_TEST(test_get_temperature_celsius_max_raw_conversion);

    return UNITY_END();
}