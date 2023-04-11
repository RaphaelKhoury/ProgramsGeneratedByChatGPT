#include <cstring> // for memcpy()

void concatenateStrings(const char* str1, int size1, const char* str2, int size2, char* result) {
    memcpy(result, str1, size1);
    memcpy(result + size1, str2, size2);
}