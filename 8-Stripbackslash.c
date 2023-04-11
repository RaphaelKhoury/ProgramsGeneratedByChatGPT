#include <stdio.h>
#include <string.h>

#define MAX_LEN 1000

int main() {
    char str[MAX_LEN];
    printf("Enter a string: ");
    fgets(str, MAX_LEN, stdin);
    str[strcspn(str, "\n")] = '\0'; // Remove newline character from input
    
    int len = strlen(str);
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] != '\\') { // If current character is not a backslash
            str[j] = str[i];
            j++;
        }
    }
    str[j] = '\0'; // Add null terminator at the end of the new string
}