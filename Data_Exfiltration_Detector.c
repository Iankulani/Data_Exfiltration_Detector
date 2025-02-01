#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 256
#define EXFIL_PATTERN "EXFIL"  // A simple pattern to look for in the data
#define EXFIL_PATTERN_LENGTH 5

// Function prototypes
void promptForInput();
void detectExfiltration(const unsigned char *data, size_t size);
void displayMenu();
void exitTool();

// Function to detect exfiltration patterns in the data
void detectExfiltration(const unsigned char *data, size_t size) {
    int detected = 0;

    // Scan the data for the EXFIL pattern
    for (size_t i = 0; i <= size - EXFIL_PATTERN_LENGTH; i++) {
        if (memcmp(data + i, EXFIL_PATTERN, EXFIL_PATTERN_LENGTH) == 0) {
            detected = 1;
            break;
        }
    }

    if (detected) {
        printf("\nALERT: Potential data exfiltration detected! The pattern '%s' was found in the data.\n", EXFIL_PATTERN);
    } else {
        printf("\nNo exfiltration patterns detected.\n");
    }
}

// Function to prompt the user for input data to analyze
void promptForInput() {
    unsigned char inputData[MAX_INPUT_SIZE];
    size_t dataSize;

    printf("Enter data to analyze (max %d characters):", MAX_INPUT_SIZE);
    fgets((char *)inputData, sizeof(inputData), stdin);
    inputData[strcspn((char *)inputData, "\n")] = 0;  // Remove newline character

    dataSize = strlen((char *)inputData);

    if (dataSize > 0) {
        // Perform exfiltration detection on the provided data
        detectExfiltration(inputData, dataSize);
    } else {
        printf("No data entered.\n");
    }
}

// Function to display the main menu
void displayMenu() {
    int userChoice;

    printf("\nData Exfiltration Detector\n");
    printf("1. Enter Data to Analyze\n");
    printf("2. Exit\n");

    printf("Enter your choice: ");
    scanf("%d", &userChoice);
    getchar();  // Consume newline character

    switch (userChoice) {
        case 1:
            promptForInput();
            break;
        case 2:
            exitTool();
            break;
        default:
            printf("Invalid choice. Please try again.\n");
    }
}

// Exit the program
void exitTool() {
    printf("Exiting the Data Exfiltration Detector.\n");
    exit(0);
}

// Main program loop
int main() {
    printf("Welcome to the Data Exfiltration Detector\n");

    // Main program loop
    while (1) {
        displayMenu();
    }

    return 0;
}
