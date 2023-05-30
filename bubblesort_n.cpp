#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

void bubbleSort(int* data, int size) {
    #pragma omp parallel
    {
        for (int i = size - 1; i > 0; --i) {
            #pragma omp for
            for (int j = 0; j < i; ++j) {
                if (data[j] > data[j + 1]) {
                    // Swap elements
                    int temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            }
        }
    }
}

void printArray(const int* arr, int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    const int size = 1000;
    int data[size];

    // Generate random numbers
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < size; ++i) {
        data[i] = rand() % 1000;
    }

    std::cout << "Input Array: ";
    printArray(data, size);

    // Perform parallel bubble sort
    bubbleSort(data, size);

    std::cout << "Sorted Array: ";
    printArray(data, size);

    return 0;
}

