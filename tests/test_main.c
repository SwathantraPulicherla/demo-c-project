#include "unity.h"
#include "temp_sensor.h"
#include "temp_converter.h"

// Stubs for functions that src/main.c calls and are listed as needing stubs

static int get_temperature_celsius_CalledCount;
static float get_temperature_celsius_Return;

float get_temperature_celsius(void) {
    get_temperature_celsius_CalledCount++;
    return get_temperature_celsius_Return;
}

// Setup function to reset stub states before each test
void setUp(void) {
    get_temperature_celsius_CalledCount = 0;
    get_temperature_celsius_Return = 0.0f; // Default value
}

// Teardown function to reset stub states after each test
void tearDown(void) {
    // Reset ALL stub variables (call counts and return values) to 0/default values
    get_temperature_celsius_CalledCount = 0;
    get_temperature_celsius_Return = 0.0f;
}

// Note: Direct testing of the 'main' function from src/main.c is not performed
// here due to the following critical constraints and best practices:
// 1. "Test functions individually, not main() or complex workflows."
// 2. To avoid duplicate 'main' symbol definition when linking with the Unity test runner's
//    main function, which would lead to compilation errors. Testing src/main.c's 'main'
//    directly would typically require modifying src/main.c (e.g., conditional compilation
//    of 'main') or a complex build system setup, which is not allowed or implied by the prompt.
// 3. The 'main' function in src/main.c primarily performs I/O (printf) and orchestrates
//    calls. Testing such a function in isolation without extensive mocking (e.g., for printf
//    output redirection) is difficult and typically outside the scope of basic unit testing,
//    especially with the constraint "NO calls to main() or other functions that don't exist
//    in testable form" (mocking printf would create a "testable form" not requested).
// The purpose of the stubs and setup/teardown is to prepare for potential tests
// of functions within src/main.c, should they become individually testable.

// Unity Test Runner main function
