/* test_temp_sensor.c – Auto-generated Expert Unity Tests */

#include "unity.h"
#include "temp_sensor.h" // For public API declarations
#include <stdbool.h>     // For bool type
#include <stdint.h>      // For uint32_t
#include <string.h>      // For memset

// ========================================================
// EXTERNAL FUNCTION PROTOTYPES FOR STUBBING
// These functions are external dependencies of temp_sensor.c
// and need to be stubbed for deterministic unit testing.
// ========================================================

// From temp_converter.h, called by get_temperature_celsius()
extern float raw_to_celsius(int raw_value);
// From stdlib.h, called by read_temperature_raw(), needs stubbing for determinism
extern int rand(void);

// ========================================================
// STUB DEFINITIONS AND CONTROL STRUCTURES
// ========================================================

// Control structure for the raw_to_celsius stub
typedef struct {
    float return_value;     // Configured return value for the stub
    bool was_called;        // Flag to check if the stub was called
    uint32_t call_count;    // Number of times the stub was called
    int last_raw_value;     // Captures the last raw_value parameter passed to the stub
} stub_raw_to_celsius_t;

static stub_raw_to_celsius_t stub_raw_to_celsius_control;

// Stub implementation for raw_to_celsius
float raw_to_celsius(int raw_value) {
    stub_raw_to_celsius_control.was_called = true;
    stub_raw_to_celsius_control.call_count++;
    stub_raw_to_celsius_control.last_raw_value = raw_value;
    return stub_raw_to_celsius_control.return_value;
}

// Control structure for the rand() stub (from stdlib.h)
// This is critical to make read_temperature_raw() deterministic.
typedef struct {
    int return_value;       // Configured return value for rand()
    bool was_called;        // Flag to check if rand() was called
    uint32_t call_count;    // Number of times rand() was called
} stub_rand_t;

static stub_rand_t stub_rand_control;

// Stub implementation for rand()
int rand(void) {
    stub_rand_control.was_called = true;
    stub_rand_control.call_count++;
    return stub_rand_control.return_value;
}

// ========================================================
// TEST FIXTURES (setUp and tearDown)
// ========================================================

void setUp(void) {
    // Completely reset all stub control structures before each test
    memset(&stub_raw_to_celsius_control, 0, sizeof(stub_raw_to_celsius_control));
    memset(&stub_rand_control, 0, sizeof(stub_rand_control));

    // Set safe default return values for stubs
    stub_raw_to_celsius_control.return_value = 0.0f;
    stub_rand_control.return_value = 0;
}

void tearDown(void) {
    // Completely reset all stub control structures after each test
    memset(&stub_raw_to_celsius_control, 0, sizeof(stub_raw_to_celsius_control));
    memset(&stub_rand_control, 0, sizeof(stub_rand_control));
}

// ========================================================
// TEST CASES FOR read_temperature_raw()
// This function calls rand(), which is stubbed to ensure determinism.
// ========================================================

void test_read_temperature_raw_min_value(void) {
    // Configure rand() stub to return 0, which should result in raw_value = 0 % 1024 = 0
    stub_rand_control.return_value = 0;
    int result = read_temperature_raw();

    // Expected: rand() should be called exactly once
    TEST_ASSERT_TRUE(stub_rand_control.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand_control.call_count);
    // Expected: raw temperature should be 0 because 0 % 1024 is 0
    TEST_ASSERT_EQUAL_INT(0, result);
}

void test_read_temperature_raw_mid_value(void) {
    // Configure rand() stub to return 512, which should result in raw_value = 512 % 1024 = 512
    stub_rand_control.return_value = 512;
    int result = read_temperature_raw();

    // Expected: rand() should be called exactly once
    TEST_ASSERT_TRUE(stub_rand_control.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand_control.call_count);
    // Expected: raw temperature should be 512 because 512 % 1024 is 512
    TEST_ASSERT_EQUAL_INT(512, result);
}

void test_read_temperature_raw_max_value(void) {
    // Configure rand() stub to return 1023, which should result in raw_value = 1023 % 1024 = 1023
    stub_rand_control.return_value = 1023;
    int result = read_temperature_raw();

    // Expected: rand() should be called exactly once
    TEST_ASSERT_TRUE(stub_rand_control.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand_control.call_count);
    // Expected: raw temperature should be 1023 because 1023 % 1024 is 1023
    TEST_ASSERT_EQUAL_INT(1023, result);
}

