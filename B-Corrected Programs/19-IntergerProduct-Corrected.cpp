unsigned long long getProduct(int arr[], int n) {
    unsigned long long product = 1;
    for (int i = 0; i < n; i++) {
        product *= arr[i];
    }
    return product;
}
