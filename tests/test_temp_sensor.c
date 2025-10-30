/* test_temp_sensor.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include "temp_sensor.h" // For functions under test prototypes
#include <stdbool.h>     // For bool type
#include <string.h>      // For memset and strcmp
#include <stdint.h>      // For uint32_t
#include <stdlib.h>      // For rand() prototype, as used in source

// Mocks/Stubs for external dependencies required by temp_sensor.c

// Stub for raw_to_celsius function
typedef struct {
    float return_value;
    bool was_called;
    uint32_t call_count;
    int last_raw_val; // Captures the last raw_val parameter passed
} stub_raw_to_celsius_t;
static stub_raw_to_celsius_t stub_raw_to_celsius = {0};

// External declaration for the stubbed raw_to_celsius function.
// The signature is inferred from its usage in temp_sensor.c and typical embedded patterns.
extern float raw_to_celsius(int raw_val);
float raw_to_celsius(int raw_val) {
    stub_raw_to_celsius.was_called = true;
    stub_raw_to_celsius.call_count++;
    stub_raw_to_celsius.last_raw_val = raw_val;
    return stub_raw_to_celsius.return_value;
}

// Stub for rand() function (from stdlib.h)
// This is necessary to make the read_temperature_raw() function deterministic for testing.
typedef struct {
    int return_value;
    bool was_called;
    uint32_t call_count;
} stub_rand_t;
static stub_rand_t stub_rand = {0};

// External declaration for the stubbed rand function.
// Prototype is provided by stdlib.h, included above.
extern int rand(void);
int rand(void) {
    stub_rand.was_called = true;
    stub_rand.call_count++;
    return stub_rand.return_value;
}


// --- Test Setup and Teardown ---

void setUp(void) {
    // Reset all stub control structures before each test
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
    memset(&stub_rand, 0, sizeof(stub_rand));
}

void tearDown(void) {
    // Ensure all stubs are reset after each test
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
    memset(&stub_rand, 0, sizeof(stub_rand));
}

// --- Test Cases for read_temperature_raw() ---

void test_read_temperature_raw_min_rand_value(void) {
    // Configure rand() stub to return the minimum possible value (0)
    stub_rand.return_value = 0;
    int result = read_temperature_raw();
    // Expected: If rand() returns 0, then 0 % 1024 is 0.
    TEST_ASSERT_EQUAL_INT(0, result);
    // Expected: rand() should have been called exactly once.
    TEST_ASSERT_TRUE(stub_rand.was_called);
    // Expected: rand() should have been called exactly once.
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand.call_count);
}

void test_read_temperature_raw_max_rand_value(void) {
    // Configure rand() stub to return a value that results in max (1023) after modulo
    stub_rand.return_value = 1023; // Maximum possible value before modulo operation, resulting in 1023.
    int result = read_temperature_raw();
    // Expected: If rand() returns 1023, then 1023 % 1024 is 1023.
    TEST_ASSERT_EQUAL_INT(1023, result);
    // Expected: rand() should have been called exactly once.
    TEST_ASSERT_TRUE(stub_rand.was_called);
    // Expected: rand() should have been called exactly once.
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand.call_count);
}

void test_read_temperature_raw_mid_rand_value(void) {
    // Configure rand() stub to return a mid-range value (e.g., 512)
    stub_rand.return_value = 512;
    int result = read_temperature_raw();
    // Expected: If rand() returns 512, then 512 % 1024 is 512.
    TEST_ASSERT_EQUAL_INT(512, result);
    // Expected: rand() should have been called exactly once.
    TEST_ASSERT_TRUE(stub_rand.was_called);
    // Expected: rand() should have been called exactly once.
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand.call_count);
}

void test_read_temperature_raw_overflow_rand_value(void) {
    // Configure rand() stub to return a value larger than 1023 to test modulo behavior
    stub_rand.return_value = 2047; // e.g., (1024 * 1) + 1023, which should result in 1023
    int result = read_temperature_raw();
    // Expected: If rand() returns 2047, then 2047 % 1024 is 1023.
    TEST_ASSERT_EQUAL_INT(1023, result);
    // Expected: rand() should have been called exactly once.
    TEST_ASSERT_TRUE(stub_rand.was_called);
    // Expected: rand() should have been called exactly once.
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand.call_count);
}

// --- Test Cases for validate_temperature_range() ---

void test_validate_temperature_range_min_valid_edge(void) {
    float temp_c = 0.0f;
    bool result = validate_temperature_range(temp_c);
    // Expected: 0.0f is within the valid range [0.0f, 125.0f].
    TEST_ASSERT_TRUE(result);
}

void test_validate_temperature_range_max_valid_edge(void) {
    float temp_c = 125.0f;
    bool result = validate_temperature_range(temp_c);
    // Expected: 125.0f is within the valid range [0.0f, 125.0f].
    TEST_ASSERT_TRUE(result);
}

void test_validate_temperature_range_mid_valid(void) {
    float temp_c = 25.0f;
    bool result = validate_temperature_range(temp_c);
    // Expected: 25.0f is within the valid range [0.0f, 125.0f].
    TEST_ASSERT_TRUE(result);
}

void test_validate_temperature_range_below_min_invalid(void) {
    float temp_c = 0.0f;
    bool result = validate_temperature_range(temp_c);
    // Expected: 0.0f is below the minimum valid range of 0.0f.
    TEST_ASSERT_FALSE(result);
}

void test_validate_temperature_range_above_max_invalid(void) {
    float temp_c = 125.1f;
    bool result = validate_temperature_range(temp_c);
    // Expected: 125.1f is above the maximum valid range of 125.0f.
    TEST_ASSERT_FALSE(result);
}

// --- Test Cases for check_temperature_status() ---

void test_check_temperature_status_critical_above_threshold(void) {
    float temp_c = 120.1f;
    const char* status = check_temperature_status(temp_c);
    // Expected: 120.1f is > 120.0f, so status is "CRITICAL".
    TEST_ASSERT_EQUAL_STRING("CRITICAL", status);
}

void test_check_temperature_status_hot_at_critical_threshold_edge(void) {
    float temp_c = 120.0f;
    const char* status = check_temperature_status(temp_c);
    // Expected: 120.0f is NOT > 120.0f, but is > 85.0f, so status is "HOT".
    TEST_ASSERT_EQUAL_STRING("HOT", status);
}

void test_check_temperature_status_hot_above_threshold(void) {
    float temp_c = 85.1f;
    const char* status = check_temperature_status(temp_c);
    // Expected: 85.1f is > 85.0f, so status is "HOT".
    TEST_ASSERT_EQUAL_STRING("HOT", status);
}

void test_check_temperature_status_hot_within_range(void) {
    float temp_c = 100.0f;
    const char* status = check_temperature_status(temp_c);
    // Expected: 100.0f is not > 120.0f, but is > 85.0f, so status is "HOT".
    TEST_ASSERT_EQUAL_STRING("HOT", status);
}

void test_check_temperature_status_normal_upper_edge(void) {
    float temp_c = 85.0f;
    const char* status = check_temperature_status(temp_c);
    // Expected: 85.0f is NOT > 85.0f, and not < 0.0f, so status is "NORMAL".
    TEST_ASSERT_EQUAL_STRING("NORMAL", status);
}

void test_check_temperature_status_normal_lower_edge(void) {
    float temp_c = 0.0f;
    const char* status = check_temperature_status(temp_c);
    // Expected: 0.0f is NOT < 0.0f, so status is "NORMAL".
    TEST_ASSERT_EQUAL_STRING("NORMAL", status);
}

void test_check_temperature_status_normal_mid_range(void) {
    float temp_c = 25.0f;
    const char* status = check_temperature_status(temp_c);
    // Expected: 25.0f is not in CRITICAL, HOT, or COLD ranges, so status is "NORMAL".
    TEST_ASSERT_EQUAL_STRING("NORMAL", status);
}

void test_check_temperature_status_cold_below_threshold(void) {
    float temp_c = 0.0f;
    const char* status = check_temperature_status(temp_c);
    // Expected: 0.0f is < 0.0f, so status is "COLD".
    TEST_ASSERT_EQUAL_STRING("COLD", status);
}

void test_check_temperature_status_cold_extreme_min_valid_temp(void) {
    float temp_c = 0.0f;
    const char* status = check_temperature_status(temp_c);
    // Expected: 0.0f is < 0.0f, so status is "COLD".
    TEST_ASSERT_EQUAL_STRING("COLD", status);
}

// --- Test Cases for get_temperature_celsius() ---

void test_get_temperature_celsius_normal_conversion(void) {
    // Configure rand() stub to return a mid-range raw value that will be passed to raw_to_celsius
    stub_rand.return_value = 512;
    // Configure raw_to_celsius stub to return a specific Celsius value for the expected raw input (512)
    stub_raw_to_celsius.return_value = 25.5f;

    float result = get_temperature_celsius();

    // Expected: rand() should have been called exactly once by read_temperature_raw().
    TEST_ASSERT_TRUE(stub_rand.was_called);
    // Expected: raw_to_celsius() should have been called exactly once.
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    // Expected: raw_to_celsius() should have received the raw value from read_temperature_raw().
    TEST_ASSERT_EQUAL_INT(512, stub_raw_to_celsius.last_raw_val);
    // Expected: The function returns the value provided by raw_to_celsius stub.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 25.5f, result);
}

void test_get_temperature_celsius_min_raw_output(void) {
    // Configure rand() stub to return the minimum raw value (0)
    stub_rand.return_value = 0;
    // Configure raw_to_celsius stub to return the corresponding Celsius value
    stub_raw_to_celsius.return_value = 0.0f;

    float result = get_temperature_celsius();

    // Expected: rand() should have been called exactly once.
    TEST_ASSERT_TRUE(stub_rand.was_called);
    // Expected: raw_to_celsius() should have been called once with raw_val 0.
    TEST_ASSERT_EQUAL_INT(0, stub_raw_to_celsius.last_raw_val);
    // Expected: The function returns the minimum Celsius value.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, result);
}

void test_get_temperature_celsius_max_raw_output(void) {
    // Configure rand() stub to return the maximum raw value (1023)
    stub_rand.return_value = 1023;
    // Configure raw_to_celsius stub to return the corresponding Celsius value
    stub_raw_to_celsius.return_value = 125.0f;

    float result = get_temperature_celsius();

    // Expected: rand() should have been called exactly once.
    TEST_ASSERT_TRUE(stub_rand.was_called);
    // Expected: raw_to_celsius() should have been called once with raw_val 1023.
    TEST_ASSERT_EQUAL_INT(1023, stub_raw_to_celsius.last_raw_val);
    // Expected: The function returns the maximum Celsius value.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 125.0f, result);
}


// --- Main Unity Test Runner ---



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_read_temperature_raw_min_rand_value);
    RUN_TEST(test_read_temperature_raw_max_rand_value);
    RUN_TEST(test_read_temperature_raw_mid_rand_value);
    RUN_TEST(test_read_temperature_raw_overflow_rand_value);
    RUN_TEST(test_validate_temperature_range_min_valid_edge);
    RUN_TEST(test_validate_temperature_range_max_valid_edge);
    RUN_TEST(test_validate_temperature_range_mid_valid);
    RUN_TEST(test_validate_temperature_range_below_min_invalid);
    RUN_TEST(test_validate_temperature_range_above_max_invalid);
    RUN_TEST(test_check_temperature_status_critical_above_threshold);
    RUN_TEST(test_check_temperature_status_hot_at_critical_threshold_edge);
    RUN_TEST(test_check_temperature_status_hot_above_threshold);
    RUN_TEST(test_check_temperature_status_hot_within_range);
    RUN_TEST(test_check_temperature_status_normal_upper_edge);
    RUN_TEST(test_check_temperature_status_normal_lower_edge);
    RUN_TEST(test_check_temperature_status_normal_mid_range);
    RUN_TEST(test_check_temperature_status_cold_below_threshold);
    RUN_TEST(test_check_temperature_status_cold_extreme_min_valid_temp);
    RUN_TEST(test_get_temperature_celsius_normal_conversion);
    RUN_TEST(test_get_temperature_celsius_min_raw_output);
    RUN_TEST(test_get_temperature_celsius_max_raw_output);

    return UNITY_END();
}