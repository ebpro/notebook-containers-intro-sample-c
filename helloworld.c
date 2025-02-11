#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

int main(int argc, char* argv[]) {
    // Check for correct argument count
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <firstname>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Validate input length to prevent buffer overflow
    if (strlen(argv[1]) > MAX_NAME_LENGTH) {
        fprintf(stderr, "Error: Name too long (max %d characters)\n", MAX_NAME_LENGTH);
        return EXIT_FAILURE;
    }

    // Print greeting
    printf("Hello %s!\n", argv[1]);
    return EXIT_SUCCESS;
}