#include <stdio.h>

int main() {
    FILE *file;
    
    // Open the file in write mode
    file = fopen("text.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    // Prompt the user for input
    printf("Enter any data: ");
    
    // Since we want to read any data type, we can use a string as a buffer
    char input[100];
    scanf("%s", input);

    // Write the input to the file
    fprintf(file, "%s", input);

    // Close the file
    fclose(file);

    printf("Data written to file successfully.\n");
    
    return 0;
}
