#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// Function to validate the string against the pattern a*bb
bool validateString(const char *str) {
    int i = 0;

    // Check for leading 'a's (zero or more)
    while (str[i] == 'a') {
        i++;
    }

    // Check for "bb" at the end
    if (str[i] == 'b' && str[i + 1] == 'b' && str[i + 2] == '\0') {
        return true;
    }

    // If the pattern doesn't match
    return false;
}

int main() {
    char input[100];

    printf("Enter a string: ");
    fgets(input, sizeof(input), stdin);

    // Remove newline character if present
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    // Check if the string is valid or invalid
    if (validateString(input)) {
        printf("Valid String\n");
    } else {
        printf("Invalid String\n");
    }

    return 0;
}
