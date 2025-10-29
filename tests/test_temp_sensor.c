/* test_temp_sensor.c – Auto-generated Expert Unity Tests */

#include "unity.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h> // For memset

// Include the header for the module under test to access its public API
#include "temp_sensor.h"

// --- EXTERNAL FUNCTION STUBS ---

// Stub for raw_to_celsius (inferred signature from temp_converter.h usage)
typedef struct {
    float return_value;
    bool was_called;
    uint32_t call_count;
    int last_raw_value;
} stub_raw_to_celsius_t;
static stub_raw_to_celsius_t stub_raw_to_celsius_obj = {0};

float raw_to_celsius(int raw_value) {
    stub_raw_to_celsius_obj.was_called = true;
    stub_raw_to_celsius_obj.call_count++;
    stub_raw_to_celsius_obj.last_raw_value = raw_value;
    return stub_raw_to_celsius_obj.return_value;
}

// Stub for rand() from stdlib.h (for deterministic testing of read_temperature_raw)
typedef struct {
    int return_value;
    bool was_called;
    uint32_t call_count;
} stub_rand_t;
static stub_rand_t stub_rand_obj = {0};

int rand(void) {
    stub_rand_obj.was_called = true;
    stub_rand_obj.call_count++;
    return stub_rand_obj.return_value;
}

// --- TEST FIXTURES ---

void setUp(void) {
    // Reset all stubs before each test
    memset(&stub_raw_to_celsius_obj, 0, sizeof(stub_raw_to_celsius_obj));
    memset(&stub_rand_obj, 0, sizeof(stub_rand_obj));
}

void tearDown(void) {
    // Ensure all stubs are fully reset after each test
    memset(&stub_raw_to_celsius_obj, 0, sizeof(stub_raw_to_celsius_obj));
    memset(&stub_rand_obj, 0, sizeof(stub_rand_obj));
}

// --- TEST CASES FOR read_temperature_raw ---

void test_read_temperature_raw_returns_value_in_range(void) {
    // Expected: The function should return the stubbed rand value modulo 1024
    stub_rand_obj.return_value = 500;
    int result = read_temperature_raw();
    TEST_ASSERT_EQUAL_INT(1, stub_rand_obj.call_count); // Expected: rand() called once
    TEST_ASSERT_EQUAL_INT(500, result); // Expected: 500 % 1024 = 500
}

void test_read_temperature_raw_returns_zero_on_modulo_match(void) {
    // Expected: The function should return 0 when rand() returns a multiple of 1024
    stub_rand_obj.return_value = 1024;
    int result = read_temperature_raw();
    TEST_ASSERT_EQUAL_INT(1, stub_rand_obj.call_count); // Expected: rand() called once
    TEST_ASSERT_EQUAL_INT(0, result); // Expected: 1024 % 1024 = 0
}

void test_read_temperature_raw_returns_max_value(void) {
    // Expected: The function should return 1023 when rand() is 1023 (max value before modulo wraps)
    stub_rand_obj.return_value = 1023;
    int result = read_temperature_raw();
    TEST_ASSERT_EQUAL_INT(1, stub_rand_obj.call_count); // Expected: rand() called once
    TEST_ASSERT_EQUAL_INT(1023, result); // Expected: 1023 % 1024 = 1023
}

void test_read_temperature_raw_large_value_mod_range(void) {
    // Expected: The function should correctly apply modulo even with a larger rand() return
    stub_rand_obj.return_value = 2047; // A value just below a multiple of 1024
    int result = read_temperature_raw();
    TEST_ASSERT_EQUAL_INT(1, stub_rand_obj.call_count); // Expected: rand() called once
    TEST_ASSERT_EQUAL_INT(1023, result); // Expected: 2047 % 1024 = 1023
}

// --- TEST CASES FOR validate_temperature_range ---

