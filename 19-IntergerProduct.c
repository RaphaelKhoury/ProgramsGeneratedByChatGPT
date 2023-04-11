#include <stdio.h>

int getProduct(int arr[], int n) {
    int product = 1;
    for (int i = 0; i < n; i++) {
        product *= arr[i];
    }
    return product;
}

int main() {
    int arr[] = {2, 3, 5, 7, 11};
    int n = sizeof(arr) / sizeof(arr[0]);
    int product = getProduct(arr, n);
    printf("Product of array elements is: %d\n", product);
    return 0;
}
