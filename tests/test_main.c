#include "unity.h"
#include "temp_sensor.h"
#include "temp_converter.h"

// It's not standard to test main(), but if required, we can rename it in the build
// process for the test executable (e.g., using -Dmain=app_main).
// We then declare it here to be able to call it from our tests.
extern int main(void);

// Stubs for get_temperature_celsius
static float stub_get_temperature_celsius_return_value;
static int stub_get_temperature_celsius_call_count;

float get_temperature_celsius(void) {
    stub_get_temperature_celsius_call_count++;
    return stub_get_temperature_celsius_return_value;
}

// Stubs for check_temperature_status
// This is required to verify that main passes the correct value.
static const char* stub_check_temperature_status_return_value;
static int stub_check_temperature_status_call_count;
static float stub_check_temperature_status_last_temp;

const char* check_temperature_status(float temperature) {
    stub_check_temperature_status_call_count++;
    stub_check_temperature_status_last_temp = temperature;
    return stub_check_temperature_status_return_value;
}

void setUp(void) {
    // Reset stubs before each test
    stub_get_temperature_celsius_return_value = 0.0f;
    stub_get_temperature_celsius_call_count = 0;

    stub_check_temperature_status_return_value = NULL;
    stub_check_temperature_status_call_count = 0;
    stub_check_temperature_status_last_temp = 0.0f; // A sentinel value
}

void tearDown(void) {
    // Reset stubs after each test to ensure test isolation
    setUp();
}

// Test main's logic with a typical, normal temperature.
void test_main_NormalOperation(void) {
    // Arrange
    float expected_temp = 25.5f;
    stub_get_temperature_celsius_return_value = expected_temp;

    // Act
    int result = 

    // Assert
    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_EQUAL_INT(1, stub_get_temperature_celsius_call_count);
    TEST_ASSERT_EQUAL_INT(1, stub_check_temperature_status_call_count);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_temp, stub_check_temperature_status_last_temp);
}

// Test main's logic with the minimum valid operating temperature.
void test_main_EdgeCase_MinTemperature(void) {
    // Arrange
    float expected_temp = 0.0f;
    stub_get_temperature_celsius_return_value = expected_temp;

    // Act
    int result = 

    // Assert
    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_EQUAL_INT(1, stub_get_temperature_celsius_call_count);
    TEST_ASSERT_EQUAL_INT(1, stub_check_temperature_status_call_count);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_temp, stub_check_temperature_status_last_temp);
}

// Test main's logic with the maximum valid operating temperature.
void test_main_EdgeCase_MaxTemperature(void) {
    // Arrange
    float expected_temp = 125.0f;
    stub_get_temperature_celsius_return_value = expected_temp;

    // Act
    int result = 

    // Assert
    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_EQUAL_INT(1, stub_get_temperature_celsius_call_count);
    TEST_ASSERT_EQUAL_INT(1, stub_check_temperature_status_call_count);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_temp, stub_check_temperature_status_last_temp);
}

// Test main's logic with a zero temperature value (boundary case).
void test_main_Boundary_ZeroTemperature(void) {
    // Arrange
    float expected_temp = 0.0f;
    stub_get_temperature_celsius_return_value = expected_temp;

    // Act
    int result = 

    // Assert
    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_EQUAL_INT(1, stub_get_temperature_celsius_call_count);
    TEST_ASSERT_EQUAL_INT(1, stub_check_temperature_status_call_count);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_temp, stub_check_temperature_status_last_temp);
}

// Test main's logic with a hot, but not maximum, temperature.
void test_main_HotTemperature(void) {
    // Arrange
    float expected_temp = 50.0f;
    stub_get_temperature_celsius_return_value = expected_temp;

    // Act
    int result = 

    // Assert
    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_EQUAL_INT(1, stub_get_temperature_celsius_call_count);
    TEST_ASSERT_EQUAL_INT(1, stub_check_temperature_status_call_count);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_temp, stub_check_temperature_status_last_temp);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_main_NormalOperation);
    RUN_TEST(test_main_EdgeCase_MinTemperature);
    RUN_TEST(test_main_EdgeCase_MaxTemperature);
    RUN_TEST(test_main_Boundary_ZeroTemperature);
    RUN_TEST(test_main_HotTemperature);

    return UNITY_END();
}