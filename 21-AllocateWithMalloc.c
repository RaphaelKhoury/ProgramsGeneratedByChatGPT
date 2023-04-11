#include <stdio.h>
#include <stdlib.h>

int main()
{
    int size;
    int* arr;

    printf("Enter the size of the array: ");
    scanf("%d", &size);

    arr = (int*)malloc(size * sizeof(int))

    if (arr == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;s
    }

    printf("Memory allocated successfully.\n");

    // Do something with the allocated memory here...

    free(arr); // Free the allocated memory when done.

    return 0;
}