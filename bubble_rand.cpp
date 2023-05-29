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

int main() {
    const int size = 10000;
    int data[size];

    // Generate random numbers
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < size; ++i) {
        data[i] = rand() % 10000;
    }
    
    // Perform parallel bubble sort
    bubbleSort(data, size);
    
    // Print sorted array
    std::cout << "Sorted array: ";
    for (int i = 0; i < size; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
    
    return 0;
}