void test_validate_temperature_range_valid_min_edge(void) {
    // Expected: 0.0f is within the valid range [0.0f, 125.0f]
    bool result = validate_temperature_range(0.0f);
    TEST_ASSERT_TRUE(result);
}

void test_validate_temperature_range_invalid_below_min(void) {
    // Expected: 0.0f is below the valid range [0.0f, 125.0f]
    bool result = validate_temperature_range(0.0f);
    TEST_ASSERT_FALSE(result);
}

void test_validate_temperature_range_valid_max_edge(void) {
    // Expected: 125.0f is within the valid range [0.0f, 125.0f]
    bool result = validate_temperature_range(125.0f);
    TEST_ASSERT_TRUE(result);
}

void test_validate_temperature_range_invalid_above_max(void) {
    // Expected: 125.1f is above the valid range [0.0f, 125.0f]
    bool result = validate_temperature_range(125.1f);
    TEST_ASSERT_FALSE(result);
}

void test_validate_temperature_range_valid_mid_range(void) {
    // Expected: 25.0f is within the valid range [0.0f, 125.0f]
    bool result = validate_temperature_range(25.0f);
    TEST_ASSERT_TRUE(result);
}

// --- TEST CASES FOR check_temperature_status ---

void test_check_temperature_status_critical_above_edge(void) {
    // Expected: 120.1f is > 120.0f, so status is "CRITICAL"
    const char* status = check_temperature_status(120.1f);
    TEST_ASSERT_EQUAL_STRING("CRITICAL", status);
}

void test_check_temperature_status_critical_high(void) {
    // Expected: 125.0f (max valid temp) is > 120.0f, so status is "CRITICAL"
    const char* status = check_temperature_status(125.0f);
    TEST_ASSERT_EQUAL_STRING("CRITICAL", status);
}

void test_check_temperature_status_hot_above_edge(void) {
    // Expected: 85.1f is > 85.0f and <= 120.0f, so status is "HOT"
    const char* status = check_temperature_status(85.1f);
    TEST_ASSERT_EQUAL_STRING("HOT", status);
}

void test_check_temperature_status_hot_below_critical_edge(void) {
    // Expected: 120.0f is > 85.0f and NOT > 120.0f, so status is "HOT"
    const char* status = check_temperature_status(120.0f);
    TEST_ASSERT_EQUAL_STRING("HOT", status);
}

void test_check_temperature_status_cold_below_edge(void) {
    // Expected: 0.0f is < 0.0f, so status is "COLD"
    const char* status = check_temperature_status(0.0f);
    TEST_ASSERT_EQUAL_STRING("COLD", status);
}

void test_check_temperature_status_cold_low(void) {
    // Expected: 0.0f (min valid temp) is < 0.0f, so status is "COLD"
    const char* status = check_temperature_status(0.0f);
    TEST_ASSERT_EQUAL_STRING("COLD", status);
}

void test_check_temperature_status_normal_mid_range(void) {
    // Expected: 25.0f is not CRITICAL, HOT, or COLD, so status is "NORMAL"
    const char* status = check_temperature_status(25.0f);
    TEST_ASSERT_EQUAL_STRING("NORMAL", status);
}

void test_check_temperature_status_normal_cold_edge(void) {
    // Expected: 0.0f is NOT < 0.0f, so status is "NORMAL"
    const char* status = check_temperature_status(0.0f);
    TEST_ASSERT_EQUAL_STRING("NORMAL", status);
}

void test_check_temperature_status_normal_hot_edge(void) {
    // Expected: 85.0f is NOT > 85.0f, so status is "NORMAL"
    const char* status = check_temperature_status(85.0f);
    TEST_ASSERT_EQUAL_STRING("NORMAL", status);
}

// --- TEST CASES FOR get_temperature_celsius ---

