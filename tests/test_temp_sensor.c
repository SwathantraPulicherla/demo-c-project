#include "unity.h"
#include "temp_sensor.h"
#include "temp_converter.h" // Needed for the stubbed function raw_to_celsius

// --- STUB IMPLEMENTATION FOR raw_to_celsius ---

static int raw_to_celsius_CallCount;
static float raw_to_celsius_ReturnValue;
static int raw_to_celsius_LastRaw;

// Stub function signature must EXACTLY match the original declaration
float raw_to_celsius(int raw) {
    raw_to_celsius_CallCount++;
    raw_to_celsius_LastRaw = raw;
    return raw_to_celsius_ReturnValue;
}

// Helper function to configure the stub's return value
void set_raw_to_celsius_return(float value) {
    raw_to_celsius_ReturnValue = value;
}

// --- SETUP AND TEARDOWN FUNCTIONS ---

void setUp(void) {
    // Reset all stub variables before each test
    raw_to_celsius_CallCount = 0;
    raw_to_celsius_ReturnValue = 0.0f;
    raw_to_celsius_LastRaw = 0;
}

void tearDown(void) {
    // Reset all stub variables after each test (redundant if setUp always runs, but good practice)
    raw_to_celsius_CallCount = 0;
    raw_to_celsius_ReturnValue = 0.0f;
    raw_to_celsius_LastRaw = 0;
}

// --- TEST FUNCTIONS FOR read_temperature_raw ---

void test_read_temperature_raw_returns_non_negative(void) {
    int raw = read_temperature_raw();
    // rand() % 1024 will always be non-negative
    TEST_ASSERT_GREATER_OR_EQUAL_INT(0, raw);
}

void test_read_temperature_raw_returns_within_expected_upper_bound(void) {
    int raw = read_temperature_raw();
    // rand() % 1024 will return a value between 0 and 1023
    TEST_ASSERT_LESS_OR_EQUAL_INT(1023, raw);
}

// --- TEST FUNCTIONS FOR validate_temperature_range ---

void test_validate_temperature_range_normal_mid_range(void) {
    TEST_ASSERT_TRUE(validate_temperature_range(25.0f));
}

void test_validate_temperature_range_normal_cold_boundary_inclusive(void) {
    TEST_ASSERT_TRUE(validate_temperature_range(0.0f)); // Minimum operational temperature
}

void test_validate_temperature_range_normal_hot_boundary_inclusive(void) {
    TEST_ASSERT_TRUE(validate_temperature_range(125.0f)); // Maximum operational temperature
}

void test_validate_temperature_range_below_min_boundary_exclusive(void) {
    TEST_ASSERT_FALSE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_above_max_boundary_exclusive(void) {
    TEST_ASSERT_FALSE(validate_temperature_range(125.1f));
}

void test_validate_temperature_range_extreme_cold_invalid(void) {
    TEST_ASSERT_FALSE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_extreme_hot_invalid(void) {
    TEST_ASSERT_FALSE(validate_temperature_range(300.0f));
}

// --- TEST FUNCTIONS FOR check_temperature_status ---

void test_check_temperature_status_critical_just_above_threshold(void) {
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(120.1f));
}

void test_check_temperature_status_critical_max_operational(void) {
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(125.0f));
}

void test_check_temperature_status_hot_just_above_threshold(void) {
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(85.1f));
}

void test_check_temperature_status_hot_just_below_critical(void) {
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(120.0f)); // Boundary: 120.0f is NOT > 120.0f
}

void test_check_temperature_status_normal_mid_range_positive(void) {
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(25.0f));
}

void test_check_temperature_status_normal_zero_celsius(void) {
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(0.0f));
}

void test_check_temperature_status_normal_just_above_cold(void) {
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(0.0f)); // Boundary: 0.0f is NOT < 0.0f
}

void test_check_temperature_status_normal_hot_boundary_inclusive(void) {
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(85.0f)); // Boundary: 85.0f is NOT > 85.0f
}

void test_check_temperature_status_normal_cold_boundary_inclusive(void) {
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(0.0f)); // Boundary: 0.0f is NOT < 0.0f
}

