#include "unity.h"
#include "temp_sensor.h"
#include "temp_converter.h"

extern int application_main();

static float _get_temperature_celsius_return_value;
static int _get_temperature_celsius_call_count;

float get_temperature_celsius() {
    _get_temperature_celsius_call_count++;
    return _get_temperature_celsius_return_value;
}

void set_get_temperature_celsius_return(float val) {
    _get_temperature_celsius_return_value = val;
}

int get_get_temperature_celsius_call_count() {
    return _get_temperature_celsius_call_count;
}

void setUp(void) {
    _get_temperature_celsius_return_value = 0.0f;
    _get_temperature_celsius_call_count = 0;
}

void tearDown(void) {
    _get_temperature_celsius_return_value = 0.0f;
    _get_temperature_celsius_call_count = 0;
}

void test_main_normal_temperature(void) {
    set_get_temperature_celsius_return(22.5f);
    int result = application_main();
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(1, get_get_temperature_celsius_call_count());
}

void test_main_low_temperature(void) {
    set_get_temperature_celsius_return(10.0f);
    int result = application_main();
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(1, get_get_temperature_celsius_call_count());
}

void test_main_high_temperature(void) {
    set_get_temperature_celsius_return(35.0f);
    int result = application_main();
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(1, get_get_temperature_celsius_call_count());
}

void test_main_zero_temperature(void) {
    set_get_temperature_celsius_return(0.0f);
    int result = application_main();
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(1, get_get_temperature_celsius_call_count());
}

void test_main_negative_temperature(void) {
    set_get_temperature_celsius_return(-5.0f);
    int result = application_main();
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(1, get_get_temperature_celsius_call_count());
}



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_main_normal_temperature);
    RUN_TEST(test_main_low_temperature);
    RUN_TEST(test_main_high_temperature);
    RUN_TEST(test_main_zero_temperature);
    RUN_TEST(test_main_negative_temperature);

    return UNITY_END();
}