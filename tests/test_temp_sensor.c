/* test_temp_sensor.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h> // For memset
#include <stdlib.h> // For original rand() declaration

// Include the header of the module under test to get public API declarations
// This is necessary to avoid manually declaring all public functions.
#include "temp_sensor.h"

// --- EXTERNAL STUBS AND THEIR CONTROL STRUCTURES ---

// Stub for raw_to_celsius (declared in temp_converter.h, called by temp_sensor.c)
typedef struct {
    float return_value;
    bool was_called;
    uint32_t call_count;
    int last_raw_param;
} stub_raw_to_celsius_t;
static stub_raw_to_celsius_t stub_raw_to_celsius = {0};

float raw_to_celsius(int raw_value) {
    stub_raw_to_celsius.was_called = true;
    stub_raw_to_celsius.call_count++;
    stub_raw_to_celsius.last_raw_param = raw_value;
    return stub_raw_to_celsius.return_value;
}

// Stub for rand() from stdlib.h (called by read_temperature_raw in temp_sensor.c)
// Need to declare extern int rand(); to override the standard library's rand() for testing.
extern int rand(); // Declare the standard library function
typedef struct {
    int return_value;
    bool was_called;
    uint32_t call_count;
} stub_rand_t;
static stub_rand_t stub_rand = {0};

int rand() {
    stub_rand.was_called = true;
    stub_rand.call_count++;
    return stub_rand.return_value;
}

// --- SETUP AND TEARDOWN FUNCTIONS ---

void setUp(void) {
    // Reset all stubs before each test
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
    memset(&stub_rand, 0, sizeof(stub_rand));
}

void tearDown(void) {
    // Ensure all stubs are reset after each test as well
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
    memset(&stub_rand, 0, sizeof(stub_rand));
}

// --- TEST CASES FOR validate_temperature_range ---

void test_validate_temperature_range_min_valid(void) {
    // Expected: 0.0f is within the valid range [0.0f, 125.0f]
    TEST_ASSERT_TRUE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_min_invalid(void) {
    // Expected: 0.0f is below the valid range [0.0f, 125.0f]
    TEST_ASSERT_FALSE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_max_valid(void) {
    // Expected: 125.0f is within the valid range [0.0f, 125.0f]
    TEST_ASSERT_TRUE(validate_temperature_range(125.0f));
}

void test_validate_temperature_range_max_invalid(void) {
    // Expected: 125.1f is above the valid range [0.0f, 125.0f]
    TEST_ASSERT_FALSE(validate_temperature_range(125.1f));
}

void test_validate_temperature_range_mid_valid(void) {
    // Expected: 25.0f is within the valid range [0.0f, 125.0f]
    TEST_ASSERT_TRUE(validate_temperature_range(25.0f));
}

void test_validate_temperature_range_zero_valid(void) {
    // Expected: 0.0f is within the valid range [0.0f, 125.0f]
    TEST_ASSERT_TRUE(validate_temperature_range(0.0f));
}

// --- TEST CASES FOR check_temperature_status ---

void test_check_temperature_status_critical_above_threshold(void) {
    // Expected: 120.1f is > 120.0f, so status is "CRITICAL"
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(120.1f));
}

void test_check_temperature_status_critical_max_valid_temp(void) {
    // Expected: 125.0f is > 120.0f, so status is "CRITICAL"
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(125.0f));
}

void test_check_temperature_status_hot_above_threshold(void) {
    // Expected: 85.1f is > 85.0f and <= 120.0f, so status is "HOT"
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(85.1f));
}

void test_check_temperature_status_hot_at_upper_bound(void) {
    // Expected: 120.0f is > 85.0f and not > 120.0f, so status is "HOT"
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(120.0f));
}

void test_check_temperature_status_normal_mid_range(void) {
    // Expected: 25.0f is <= 85.0f and >= 0.0f, so status is "NORMAL"
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(25.0f));
}

void test_check_temperature_status_normal_at_hot_lower_bound(void) {
    // Expected: 85.0f is not > 85.0f and >= 0.0f, so status is "NORMAL"
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(85.0f));
}

void test_check_temperature_status_normal_at_cold_upper_bound(void) {
    // Expected: 0.0f is not < 0.0f and <= 85.0f, so status is "NORMAL"
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(0.0f));
}

void test_check_temperature_status_normal_zero(void) {
    // Expected: 0.0f is not < 0.0f and <= 85.0f, so status is "NORMAL"
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(0.0f));
}

void test_check_temperature_status_cold_below_threshold(void) {
    // Expected: 0.0f is < 0.0f, so status is "COLD"
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(0.0f));
}

void test_check_temperature_status_cold_min_valid_temp(void) {
    // Expected: 0.0f is < 0.0f, so status is "COLD"
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(0.0f));
}

void test_check_temperature_status_cold_invalid_temp(void) {
    // Expected: 0.0f is < 0.0f, so status is "COLD" (status logic applies even if range invalid)
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(0.0f));
}

// --- TEST CASES FOR get_temperature_celsius ---

void test_get_temperature_celsius_normal_conversion(void) {
    // Configure rand() to return a specific raw value
    stub_rand.return_value = 512; // A mid-range raw value (00.0f)
    // Configure raw_to_celsius to return a specific Celsius value for any raw input
    stub_raw_to_celsius.return_value = 25.5f;

    float result = get_temperature_celsius();

    // Expected: rand() was called once
    TEST_ASSERT_TRUE(stub_rand.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand.call_count);
    // Expected: raw_to_celsius was called once with the raw value from rand()
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    TEST_ASSERT_EQUAL_INT(512, stub_raw_to_celsius.last_raw_param);
    // Expected: The function returns the value from raw_to_celsius
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 25.5f, result);
}

void test_get_temperature_celsius_min_raw_conversion(void) {
    // Configure rand() to return the minimum raw value
    stub_rand.return_value = 0; // Minimum raw value from rand() % 1024
    // Configure raw_to_celsius to return a specific Celsius value
    stub_raw_to_celsius.return_value = 0.0f; // Example min Celsius

    float result = get_temperature_celsius();

    // Expected: rand() was called once and returned 0
    TEST_ASSERT_EQUAL_INT(0, stub_rand.return_value);
    // Expected: raw_to_celsius was called with 0
    TEST_ASSERT_EQUAL_INT(0, stub_raw_to_celsius.last_raw_param);
    // Expected: The function returns 0.0f
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, result);
}

void test_get_temperature_celsius_max_raw_conversion(void) {
    // Configure rand() to return the maximum raw value possible (1023)
    stub_rand.return_value = 1023; // Maximum raw value from rand() % 1024
    // Configure raw_to_celsius to return a specific Celsius value
    stub_raw_to_celsius.return_value = 125.0f; // Example max Celsius

    float result = get_temperature_celsius();

    // Expected: rand() was called once and returned 1023
    TEST_ASSERT_EQUAL_INT(1023, stub_rand.return_value);
    // Expected: raw_to_celsius was called with 1023
    TEST_ASSERT_EQUAL_INT(1023, stub_raw_to_celsius.last_raw_param);
    // Expected: The function returns 125.0f
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 125.0f, result);
}

// --- MAIN FUNCTION FOR RUNNING TESTS ---



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_validate_temperature_range_min_valid);
    RUN_TEST(test_validate_temperature_range_min_invalid);
    RUN_TEST(test_validate_temperature_range_max_valid);
    RUN_TEST(test_validate_temperature_range_max_invalid);
    RUN_TEST(test_validate_temperature_range_mid_valid);
    RUN_TEST(test_validate_temperature_range_zero_valid);
    RUN_TEST(test_check_temperature_status_critical_above_threshold);
    RUN_TEST(test_check_temperature_status_critical_max_valid_temp);
    RUN_TEST(test_check_temperature_status_hot_above_threshold);
    RUN_TEST(test_check_temperature_status_hot_at_upper_bound);
    RUN_TEST(test_check_temperature_status_normal_mid_range);
    RUN_TEST(test_check_temperature_status_normal_at_hot_lower_bound);
    RUN_TEST(test_check_temperature_status_normal_at_cold_upper_bound);
    RUN_TEST(test_check_temperature_status_normal_zero);
    RUN_TEST(test_check_temperature_status_cold_below_threshold);
    RUN_TEST(test_check_temperature_status_cold_min_valid_temp);
    RUN_TEST(test_check_temperature_status_cold_invalid_temp);
    RUN_TEST(test_get_temperature_celsius_normal_conversion);
    RUN_TEST(test_get_temperature_celsius_min_raw_conversion);
    RUN_TEST(test_get_temperature_celsius_max_raw_conversion);

    return UNITY_END();
}