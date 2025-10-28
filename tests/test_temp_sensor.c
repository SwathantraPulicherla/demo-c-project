#include "unity.h"
#include "temp_sensor.h"
#include "temp_converter.h"
#include <stdbool.h>

//==================================================================================================
// STUBS
//==================================================================================================

// Stub for raw_to_celsius
static float stub_raw_to_celsius_return_value;
static int stub_raw_to_celsius_last_param;
static int stub_raw_to_celsius_call_count;

// Stub implementation that replaces the real function
float raw_to_celsius(int raw) {
    stub_raw_to_celsius_call_count++;
    stub_raw_to_celsius_last_param = raw;
    return stub_raw_to_celsius_return_value;
}

// Helper to reset all stub variables
void reset_stubs(void) {
    stub_raw_to_celsius_return_value = 0.0f;
    stub_raw_to_celsius_last_param = 0.0f;
    stub_raw_to_celsius_call_count = 0;
}


//==================================================================================================
// SETUP & TEARDOWN
//==================================================================================================

void setUp(void) {
    reset_stubs();
}

void tearDown(void) {
    reset_stubs();
}

//==================================================================================================
// TESTS
//==================================================================================================

//== read_temperature_raw ==

void test_read_temperature_raw_should_ReturnValueWithinExpectedRange(void) {
    // This function uses rand(), so we can only test that its output is within the expected range.
    // We'll run it a few times to increase confidence.
    for (int i = 0; i < 100; ++i) {
        int raw_value = read_temperature_raw();
        TEST_ASSERT_GREATER_OR_EQUAL_INT(0, raw_value);
        TEST_ASSERT_LESS_OR_EQUAL_INT(1023, raw_value);
    }
}

//== validate_temperature_range ==

void test_validate_temperature_range_should_ReturnTrue_ForNormalTemperature(void) {
    TEST_ASSERT_TRUE(validate_temperature_range(25.0f));
}

void test_validate_temperature_range_should_ReturnTrue_ForMinimumBoundary(void) {
    TEST_ASSERT_TRUE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_should_ReturnTrue_ForMaximumBoundary(void) {
    TEST_ASSERT_TRUE(validate_temperature_range(125.0f));
}

void test_validate_temperature_range_should_ReturnTrue_ForZero(void) {
    TEST_ASSERT_TRUE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_should_ReturnFalse_JustBelowMinimum(void) {
    TEST_ASSERT_FALSE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_should_ReturnFalse_JustAboveMaximum(void) {
    TEST_ASSERT_FALSE(validate_temperature_range(125.1f));
}


//== check_temperature_status ==

// Test CRITICAL branch
void test_check_temperature_status_should_ReturnCritical_JustAboveBoundary(void) {
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(120.1f));
}

void test_check_temperature_status_should_ReturnCritical_AtMaximumValue(void) {
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(125.0f));
}

// Test HOT branch
void test_check_temperature_status_should_ReturnHot_AtUpperBoundary(void) {
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(120.0f));
}

void test_check_temperature_status_should_ReturnHot_JustAboveBoundary(void) {
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(85.1f));
}

// Test COLD branch
void test_check_temperature_status_should_ReturnCold_JustBelowBoundary(void) {
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(0.0f));
}

void test_check_temperature_status_should_ReturnCold_AtMinimumValue(void) {
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(0.0f));
}

// Test NORMAL branch
void test_check_temperature_status_should_ReturnNormal_AtLowerBoundary(void) {
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(0.0f));
}

void test_check_temperature_status_should_ReturnNormal_AtUpperBoundary(void) {
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(85.0f));
}

void test_check_temperature_status_should_ReturnNormal_ForRoomTemperature(void) {
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(25.0f));
}

void test_check_temperature_status_should_ReturnNormal_ForZeroTemperature(void) {
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(0.0f));
}


//== get_temperature_celsius ==

void test_get_temperature_celsius_should_CallConverterAndReturnItsValue(void) {
    // Arrange: Configure the stub to return a known value.
    stub_raw_to_celsius_return_value = 37.5f;

    // Act: Call the function under test.
    float result = get_temperature_celsius();

    // Assert: Check the results and stub interactions.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 37.5f, result);
    TEST_ASSERT_EQUAL_INT(1, stub_raw_to_celsius_call_count);
    
    // We cannot know the exact raw value due to rand(), but we can check its range.
    TEST_ASSERT_GREATER_OR_EQUAL_INT(0, stub_raw_to_celsius_last_param);
    TEST_ASSERT_LESS_OR_EQUAL_INT(1023, stub_raw_to_celsius_last_param);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_read_temperature_raw_should_ReturnValueWithinExpectedRange);
    RUN_TEST(test_validate_temperature_range_should_ReturnTrue_ForNormalTemperature);
    RUN_TEST(test_validate_temperature_range_should_ReturnTrue_ForMinimumBoundary);
    RUN_TEST(test_validate_temperature_range_should_ReturnTrue_ForMaximumBoundary);
    RUN_TEST(test_validate_temperature_range_should_ReturnTrue_ForZero);
    RUN_TEST(test_validate_temperature_range_should_ReturnFalse_JustBelowMinimum);
    RUN_TEST(test_validate_temperature_range_should_ReturnFalse_JustAboveMaximum);
    RUN_TEST(test_check_temperature_status_should_ReturnCritical_JustAboveBoundary);
    RUN_TEST(test_check_temperature_status_should_ReturnCritical_AtMaximumValue);
    RUN_TEST(test_check_temperature_status_should_ReturnHot_AtUpperBoundary);
    RUN_TEST(test_check_temperature_status_should_ReturnHot_JustAboveBoundary);
    RUN_TEST(test_check_temperature_status_should_ReturnCold_JustBelowBoundary);
    RUN_TEST(test_check_temperature_status_should_ReturnCold_AtMinimumValue);
    RUN_TEST(test_check_temperature_status_should_ReturnNormal_AtLowerBoundary);
    RUN_TEST(test_check_temperature_status_should_ReturnNormal_AtUpperBoundary);
    RUN_TEST(test_check_temperature_status_should_ReturnNormal_ForRoomTemperature);
    RUN_TEST(test_check_temperature_status_should_ReturnNormal_ForZeroTemperature);
    RUN_TEST(test_get_temperature_celsius_should_CallConverterAndReturnItsValue);

    return UNITY_END();
}