void test_check_temperature_status_cold_just_below_threshold(void) {
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(0.0f));
}

void test_check_temperature_status_cold_min_operational(void) {
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(0.0f));
}

void test_check_temperature_status_cold_extreme(void) {
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(0.0f));
}

// --- TEST FUNCTIONS FOR get_temperature_celsius ---

void test_get_temperature_celsius_returns_normal_stubbed_value(void) {
    float expected_celsius = 25.0f;
    set_raw_to_celsius_return(expected_celsius);

    float actual_celsius = get_temperature_celsius();

    TEST_ASSERT_EQUAL_INT(1, raw_to_celsius_CallCount); // Verify stub was called once
    // Verify that the raw value passed to the stub is within the expected range (00.0f)
    TEST_ASSERT_GREATER_OR_EQUAL_INT(0, raw_to_celsius_LastRaw);
    TEST_ASSERT_LESS_OR_EQUAL_INT(1023, raw_to_celsius_LastRaw);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

void test_get_temperature_celsius_returns_max_operational_stubbed_value(void) {
    float expected_celsius = 125.0f;
    set_raw_to_celsius_return(expected_celsius);

    float actual_celsius = get_temperature_celsius();

    TEST_ASSERT_EQUAL_INT(1, raw_to_celsius_CallCount);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

void test_get_temperature_celsius_returns_min_operational_stubbed_value(void) {
    float expected_celsius = 0.0f;
    set_raw_to_celsius_return(expected_celsius);

    float actual_celsius = get_temperature_celsius();

    TEST_ASSERT_EQUAL_INT(1, raw_to_celsius_CallCount);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

void test_get_temperature_celsius_returns_zero_stubbed_value(void) {
    float expected_celsius = 0.0f;
    set_raw_to_celsius_return(expected_celsius);

    float actual_celsius = get_temperature_celsius();

    TEST_ASSERT_EQUAL_INT(1, raw_to_celsius_CallCount);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_read_temperature_raw_returns_non_negative);
    RUN_TEST(test_read_temperature_raw_returns_within_expected_upper_bound);
    RUN_TEST(test_validate_temperature_range_normal_mid_range);
    RUN_TEST(test_validate_temperature_range_normal_cold_boundary_inclusive);
    RUN_TEST(test_validate_temperature_range_normal_hot_boundary_inclusive);
    RUN_TEST(test_validate_temperature_range_below_min_boundary_exclusive);
    RUN_TEST(test_validate_temperature_range_above_max_boundary_exclusive);
    RUN_TEST(test_validate_temperature_range_extreme_cold_invalid);
    RUN_TEST(test_validate_temperature_range_extreme_hot_invalid);
    RUN_TEST(test_check_temperature_status_critical_just_above_threshold);
    RUN_TEST(test_check_temperature_status_critical_max_operational);
    RUN_TEST(test_check_temperature_status_hot_just_above_threshold);
    RUN_TEST(test_check_temperature_status_hot_just_below_critical);
    RUN_TEST(test_check_temperature_status_normal_mid_range_positive);
    RUN_TEST(test_check_temperature_status_normal_zero_celsius);
    RUN_TEST(test_check_temperature_status_normal_just_above_cold);
    RUN_TEST(test_check_temperature_status_normal_hot_boundary_inclusive);
    RUN_TEST(test_check_temperature_status_normal_cold_boundary_inclusive);
    RUN_TEST(test_check_temperature_status_cold_just_below_threshold);
    RUN_TEST(test_check_temperature_status_cold_min_operational);
    RUN_TEST(test_check_temperature_status_cold_extreme);
    RUN_TEST(test_get_temperature_celsius_returns_normal_stubbed_value);
    RUN_TEST(test_get_temperature_celsius_returns_max_operational_stubbed_value);
    RUN_TEST(test_get_temperature_celsius_returns_min_operational_stubbed_value);
    RUN_TEST(test_get_temperature_celsius_returns_zero_stubbed_value);

    return UNITY_END();
}