#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

void merge(int* data, int left, int mid, int right) {
    int size1 = mid - left + 1;
    int size2 = right - mid;

    int* leftArray = new int[size1];
    int* rightArray = new int[size2];

    for (int i = 0; i < size1; ++i) {
        leftArray[i] = data[left + i];
    }
    for (int i = 0; i < size2; ++i) {
        rightArray[i] = data[mid + 1 + i];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < size1 && j < size2) {
        if (leftArray[i] <= rightArray[j]) {
            data[k] = leftArray[i];
            ++i;
        } else {
            data[k] = rightArray[j];
            ++j;
        }
        ++k;
    }

    while (i < size1) {
        data[k] = leftArray[i];
        ++i;
        ++k;
    }

    while (j < size2) {
        data[k] = rightArray[j];
        ++j;
        ++k;
    }

    delete[] leftArray;
    delete[] rightArray;
}

void mergeSort(int* data, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                mergeSort(data, left, mid);
            }

            #pragma omp section
            {
                mergeSort(data, mid + 1, right);
            }
        }

        merge(data, left, mid, right);
    }
}

int main() {
    const int size = 10000;
    int data[size];

    // Generate random numbers
    srand(static_cast<unsigned int>(time(NULL)));
    for (int i = 0; i < size; ++i) {
        data[i] = rand();
    }

    // Perform parallel merge sort
    #pragma omp parallel
    {
        #pragma omp single nowait
        {
            mergeSort(data, 0, size - 1);
        }
    }

    // Print sorted array
    std::cout << "Sorted array: ";
    for (int i = 0; i < size; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}