void test_get_temperature_celsius_normal_flow(void) {
    // Expected: Calls read_temperature_raw (which calls rand), then raw_to_celsius, returns the converted value
    stub_rand_obj.return_value = 500; // read_temperature_raw will return 500
    stub_raw_to_celsius_obj.return_value = 25.5f; // raw_to_celsius(500) will return 25.5f

    float result = get_temperature_celsius();

    TEST_ASSERT_EQUAL_INT(1, stub_rand_obj.call_count); // Expected: rand() called once by read_temperature_raw
    TEST_ASSERT_EQUAL_INT(1, stub_raw_to_celsius_obj.call_count); // Expected: raw_to_celsius called once
    TEST_ASSERT_EQUAL_INT(500, stub_raw_to_celsius_obj.last_raw_value); // Expected: raw_to_celsius called with 500
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 25.5f, result); // Expected: Converted temperature is 25.5f
}

void test_get_temperature_celsius_edge_raw_min(void) {
    // Expected: Handles minimum raw value conversion
    stub_rand_obj.return_value = 0; // read_temperature_raw will return 0
    stub_raw_to_celsius_obj.return_value = 0.0f; // raw_to_celsius(0) will return 0.0f

    float result = get_temperature_celsius();

    TEST_ASSERT_EQUAL_INT(1, stub_rand_obj.call_count); // Expected: rand() called once
    TEST_ASSERT_EQUAL_INT(1, stub_raw_to_celsius_obj.call_count); // Expected: raw_to_celsius called once
    TEST_ASSERT_EQUAL_INT(0, stub_raw_to_celsius_obj.last_raw_value); // Expected: raw_to_celsius called with 0
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, result); // Expected: Converted temperature is 0.0f
}

void test_get_temperature_celsius_edge_raw_max(void) {
    // Expected: Handles maximum raw value conversion
    stub_rand_obj.return_value = 1023; // read_temperature_raw will return 1023
    stub_raw_to_celsius_obj.return_value = 125.0f; // raw_to_celsius(1023) will return 125.0f

    float result = get_temperature_celsius();

    TEST_ASSERT_EQUAL_INT(1, stub_rand_obj.call_count); // Expected: rand() called once
    TEST_ASSERT_EQUAL_INT(1, stub_raw_to_celsius_obj.call_count); // Expected: raw_to_celsius called once
    TEST_ASSERT_EQUAL_INT(1023, stub_raw_to_celsius_obj.last_raw_value); // Expected: raw_to_celsius called with 1023
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 125.0f, result); // Expected: Converted temperature is 125.0f
}

// --- MAIN RUNNER ---



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_read_temperature_raw_returns_value_in_range);
    RUN_TEST(test_read_temperature_raw_returns_zero_on_modulo_match);
    RUN_TEST(test_read_temperature_raw_returns_max_value);
    RUN_TEST(test_read_temperature_raw_large_value_mod_range);
    RUN_TEST(test_validate_temperature_range_valid_min_edge);
    RUN_TEST(test_validate_temperature_range_invalid_below_min);
    RUN_TEST(test_validate_temperature_range_valid_max_edge);
    RUN_TEST(test_validate_temperature_range_invalid_above_max);
    RUN_TEST(test_validate_temperature_range_valid_mid_range);
    RUN_TEST(test_check_temperature_status_critical_above_edge);
    RUN_TEST(test_check_temperature_status_critical_high);
    RUN_TEST(test_check_temperature_status_hot_above_edge);
    RUN_TEST(test_check_temperature_status_hot_below_critical_edge);
    RUN_TEST(test_check_temperature_status_cold_below_edge);
    RUN_TEST(test_check_temperature_status_cold_low);
    RUN_TEST(test_check_temperature_status_normal_mid_range);
    RUN_TEST(test_check_temperature_status_normal_cold_edge);
    RUN_TEST(test_check_temperature_status_normal_hot_edge);
    RUN_TEST(test_get_temperature_celsius_normal_flow);
    RUN_TEST(test_get_temperature_celsius_edge_raw_min);
    RUN_TEST(test_get_temperature_celsius_edge_raw_max);

    return UNITY_END();
}