void test_read_temperature_raw_over_modulo_max_value(void) {
    // Configure rand() stub to return a value greater than 1023 but still yielding max after modulo
    stub_rand_control.return_value = 2047; // 2047 = 2 * 1024 + 1023
    int result = read_temperature_raw();

    // Expected: rand() should be called exactly once
    TEST_ASSERT_TRUE(stub_rand_control.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand_control.call_count);
    // Expected: raw temperature should be 1023 because 2047 % 1024 is 1023
    TEST_ASSERT_EQUAL_INT(1023, result);
}

// ========================================================
// TEST CASES FOR validate_temperature_range()
// Logic: return temp_c >= 0.0f && temp_c <= 125.0f;
// ========================================================

void test_validate_temperature_range_valid_min_edge(void) {
    // Test the exact lower boundary of the valid range [0.0f, 125.0f]
    TEST_ASSERT_TRUE(validate_temperature_range(0.0f)); // Expected: 0.0f is within the valid range
}

void test_validate_temperature_range_invalid_below_min(void) {
    // Test just below the lower boundary
    TEST_ASSERT_FALSE(validate_temperature_range(0.0f)); // Expected: 0.0f is outside the valid range
}

void test_validate_temperature_range_valid_max_edge(void) {
    // Test the exact upper boundary of the valid range
    TEST_ASSERT_TRUE(validate_temperature_range(125.0f)); // Expected: 125.0f is within the valid range
}

void test_validate_temperature_range_invalid_above_max(void) {
    // Test just above the upper boundary
    TEST_ASSERT_FALSE(validate_temperature_range(125.1f)); // Expected: 125.1f is outside the valid range
}

void test_validate_temperature_range_valid_mid_range(void) {
    // Test a typical value within the valid range
    TEST_ASSERT_TRUE(validate_temperature_range(25.0f)); // Expected: 25.0f is within the valid range
}

// ========================================================
// TEST CASES FOR check_temperature_status()
// Logic: > 120.0f -> "CRITICAL", > 85.0f -> "HOT", < 0.0f -> "COLD", else -> "NORMAL"
// ========================================================

void test_check_temperature_status_critical_above_threshold(void) {
    // Input is just above the CRITICAL threshold ( > 120.0f )
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(120.1f)); // Expected: 120.1f is > 120.0f
}

void test_check_temperature_status_hot_above_threshold(void) {
    // Input is just above the HOT threshold ( > 85.0f ), but not CRITICAL
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(85.1f)); // Expected: 85.1f is > 85.0f but not > 120.0f
}

void test_check_temperature_status_hot_at_critical_edge(void) {
    // Input is exactly at the CRITICAL threshold (120.0f), should fall into HOT as it's not strictly > 120.0f
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(120.0f)); // Expected: 120.0f is not > 120.0f, but it is > 85.0f
}

void test_check_temperature_status_cold_below_threshold(void) {
    // Input is just below the COLD threshold ( < 0.0f )
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(0.0f)); // Expected: 0.0f is < 0.0f
}

void test_check_temperature_status_normal_at_hot_edge(void) {
    // Input is exactly at the HOT threshold (85.0f), should fall into NORMAL as it's not strictly > 85.0f
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(85.0f)); // Expected: 85.0f is not > 85.0f, so it's NORMAL
}

void test_check_temperature_status_normal_at_cold_edge(void) {
    // Input is exactly at the COLD threshold (0.0f), should fall into NORMAL as it's not strictly < 0.0f
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(0.0f)); // Expected: 0.0f is not < 0.0f, so it's NORMAL
}

void test_check_temperature_status_normal_mid_range(void) {
    // Input is a typical normal temperature
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(25.0f)); // Expected: 25.0f falls into the NORMAL range
}

void test_check_temperature_status_normal_upper_range(void) {
    // Input is a high normal temperature, just below HOT threshold
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(84.9f)); // Expected: 84.9f is not > 85.0f, so it's NORMAL
}

void test_check_temperature_status_normal_lower_range(void) {
    // Input is a low normal temperature, just above COLD threshold
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(0.0f)); // Expected: 0.0f is not < 0.0f, so it's NORMAL
}

// ========================================================
// TEST CASES FOR get_temperature_celsius()
// This function calls read_temperature_raw() (internal) and raw_to_celsius() (external, stubbed).
// ========================================================

