#include "unity.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // For sscanf, remove
#include "temp_sensor.h"
#include "temp_converter.h" // For check_temperature_status

// --- Stubs for external functions ---

// Stub variables for get_temperature_celsius
static float get_temperature_celsius_return_value;
static int get_temperature_celsius_call_count;

float get_temperature_celsius(void) {
    get_temperature_celsius_call_count++;
    return get_temperature_celsius_return_value;
}

// --- Global variables for stdout redirection ---
static FILE* original_stdout;
static const char* TEST_OUTPUT_FILE = "test_output.txt";

// --- setUp and tearDown functions ---

void setUp(void) {
    // Reset stub variables
    get_temperature_celsius_return_value = 0.0f;
    get_temperature_celsius_call_count = 0;

    // Redirect stdout
    original_stdout = stdout; // Save original stdout
    fflush(stdout); // Flush any pending output
    stdout = freopen(TEST_OUTPUT_FILE, "w", stdout); // Redirect stdout to a file
    TEST_ASSERT_NOT_NULL_MESSAGE(stdout, "Failed to redirect stdout");
}

void tearDown(void) {
    // Reset stub variables (redundant if setUp always cleans, but good for safety)
    get_temperature_celsius_return_value = 0.0f;
    get_temperature_celsius_call_count = 0;

    // Restore stdout
    fflush(stdout); // Ensure all output is written to the file
    fclose(stdout); // Close the redirected file
    stdout = original_stdout; // Restore original stdout

    // Clean up test output file
    remove(TEST_OUTPUT_FILE);
}

// --- Helper function to read and parse main's output ---
static void read_and_parse_main_output(float* parsed_temp, char* parsed_status, size_t status_buffer_size) {
    FILE* fp = fopen(TEST_OUTPUT_FILE, "r");
    TEST_ASSERT_NOT_NULL_MESSAGE(fp, "Failed to open test output file for reading");

    char line1[256];
    char line2[256];

    TEST_ASSERT_NOT_NULL_MESSAGE(fgets(line1, sizeof(line1), fp), "Failed to read first line from output");
    TEST_ASSERT_NOT_NULL_MESSAGE(fgets(line2, sizeof(line2), fp), "Failed to read second line from output");
    
    fclose(fp);

    int read_count1 = sint read_count2 = sTEST_ASSERT_EQUAL_INT_MESSAGE(1, read_count1, "Failed to parse temperature from output");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, read_count2, "Failed to parse status from output");
}

// --- Test Cases for main ---

// Normal operation tests
void test_main_normal_temp_25C(void) {
    get_temperature_celsius_return_value = 25.0f;

    

    float actual_temp;
    char actual_status[100];
    read_and_parse_main_output(&actual_temp, actual_status, sizeof(actual_status));

    TEST_ASSERT_FLOAT_WITHIN(0.1f, 25.0f, actual_temp);
    TEST_ASSERT_EQUAL_STRING("OK", actual_status); // Assuming check_temperature_status(25.0f) returns "OK"
    TEST_ASSERT_EQUAL_INT(1, get_temperature_celsius_call_count);
}

void test_main_normal_temp_40C(void) {
    get_temperature_celsius_return_value = 40.0f;

    

    float actual_temp;
    char actual_status[100];
    read_and_parse_main_output(&actual_temp, actual_status, sizeof(actual_status));

    TEST_ASSERT_FLOAT_WITHIN(0.1f, 40.0f, actual_temp);
    TEST_ASSERT_EQUAL_STRING("OK", actual_status); // Assuming check_temperature_status(40.0f) returns "OK"
    TEST_ASSERT_EQUAL_INT(1, get_temperature_celsius_call_count);
}

// Edge case tests
void test_main_edge_min_operational_0C(void) {
    get_temperature_celsius_return_value = 0.0f;

    

    float actual_temp;
    char actual_status[100];
    read_and_parse_main_output(&actual_temp, actual_status, sizeof(actual_status));

    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, actual_temp);
    TEST_ASSERT_EQUAL_STRING("OK", actual_status); // Assuming 0C is considered OK or LOW by check_temperature_status. Using "OK" for this test.
    TEST_ASSERT_EQUAL_INT(1, get_temperature_celsius_call_count);
}

void test_main_edge_max_operational_125C(void) {
    get_temperature_celsius_return_value = 125.0f;

    

    float actual_temp;
    char actual_status[100];
    read_and_parse_main_output(&actual_temp, actual_status, sizeof(actual_status));

    TEST_ASSERT_FLOAT_WITHIN(0.1f, 125.0f, actual_temp);
    TEST_ASSERT_EQUAL_STRING("HIGH", actual_status); // Assuming check_temperature_status(125.0f) returns "HIGH"
    TEST_ASSERT_EQUAL_INT(1, get_temperature_celsius_call_count);
}

void test_main_edge_negative_40C(void) {
    get_temperature_celsius_return_value = 0.0f;

    

    float actual_temp;
    char actual_status[100];
    read_and_parse_main_output(&actual_temp, actual_status, sizeof(actual_status));

    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, actual_temp);
    TEST_ASSERT_EQUAL_STRING("LOW", actual_status); // Assuming check_temperature_status(0.0f) returns "LOW"
    TEST_ASSERT_EQUAL_INT(1, get_temperature_celsius_call_count);
}

void test_main_boundary_just_below_zero_minus0_1C(void) {
    get_temperature_celsius_return_value = 0.0f;

    

    float actual_temp;
    char actual_status[100];
    read_and_parse_main_output(&actual_temp, actual_status, sizeof(actual_status));

    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, actual_temp);
    TEST_ASSERT_EQUAL_STRING("LOW", actual_status); // Assuming check_temperature_status(0.0f) returns "LOW"
    TEST_ASSERT_EQUAL_INT(1, get_temperature_celsius_call_count);
}

void test_main_boundary_just_above_limit_50_1C(void) {
    get_temperature_celsius_return_value = 50.1f;

    

    float actual_temp;
    char actual_status[100];
    read_and_parse_main_output(&actual_temp, actual_status, sizeof(actual_status));

    TEST_ASSERT_FLOAT_WITHIN(0.1f, 50.1f, actual_temp);
    TEST_ASSERT_EQUAL_STRING("HIGH", actual_status); // Assuming check_temperature_status(50.1f) returns "HIGH"
    TEST_ASSERT_EQUAL_INT(1, get_temperature_celsius_call_count);
}

// Test runner


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_main_normal_temp_25C);
    RUN_TEST(test_main_normal_temp_40C);
    RUN_TEST(test_main_edge_min_operational_0C);
    RUN_TEST(test_main_edge_max_operational_125C);
    RUN_TEST(test_main_edge_negative_40C);
    RUN_TEST(test_main_boundary_just_below_zero_minus0_1C);
    RUN_TEST(test_main_boundary_just_above_limit_50_1C);

    return UNITY_END();
}