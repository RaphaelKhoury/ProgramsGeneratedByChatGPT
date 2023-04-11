#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::cout << "Enter the number of elements in the list : ";
    std::cin >> n;

    std::vector<int> list(n);
    for (int i = 0; i < n; i++) {
        std::cout << "Enter element number " << i + 1 << " : ";
        std::cin >> list[i];
    }

    std::sort(list.begin(), list.end());

    while (true) {
        std::cout << std::endl;
        std::cout << "What would you like to do ?" << std::endl;
        std::cout << "1. Print the sorted list" << std::endl;
        std::cout << "2. Print a specific element from the list" << std::endl;
        std::cout << "3. Exit the program" << std::endl;
        std::cout << "Enter your choice (1-3) : ";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "The sorted list is : ";
            for (int i = 0; i < n; i++) {
                std::cout << list[i] << " ";
            }
            std::cout << std::endl;
        }
        else if (choice == 2) {
            int index;
            std::cout << "Enter the index of the element (from 1 to " << n << ") : ";
            std::cin >> index;

            if (index >= 1 && index <= n) {
                std::cout << "Element number" << index << " is : " << list[index - 1] << std::endl;
            }
            else {
                std::cout << "Invalid index. Please enter an value between  1 and " << n << "." << std::endl;
            }
        }
        else if (choice == 3) {
            std::cout << "Goodbye !" << std::endl;
            break;
        }
        else {
            std::cout << "Invalid choice. Please enter a number between 1 and 3." << std::endl;
        }
    }

    return 0;
}
