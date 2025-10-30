/* test_temp_sensor.c – Auto-generated Expert Unity Tests */

#include "unity.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

// Include the header for the source code under test to get function declarations
// This is required so the test file knows about `read_temperature_raw`, `validate_temperature_range`, etc.
#include "temp_sensor.h"

// --- EXTERNAL STUB DECLARATIONS ---
// Declarations for external functions not defined in temp_sensor.c, but used by it.
// These will be defined as stubs below.
extern int rand(void);
extern float raw_to_celsius(int raw_temp);

// --- STUB CONTROL STRUCTURES ---
// These structures hold state for our stubbed external functions.
typedef struct {
    int return_value;
    uint32_t call_count;
    bool was_called;
} stub_rand_t;
static stub_rand_t stub_rand = {0};

typedef struct {
    float return_value;
    uint32_t call_count;
    bool was_called;
    int last_raw_temp; // Capture parameter for assertion
} stub_raw_to_celsius_t;
static stub_raw_to_celsius_t stub_raw_to_celsius = {0};

// --- STUB IMPLEMENTATIONS ---
// Implementations of the stubbed external functions.
int rand(void) {
    stub_rand.call_count++;
    stub_rand.was_called = true;
    return stub_rand.return_value;
}

float raw_to_celsius(int raw_temp) {
    stub_raw_to_celsius.call_count++;
    stub_raw_to_celsius.was_called = true;
    stub_raw_to_celsius.last_raw_temp = raw_temp;
    return stub_raw_to_celsius.return_value;
}

// --- UNITY TEST FRAMEWORK SETUP/TEARDOWN ---
void setUp(void) {
    // Reset all stub control structures to a known state before each test
    memset(&stub_rand, 0, sizeof(stub_rand));
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));

    // Set default return values for stubs if needed for common scenarios
    // Example: For rand, a mid-range default might be useful if not explicitly set by tests.
    stub_rand.return_value = 512; // A reasonable default for rand() % 1024
    stub_raw_to_celsius.return_value = 25.0f; // A reasonable default for temperature
}

void tearDown(void) {
    // Ensure all stubs are completely reset after each test
    memset(&stub_rand, 0, sizeof(stub_rand));
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
}

// --- TESTS FOR read_temperature_raw() ---
// This function internally uses rand(). We stub rand() to control its output.

void test_read_temperature_raw_returns_min_value(void) {
    stub_rand.return_value = 0; // Configure rand() to return 0
    int result = read_temperature_raw();
    // Expected: read_temperature_raw() returns 0 when rand() returns 0.
    TEST_ASSERT_EQUAL_INT(0, result);
    // Expected: rand() was called exactly once.
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand.call_count);
}

void test_read_temperature_raw_returns_max_value(void) {
    stub_rand.return_value = 1023; // Configure rand() to return 1023
    int result = read_temperature_raw();
    // Expected: read_temperature_raw() returns 1023 when rand() returns 1023.
    TEST_ASSERT_EQUAL_INT(1023, result);
    // Expected: rand() was called exactly once.
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand.call_count);
}

void test_read_temperature_raw_returns_mid_value(void) {
    stub_rand.return_value = 512; // Configure rand() to return 512
    int result = read_temperature_raw();
    // Expected: read_temperature_raw() returns 512 when rand() returns 512.
    TEST_ASSERT_EQUAL_INT(512, result);
    // Expected: rand() was called exactly once.
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand.call_count);
}

void test_read_temperature_raw_handles_rand_greater_than_1023(void) {
    // Though rand() % 1024 would prevent this, it's good to ensure if rand() somehow returned a higher number,
    // the modulo would correctly limit it. This test might be redundant if we trust rand() % X.
    // However, the rule "No unrealistic values" means `stub_rand.return_value` should also be within a reasonable range for `rand()`.
    // Let's assume rand() could return a higher number, and the modulo brings it down.
    stub_rand.return_value = 2047; // A value > 1023, but within int limits. 2047 % 1024 = 1023.
    int result = read_temperature_raw();
    // Expected: read_temperature_raw() returns 1023 (2047 % 1024) when rand() returns 2047.
    TEST_ASSERT_EQUAL_INT(1023, result);
    // Expected: rand() was called exactly once.
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand.call_count);
}

// --- TESTS FOR validate_temperature_range() ---

void test_validate_temperature_range_min_valid_edge(void) {
    // Expected: 0.0f is within the valid range (>= 0.0f).
    TEST_ASSERT_TRUE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_min_invalid_below_edge(void) {
    // Expected: 0.0f is outside the valid range (less than 0.0f).
    TEST_ASSERT_FALSE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_max_valid_edge(void) {
    // Expected: 125.0f is within the valid range (<= 125.0f).
    TEST_ASSERT_TRUE(validate_temperature_range(125.0f));
}

void test_validate_temperature_range_max_invalid_above_edge(void) {
    // Expected: 125.1f is outside the valid range (greater than 125.0f).
    TEST_ASSERT_FALSE(validate_temperature_range(125.1f));
}

void test_validate_temperature_range_mid_valid(void) {
    // Expected: 25.0f is within the valid range.
    TEST_ASSERT_TRUE(validate_temperature_range(25.0f));
}

void test_validate_temperature_range_zero_valid(void) {
    // Expected: 0.0f is within the valid range.
    TEST_ASSERT_TRUE(validate_temperature_range(0.0f));
}

// --- TESTS FOR check_temperature_status() ---

void test_check_temperature_status_critical_above_120(void) {
    // Expected: 120.1f is 'CRITICAL' as it's > 120.0f.
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(120.1f));
}

void test_check_temperature_status_critical_max_valid_range(void) {
    // Expected: 125.0f is 'CRITICAL' as it's > 120.0f.
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(125.0f));
}