void test_get_temperature_celsius_normal_conversion(void) {
    // Configure stubs: rand() returns a mid-range raw value (512), raw_to_celsius converts it to a normal temp (25.5f)
    stub_rand_control.return_value = 512;
    stub_raw_to_celsius_control.return_value = 25.5f;

    float result = get_temperature_celsius();

    // Expected: rand() should be called once to get raw value
    TEST_ASSERT_TRUE(stub_rand_control.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand_control.call_count);
    // Expected: raw_to_celsius() should be called once with the raw value from rand() (512)
    TEST_ASSERT_TRUE(stub_raw_to_celsius_control.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius_control.call_count);
    TEST_ASSERT_EQUAL_INT(512, stub_raw_to_celsius_control.last_raw_value); // Expected: 512 passed to the converter stub
    // Expected: The final temperature should be the value configured for raw_to_celsius_control.return_value
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 25.5f, result); // Expected: 25.5f as converted temperature, with 0.1f tolerance
}

void test_get_temperature_celsius_min_raw_produces_min_celsius(void) {
    // Configure stubs for minimum raw value (0) resulting in minimum valid celsius (0.0f)
    stub_rand_control.return_value = 0;
    stub_raw_to_celsius_control.return_value = 0.0f;

    float result = get_temperature_celsius();

    // Expected: rand() called once, raw_to_celsius called once with raw value 0
    TEST_ASSERT_TRUE(stub_rand_control.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand_control.call_count);
    TEST_ASSERT_TRUE(stub_raw_to_celsius_control.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius_control.call_count);
    TEST_ASSERT_EQUAL_INT(0, stub_raw_to_celsius_control.last_raw_value); // Expected: 0 passed to the converter stub
    // Expected: The final temperature should be the configured minimum Celsius
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, result); // Expected: 0.0f as converted temperature, with 0.1f tolerance
}

void test_get_temperature_celsius_max_raw_produces_max_celsius(void) {
    // Configure stubs for maximum raw value (1023) resulting in maximum valid celsius (125.0f)
    stub_rand_control.return_value = 1023;
    stub_raw_to_celsius_control.return_value = 125.0f;

    float result = get_temperature_celsius();

    // Expected: rand() called once, raw_to_celsius called once with raw value 1023
    TEST_ASSERT_TRUE(stub_rand_control.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand_control.call_count);
    TEST_ASSERT_TRUE(stub_raw_to_celsius_control.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius_control.call_count);
    TEST_ASSERT_EQUAL_INT(1023, stub_raw_to_celsius_control.last_raw_value); // Expected: 1023 passed to the converter stub
    // Expected: The final temperature should be the configured maximum Celsius
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 125.0f, result); // Expected: 125.0f as converted temperature, with 0.1f tolerance
}

// ========================================================
// MAIN TEST RUNNER
// ========================================================



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_read_temperature_raw_min_value);
    RUN_TEST(test_read_temperature_raw_mid_value);
    RUN_TEST(test_read_temperature_raw_max_value);
    RUN_TEST(test_read_temperature_raw_over_modulo_max_value);
    RUN_TEST(test_validate_temperature_range_valid_min_edge);
    RUN_TEST(test_validate_temperature_range_invalid_below_min);
    RUN_TEST(test_validate_temperature_range_valid_max_edge);
    RUN_TEST(test_validate_temperature_range_invalid_above_max);
    RUN_TEST(test_validate_temperature_range_valid_mid_range);
    RUN_TEST(test_check_temperature_status_critical_above_threshold);
    RUN_TEST(test_check_temperature_status_hot_above_threshold);
    RUN_TEST(test_check_temperature_status_hot_at_critical_edge);
    RUN_TEST(test_check_temperature_status_cold_below_threshold);
    RUN_TEST(test_check_temperature_status_normal_at_hot_edge);
    RUN_TEST(test_check_temperature_status_normal_at_cold_edge);
    RUN_TEST(test_check_temperature_status_normal_mid_range);
    RUN_TEST(test_check_temperature_status_normal_upper_range);
    RUN_TEST(test_check_temperature_status_normal_lower_range);
    RUN_TEST(test_get_temperature_celsius_normal_conversion);
    RUN_TEST(test_get_temperature_celsius_min_raw_produces_min_celsius);
    RUN_TEST(test_get_temperature_celsius_max_raw_produces_max_celsius);

    return UNITY_END();
}