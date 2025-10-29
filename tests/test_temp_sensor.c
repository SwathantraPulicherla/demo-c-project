/* test_temp_sensor.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

// Include the header for the module under test to access its public API
#include "temp_sensor.h"

// EXTERNAL DEPENDENCY STUBS
// Stubs are provided ONLY for external functions that are NOT defined in
// the source file being tested (temp_sensor.c).
// For rand() from stdlib.h, a stub is provided to ensure deterministic behavior,
// as explicitly mandated for non-deterministic functions.

// Stub for rand() from stdlib.h
// Signature: int rand(void)
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

// Stub for raw_to_celsius
// Inferred signature from call in get_temperature_celsius(): float raw_to_celsius(int raw_value)
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

// SETUP AND TEARDOWN FUNCTIONS
// setUp() is called before each test function.
void setUp(void) {
    // Completely reset all stub control structures to their default, clean state.
    memset(&stub_rand, 0, sizeof(stub_rand));
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
}

// tearDown() is called after each test function.
void tearDown(void) {
    // Ensure all stub control structures are reset after the test completes,
    // guaranteeing full isolation between tests.
    memset(&stub_rand, 0, sizeof(stub_rand));
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
}

// TEST CASES FOR read_temperature_raw()
// This function internally calls rand() and applies a modulo operation.
// We stub rand() to ensure deterministic return values for testing.

void test_read_temperature_raw_returns_min_value_from_rand(void) {
    stub_rand.return_value = 0; // Simulate rand() returning 0
    int result = read_temperature_raw();
    // Expected: raw value 0 when rand() returns 0 (0 % 1024 = 0)
    TEST_ASSERT_EQUAL_INT(0, result);
    // Expected: rand() was called exactly once
    TEST_ASSERT_TRUE(stub_rand.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand.call_count);
}

void test_read_temperature_raw_returns_max_value_from_rand(void) {
    stub_rand.return_value = 1023; // Simulate rand() returning 1023
    int result = read_temperature_raw();
    // Expected: raw value 1023 when rand() returns 1023 (1023 % 1024 = 1023)
    TEST_ASSERT_EQUAL_INT(1023, result);
    // Expected: rand() was called exactly once
    TEST_ASSERT_TRUE(stub_rand.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand.call_count);
}

void test_read_temperature_raw_returns_mid_value_from_rand(void) {
    stub_rand.return_value = 512; // Simulate rand() returning a mid-range value
    int result = read_temperature_raw();
    // Expected: raw value 512 when rand() returns 512 (512 % 1024 = 512)
    TEST_ASSERT_EQUAL_INT(512, result);
    // Expected: rand() was called exactly once
    TEST_ASSERT_TRUE(stub_rand.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand.call_count);
}

void test_read_temperature_raw_returns_zero_when_rand_equals_modulo_divisor(void) {
    stub_rand.return_value = 1024; // Simulate rand() returning a value equal to the modulo divisor
    int result = read_temperature_raw();
    // Expected: raw value 0 when rand() returns 1024 (1024 % 1024 = 0)
    TEST_ASSERT_EQUAL_INT(0, result);
    // Expected: rand() was called exactly once
    TEST_ASSERT_TRUE(stub_rand.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand.call_count);
}

// TEST CASES FOR validate_temperature_range(float temp_c)
// This function validates if a given temperature is within 0.0f to 125.0f (inclusive).

void test_validate_temperature_range_valid_at_min_edge(void) {
    bool result = validate_temperature_range(0.0f);
    // Expected: 0.0f is valid (temp_c >= 0.0f)
    TEST_ASSERT_TRUE(result);
}

void test_validate_temperature_range_invalid_below_min_edge(void) {
    bool result = validate_temperature_range(0.0f);
    // Expected: 0.0f is invalid (temp_c < 0.0f)
    TEST_ASSERT_FALSE(result);
}

void test_validate_temperature_range_valid_at_max_edge(void) {
    bool result = validate_temperature_range(125.0f);
    // Expected: 125.0f is valid (temp_c <= 125.0f)
    TEST_ASSERT_TRUE(result);
}

void test_validate_temperature_range_invalid_above_max_edge(void) {
    bool result = validate_temperature_range(125.1f);
    // Expected: 125.1f is invalid (temp_c > 125.0f)
    TEST_ASSERT_FALSE(result);
}

void test_validate_temperature_range_valid_mid_range(void) {
    bool result = validate_temperature_range(25.0f);
    // Expected: 25.0f is valid (between 0.0f and 125.0f)
    TEST_ASSERT_TRUE(result);
}

void test_validate_temperature_range_valid_cold_mid_range(void) {
    bool result = validate_temperature_range(0.0f);
    // Expected: 0.0f is valid (between 0.0f and 125.0f)
    TEST_ASSERT_TRUE(result);
}

void test_validate_temperature_range_valid_hot_mid_range(void) {
    bool result = validate_temperature_range(100.0f);
    // Expected: 100.0f is valid (between 0.0f and 125.0f)
    TEST_ASSERT_TRUE(result);
}

// TEST CASES FOR check_temperature_status(float temp_c)
// This function categorizes temperature into CRITICAL, HOT, COLD, or NORMAL based on thresholds.

void test_check_temperature_status_critical_just_above_edge(void) {
    const char* status = check_temperature_status(120.1f);
    // Expected: 120.1f is CRITICAL (> 120.0f)
    TEST_ASSERT_EQUAL_STRING("CRITICAL", status);
}

void test_check_temperature_status_critical_high_value(void) {
    const char* status = check_temperature_status(122.5f);
    // Expected: 122.5f is CRITICAL (> 120.0f)
    TEST_ASSERT_EQUAL_STRING("CRITICAL", status);
}

void test_check_temperature_status_hot_at_critical_edge(void) {
    const char* status = check_temperature_status(120.0f);
    // Expected: 120.0f is HOT (not > 120.0f, but > 85.0f)
    TEST_ASSERT_EQUAL_STRING("HOT", status);
}

void test_check_temperature_status_hot_just_above_edge(void) {
    const char* status = check_temperature_status(85.1f);
    // Expected: 85.1f is HOT (> 85.0f)
    TEST_ASSERT_EQUAL_STRING("HOT", status);
}

void test_check_temperature_status_hot_mid_range(void) {
    const char* status = check_temperature_status(95.0f);
    // Expected: 95.0f is HOT (> 85.0f)
    TEST_ASSERT_EQUAL_STRING("HOT", status);
}

void test_check_temperature_status_cold_just_below_edge(void) {
    const char* status = check_temperature_status(0.0f);
    // Expected: 0.0f is COLD (< 0.0f)
    TEST_ASSERT_EQUAL_STRING("COLD", status);
}

void test_check_temperature_status_cold_low_value(void) {
    const char* status = check_temperature_status(0.0f);
    // Expected: 0.0f is COLD (< 0.0f)
    TEST_ASSERT_EQUAL_STRING("COLD", status);
}

void test_check_temperature_status_normal_at_cold_edge(void) {
    const char* status = check_temperature_status(0.0f);
    // Expected: 0.0f is NORMAL (not > 120.0f, not > 85.0f, not < 0.0f)
    TEST_ASSERT_EQUAL_STRING("NORMAL", status);
}

void test_check_temperature_status_normal_at_hot_edge(void) {
    const char* status = check_temperature_status(85.0f);
    // Expected: 85.0f is NORMAL (not > 120.0f, not > 85.0f)
    TEST_ASSERT_EQUAL_STRING("NORMAL", status);
}

void test_check_temperature_status_normal_mid_range(void) {
    const char* status = check_temperature_status(25.0f);
    // Expected: 25.0f is NORMAL (within the default range)
    TEST_ASSERT_EQUAL_STRING("NORMAL", status);
}

void test_check_temperature_status_normal_at_zero(void) {
    const char* status = check_temperature_status(0.0f);
    // Expected: 0.0f is NORMAL (within the default range)
    TEST_ASSERT_EQUAL_STRING("NORMAL", status);
}

// TEST CASES FOR get_temperature_celsius()
// This function orchestrates calls to read_temperature_raw() and raw_to_celsius().
// Both internal (read_temperature_raw) and external (raw_to_celsius) dependencies are controlled via stubs.

void test_get_temperature_celsius_normal_conversion_flow(void) {
    // Configure stub for rand() to control read_temperature_raw()
    stub_rand.return_value = 500; // Simulate raw sensor reading of 500
    // Configure stub for raw_to_celsius() to control the conversion logic
    stub_raw_to_celsius.return_value = 25.0f; // Simulate 500 raw converting to 25.0 Celsius

    float result = get_temperature_celsius();

    // Expected: read_temperature_raw() was implicitly called, meaning rand() was called once
    TEST_ASSERT_TRUE(stub_rand.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand.call_count);

    // Expected: raw_to_celsius() was called exactly once
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    // Expected: raw_to_celsius() received the raw value from read_temperature_raw() (i.e., 500)
    TEST_ASSERT_EQUAL_INT(500, stub_raw_to_celsius.last_raw_value);

    // Expected: the function returns the converted Celsius value
    // Using 0.1f as a domain-specific tolerance for temperature floats.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 25.0f, result);
}

void test_get_temperature_celsius_min_raw_value_conversion(void) {
    // Simulate min raw value possible from sensor
    stub_rand.return_value = 0;
    // Simulate conversion of 0 raw to min valid Celsius
    stub_raw_to_celsius.return_value = 0.0f;

    float result = get_temperature_celsius();

    // Expected: rand() was called once
    TEST_ASSERT_TRUE(stub_rand.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand.call_count);
    // Expected: raw_to_celsius() was called with 0
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    TEST_ASSERT_EQUAL_INT(0, stub_raw_to_celsius.last_raw_value);
    // Expected: function returns 0.0f
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, result);
}

void test_get_temperature_celsius_max_raw_value_conversion(void) {
    // Simulate max raw value possible from sensor
    stub_rand.return_value = 1023;
    // Simulate conversion of 1023 raw to max valid Celsius
    stub_raw_to_celsius.return_value = 125.0f;

    float result = get_temperature_celsius();

    // Expected: rand() was called once
    TEST_ASSERT_TRUE(stub_rand.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand.call_count);
    // Expected: raw_to_celsius() was called with 1023
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    TEST_ASSERT_EQUAL_INT(1023, stub_raw_to_celsius.last_raw_value);
    // Expected: function returns 125.0f
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 125.0f, result);
}

// MAIN function to run all test cases


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_read_temperature_raw_returns_min_value_from_rand);
    RUN_TEST(test_read_temperature_raw_returns_max_value_from_rand);
    RUN_TEST(test_read_temperature_raw_returns_mid_value_from_rand);
    RUN_TEST(test_read_temperature_raw_returns_zero_when_rand_equals_modulo_divisor);
    RUN_TEST(test_validate_temperature_range_valid_at_min_edge);
    RUN_TEST(test_validate_temperature_range_invalid_below_min_edge);
    RUN_TEST(test_validate_temperature_range_valid_at_max_edge);
    RUN_TEST(test_validate_temperature_range_invalid_above_max_edge);
    RUN_TEST(test_validate_temperature_range_valid_mid_range);
    RUN_TEST(test_validate_temperature_range_valid_cold_mid_range);
    RUN_TEST(test_validate_temperature_range_valid_hot_mid_range);
    RUN_TEST(test_check_temperature_status_critical_just_above_edge);
    RUN_TEST(test_check_temperature_status_critical_high_value);
    RUN_TEST(test_check_temperature_status_hot_at_critical_edge);
    RUN_TEST(test_check_temperature_status_hot_just_above_edge);
    RUN_TEST(test_check_temperature_status_hot_mid_range);
    RUN_TEST(test_check_temperature_status_cold_just_below_edge);
    RUN_TEST(test_check_temperature_status_cold_low_value);
    RUN_TEST(test_check_temperature_status_normal_at_cold_edge);
    RUN_TEST(test_check_temperature_status_normal_at_hot_edge);
    RUN_TEST(test_check_temperature_status_normal_mid_range);
    RUN_TEST(test_check_temperature_status_normal_at_zero);
    RUN_TEST(test_get_temperature_celsius_normal_conversion_flow);
    RUN_TEST(test_get_temperature_celsius_min_raw_value_conversion);
    RUN_TEST(test_get_temperature_celsius_max_raw_value_conversion);

    return UNITY_END();
}