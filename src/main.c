#include <stdio.h>
#include <stdlib.h>
#include "temp_sensor.h"
#include "temp_converter.h"

void display_menu() {
    printf("\n=== Temperature Sensor Demo ===\n");
    printf("1. Get current temperature (Celsius)\n");
    printf("2. Get current temperature (Fahrenheit)\n");
    printf("3. Check temperature status\n");
    printf("4. Get raw ADC value\n");
    printf("5. Validate temperature range\n");
    printf("6. Check if temperature is rising\n");
    printf("7. Continuous monitoring mode\n");
    printf("0. Exit\n");
    printf("Choose an option: ");
}

void continuous_monitoring() {
    printf("\n=== Continuous Monitoring Mode ===\n");
    printf("Press Ctrl+C to stop monitoring\n\n");

    float prev_temp = get_temperature_celsius();

    while (1) {
        float current_temp = get_temperature_celsius();
        const char* status = check_temperature_status(current_temp);
        float temp_f = celsius_to_fahrenheit(current_temp);
        int raw_value = read_temperature_raw();

        printf("Raw: %4d | Celsius: %6.2f C | Fahrenheit: %6.2f F | Status: %s",
               raw_value, current_temp, temp_f, status);

        // Check if temperature is rising
        if (is_temperature_rising(prev_temp, current_temp, 0.5f)) {
            printf(" | RISING");
        }
        printf("\n");

        prev_temp = current_temp;

        // Wait 2 seconds
        #ifdef _WIN32
            Sleep(2000);
        #else
            sleep(2);
        #endif
    }
}

int main() {
    int choice;
    float temp_c, temp_f;
    int raw_value;
    const char* status;
    bool is_valid;

    do {
        display_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Get current temperature (Celsius)
                temp_c = get_temperature_celsius();
                printf("Current temperature: %.2f °C\n", temp_c);
                break;

            case 2: // Get current temperature (Fahrenheit)
                temp_c = get_temperature_celsius();
                temp_f = celsius_to_fahrenheit(temp_c);
                printf("Current temperature: %.2f °F (%.2f °C)\n", temp_f, temp_c);
                break;

            case 3: // Check temperature status
                temp_c = get_temperature_celsius();
                status = check_temperature_status(temp_c);
                printf("Temperature: %.2f °C - Status: %s\n", temp_c, status);
                break;

            case 4: // Get raw ADC value
                raw_value = read_temperature_raw();
                printf("Raw ADC value: %d (range: 0-1023)\n", raw_value);
                break;

            case 5: // Validate temperature range
                temp_c = get_temperature_celsius();
                is_valid = validate_temperature_range(temp_c);
                printf("Temperature: %.2f °C - Valid range (-40°C to 125°C): %s\n",
                       temp_c, is_valid ? "YES" : "NO");
                break;

            case 6: // Check if temperature is rising
                {
                    static float prev_temp = 0.0f;
                    temp_c = get_temperature_celsius();
                    bool rising = is_temperature_rising(prev_temp, temp_c, 0.5f);
                    printf("Previous: %.2f °C, Current: %.2f °C - Rising: %s\n",
                           prev_temp, temp_c, rising ? "YES" : "NO");
                    prev_temp = temp_c;
                }
                break;

            case 7: // Continuous monitoring mode
                continuous_monitoring();
                break;

            case 0: // Exit
                printf("Exiting Temperature Sensor Demo. Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }

        // Clear input buffer
        while (getchar() != '\n');

    } while (choice != 0);

    return 0;
}