void test_check_temperature_status_hot_above_85_edge(void) {
    // Expected: 85.1f is 'HOT' as it's > 85.0f and <= 120.0f.
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(85.1f));
}

void test_check_temperature_status_hot_below_120_edge(void) {
    // Expected: 120.0f is 'HOT' as it's > 85.0f and <= 120.0f.
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(120.0f));
}

void test_check_temperature_status_cold_below_minus_10(void) {
    // Expected: 0.0f is 'COLD' as it's < 0.0f.
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(0.0f));
}

void test_check_temperature_status_cold_min_valid_range(void) {
    // Expected: 0.0f is 'COLD' as it's < 0.0f.
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(0.0f));
}

void test_check_temperature_status_normal_at_minus_10_edge(void) {
    // Expected: 0.0f is 'NORMAL' as it's not < 0.0f.
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(0.0f));
}

void test_check_temperature_status_normal_at_85_edge(void) {
    // Expected: 85.0f is 'NORMAL' as it's not > 85.0f and not < 0.0f.
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(85.0f));
}

void test_check_temperature_status_normal_mid_range(void) {
    // Expected: 25.0f is 'NORMAL' as it falls within the 0.0f to 85.0f range.
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(25.0f));
}

void test_check_temperature_status_normal_zero(void) {
    // Expected: 0.0f is 'NORMAL' as it falls within the 0.0f to 85.0f range.
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(0.0f));
}

// --- TESTS FOR get_temperature_celsius() ---

void test_get_temperature_celsius_normal_conversion(void) {
    stub_rand.return_value = 500; // Mock raw sensor reading
    stub_raw_to_celsius.return_value = 25.0f; // Mock conversion result

    float result = get_temperature_celsius();
    // Expected: read_temperature_raw() was called once.
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand.call_count);
    // Expected: raw_to_celsius() was called once.
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    // Expected: raw_to_celsius() received the raw value from read_temperature_raw().
    TEST_ASSERT_EQUAL_INT(500, stub_raw_to_celsius.last_raw_temp);
    // Expected: get_temperature_celsius() returns the converted value from raw_to_celsius().
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 25.0f, result);
}

void test_get_temperature_celsius_min_raw_produces_expected_celsius(void) {
    stub_rand.return_value = 0; // Mock raw sensor reading (min)
    stub_raw_to_celsius.return_value = 0.0f; // Mock conversion to min valid Celsius

    float result = get_temperature_celsius();
    // Expected: read_temperature_raw() was called once.
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand.call_count);
    // Expected: raw_to_celsius() was called once.
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    // Expected: raw_to_celsius() received the min raw value.
    TEST_ASSERT_EQUAL_INT(0, stub_raw_to_celsius.last_raw_temp);
    // Expected: get_temperature_celsius() returns the converted min Celsius value.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, result);
}

void test_get_temperature_celsius_max_raw_produces_expected_celsius(void) {
    stub_rand.return_value = 1023; // Mock raw sensor reading (max)
    stub_raw_to_celsius.return_value = 125.0f; // Mock conversion to max valid Celsius

    float result = get_temperature_celsius();
    // Expected: read_temperature_raw() was called once.
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand.call_count);
    // Expected: raw_to_celsius() was called once.
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    // Expected: raw_to_celsius() received the max raw value.
    TEST_ASSERT_EQUAL_INT(1023, stub_raw_to_celsius.last_raw_temp);
    // Expected: get_temperature_celsius() returns the converted max Celsius value.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 125.0f, result);
}

// --- MAIN UNITY TEST RUNNER ---


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_read_temperature_raw_returns_min_value);
    RUN_TEST(test_read_temperature_raw_returns_max_value);
    RUN_TEST(test_read_temperature_raw_returns_mid_value);
    RUN_TEST(test_read_temperature_raw_handles_rand_greater_than_1023);
    RUN_TEST(test_validate_temperature_range_min_valid_edge);
    RUN_TEST(test_validate_temperature_range_min_invalid_below_edge);
    RUN_TEST(test_validate_temperature_range_max_valid_edge);
    RUN_TEST(test_validate_temperature_range_max_invalid_above_edge);
    RUN_TEST(test_validate_temperature_range_mid_valid);
    RUN_TEST(test_validate_temperature_range_zero_valid);
    RUN_TEST(test_check_temperature_status_critical_above_120);
    RUN_TEST(test_check_temperature_status_critical_max_valid_range);
    RUN_TEST(test_check_temperature_status_hot_above_85_edge);
    RUN_TEST(test_check_temperature_status_hot_below_120_edge);
    RUN_TEST(test_check_temperature_status_cold_below_minus_10);
    RUN_TEST(test_check_temperature_status_cold_min_valid_range);
    RUN_TEST(test_check_temperature_status_normal_at_minus_10_edge);
    RUN_TEST(test_check_temperature_status_normal_at_85_edge);
    RUN_TEST(test_check_temperature_status_normal_mid_range);
    RUN_TEST(test_check_temperature_status_normal_zero);
    RUN_TEST(test_get_temperature_celsius_normal_conversion);
    RUN_TEST(test_get_temperature_celsius_min_raw_produces_expected_celsius);
    RUN_TEST(test_get_temperature_celsius_max_raw_produces_expected_celsius);

    return UNITY_END();
}