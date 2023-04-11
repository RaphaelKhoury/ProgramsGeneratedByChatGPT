Copy code
void concatenateStrings(const char* str1, int size1, const char* str2, int size2, char* result, int maxResultSize) {
    int totalSize = size1 + size2;
    if (totalSize > maxResultSize - 1) {
        // if the total size of the concatenated string exceeds the maximum size of the result buffer,
        // truncate the second string to fit within the remaining space in the buffer
        size2 = maxResultSize - size1 - 1;
    }
    memcpy(result, str1, size1);
    memcpy(result + size1, str2, size2);
    result[size1 + size2] = '\0'; // null-terminate the concatenated string
}