#include "unity.h"
#include "temp_sensor.h" // For functions under test
#include "temp_converter.h" // For raw_to_celsius (which will be stubbed)
#include <stdbool.h>
#include <stdint.h>
#include <string.h> // For memset, strcmp
#include <stdlib.h> // For rand() in the real read_temperature_raw; needed for linking against source object

// ==============================================================================
// STUB IMPLEMENTATIONS
// ==============================================================================

// Stub for raw_to_celsius function
typedef struct {
    float return_value;
    bool was_called;
    uint32_t call_count;
    int captured_raw; // Capture argument for validation
} stub_raw_to_celsius_t;
stub_raw_to_celsius_t stub_raw_to_celsius_config;

// Mock implementation for raw_to_celsius
float raw_to_celsius(int raw) {
    stub_raw_to_celsius_config.was_called = true;
    stub_raw_to_celsius_config.call_count++;
    stub_raw_to_celsius_config.captured_raw = raw;
    return stub_raw_to_celsius_config.return_value;
}

// Stub for read_temperature_raw function
// The prompt states to test read_temperature_raw but also to "BAN random values".
// Since read_temperature_raw internally uses rand(), it cannot be meaningfully tested
// directly while adhering to the "BAN random values" mandate.
// Therefore, it is only stubbed to provide deterministic behavior for functions
// that depend on it (e.g., get_temperature_celsius).
typedef struct {
    int return_value;
    bool was_called;
    uint32_t call_count;
} stub_read_temperature_raw_t;
stub_read_temperature_raw_t stub_read_temperature_raw_config;

// Mock implementation for read_temperature_raw
int read_temperature_raw() {
    stub_read_temperature_raw_config.was_called = true;
    stub_read_temperature_raw_config.call_count++;
    return stub_read_temperature_raw_config.return_value;
}

// ==============================================================================
// TEST FIXTURES
// ==============================================================================

void setUp(void) {
    // Reset all stub configurations to ensure test isolation
    memset(&stub_raw_to_celsius_config, 0, sizeof(stub_raw_to_celsius_t));
    memset(&stub_read_temperature_raw_config, 0, sizeof(stub_read_temperature_raw_t));
}

void tearDown(void) {
    // Complete cleanup and reset for ALL stubs after each test
    memset(&stub_raw_to_celsius_config, 0, sizeof(stub_raw_to_celsius_t));
    memset(&stub_read_temperature_raw_config, 0, sizeof(stub_read_temperature_raw_t));
}

// ==============================================================================
// TESTS FOR validate_temperature_range
// ==============================================================================

void test_validate_temperature_range_nominal_valid(void) {
    // Expected: 25.0f is within the valid range [0.0f, 125.0f]
    TEST_ASSERT_TRUE(validate_temperature_range(25.0f));
}

void test_validate_temperature_range_min_edge_valid(void) {
    // Expected: 0.0f is the exact minimum valid temperature
    TEST_ASSERT_TRUE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_max_edge_valid(void) {
    // Expected: 125.0f is the exact maximum valid temperature
    TEST_ASSERT_TRUE(validate_temperature_range(125.0f));
}

void test_validate_temperature_range_below_min_invalid(void) {
    // Expected: 0.0f is strictly below the minimum valid temperature
    TEST_ASSERT_FALSE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_above_max_invalid(void) {
    // Expected: 125.1f is strictly above the maximum valid temperature
    TEST_ASSERT_FALSE(validate_temperature_range(125.1f));
}

void test_validate_temperature_range_zero_valid(void) {
    // Expected: 0.0f is a valid temperature within the range
    TEST_ASSERT_TRUE(validate_temperature_range(0.0f));
}

// ==============================================================================
// TESTS FOR check_temperature_status
// ==============================================================================

void test_check_temperature_status_critical_above_120(void) {
    // Expected: Temperature 120.1f is above 120.0f, thus "CRITICAL"
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(120.1f));
}

void test_check_temperature_status_critical_at_max_valid(void) {
    // Expected: Temperature 125.0f (maximum physical limit) is "CRITICAL"
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(125.0f));
}

void test_check_temperature_status_hot_above_85(void) {
    // Expected: Temperature 85.1f is above 85.0f, thus "HOT"
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(85.1f));
}

void test_check_temperature_status_hot_at_boundary_below_critical(void) {
    // Expected: Temperature 120.0f is not strictly greater than 120.0f, thus "HOT"
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(120.0f));
}

void test_check_temperature_status_normal_nominal(void) {
    // Expected: Temperature 25.0f is within the "NORMAL" range
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(25.0f));
}

void test_check_temperature_status_normal_at_boundary_below_hot(void) {
    // Expected: Temperature 85.0f is not strictly greater than 85.0f, thus "NORMAL"
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(85.0f));
}

void test_check_temperature_status_normal_at_boundary_above_cold(void) {
    // Expected: Temperature 0.0f is not strictly less than 0.0f, thus "NORMAL"
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(0.0f));
}

void test_check_temperature_status_cold_below_minus10(void) {
    // Expected: Temperature 0.0f is strictly less than 0.0f, thus "COLD"
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(0.0f));
}

void test_check_temperature_status_cold_at_min_valid(void) {
    // Expected: Temperature 0.0f (minimum physical limit) is "COLD"
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(0.0f));
}

// ==============================================================================
// TESTS FOR get_temperature_celsius
// ==============================================================================

void test_get_temperature_celsius_nominal(void) {
    // Configure stubs for a nominal scenario: raw 500 converts to 25.0f C
    stub_read_temperature_raw_config.return_value = 500;
    stub_raw_to_celsius_config.return_value = 25.0f;

    float result = get_temperature_celsius();

    // Expected: read_temperature_raw was called exactly once
    TEST_ASSERT_TRUE(stub_read_temperature_raw_config.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_read_temperature_raw_config.call_count);
    // Expected: raw_to_celsius was called exactly once with the raw value 500
    TEST_ASSERT_TRUE(stub_raw_to_celsius_config.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius_config.call_count);
    TEST_ASSERT_EQUAL_INT(500, stub_raw_to_celsius_config.captured_raw);
    // Expected: The final converted temperature is 25.0f within tolerance
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 25.0f, result);
}

void test_get_temperature_celsius_min_raw_produces_min_celsius(void) {
    // Configure stubs for the minimum raw value (0) converting to the minimum realistic Celsius (0.0f)
    stub_read_temperature_raw_config.return_value = 0;
    stub_raw_to_celsius_config.return_value = 0.0f;

    float result = get_temperature_celsius();

    // Expected: Stubs called once, raw value 0 passed
    TEST_ASSERT_TRUE(stub_read_temperature_raw_config.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_read_temperature_raw_config.call_count);
    TEST_ASSERT_TRUE(stub_raw_to_celsius_config.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius_config.call_count);
    TEST_ASSERT_EQUAL_INT(0, stub_raw_to_celsius_config.captured_raw);
    // Expected: Final temperature is 0.0f within tolerance
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, result);
}

void test_get_temperature_celsius_max_raw_produces_max_celsius(void) {
    // Configure stubs for the maximum raw value (1023, from rand() % 1024) converting to the maximum realistic Celsius (125.0f)
    stub_read_temperature_raw_config.return_value = 1023;
    stub_raw_to_celsius_config.return_value = 125.0f;

    float result = get_temperature_celsius();

    // Expected: Stubs called once, raw value 1023 passed
    TEST_ASSERT_TRUE(stub_read_temperature_raw_config.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_read_temperature_raw_config.call_count);
    TEST_ASSERT_TRUE(stub_raw_to_celsius_config.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius_config.call_count);
    TEST_ASSERT_EQUAL_INT(1023, stub_raw_to_celsius_config.captured_raw);
    // Expected: Final temperature is 125.0f within tolerance
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 125.0f, result);
}

void test_get_temperature_celsius_intermediate_raw_to_zero_celsius(void) {
    // Configure stubs for an intermediate raw value (256) converting to 0.0f Celsius
    stub_read_temperature_raw_config.return_value = 256;
    stub_raw_to_celsius_config.return_value = 0.0f;

    float result = get_temperature_celsius();

    // Expected: Stubs called once, raw value 256 passed
    TEST_ASSERT_TRUE(stub_read_temperature_raw_config.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_read_temperature_raw_config.call_count);
    TEST_ASSERT_TRUE(stub_raw_to_celsius_config.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius_config.call_count);
    TEST_ASSERT_EQUAL_INT(256, stub_raw_to_celsius_config.captured_raw);
    // Expected: Final temperature is 0.0f within tolerance
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, result);
}

// ==============================================================================
// MAIN TEST RUNNER
// ==============================================================================



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_validate_temperature_range_nominal_valid);
    RUN_TEST(test_validate_temperature_range_min_edge_valid);
    RUN_TEST(test_validate_temperature_range_max_edge_valid);
    RUN_TEST(test_validate_temperature_range_below_min_invalid);
    RUN_TEST(test_validate_temperature_range_above_max_invalid);
    RUN_TEST(test_validate_temperature_range_zero_valid);
    RUN_TEST(test_check_temperature_status_critical_above_120);
    RUN_TEST(test_check_temperature_status_critical_at_max_valid);
    RUN_TEST(test_check_temperature_status_hot_above_85);
    RUN_TEST(test_check_temperature_status_hot_at_boundary_below_critical);
    RUN_TEST(test_check_temperature_status_normal_nominal);
    RUN_TEST(test_check_temperature_status_normal_at_boundary_below_hot);
    RUN_TEST(test_check_temperature_status_normal_at_boundary_above_cold);
    RUN_TEST(test_check_temperature_status_cold_below_minus10);
    RUN_TEST(test_check_temperature_status_cold_at_min_valid);
    RUN_TEST(test_get_temperature_celsius_nominal);
    RUN_TEST(test_get_temperature_celsius_min_raw_produces_min_celsius);
    RUN_TEST(test_get_temperature_celsius_max_raw_produces_max_celsius);
    RUN_TEST(test_get_temperature_celsius_intermediate_raw_to_zero_celsius);

    return UNITY_END();
}