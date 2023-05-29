#include <iostream>
#include <omp.h>

int main() {
    int array[1000];
    int size;

    // Get the size of the array from the user
    std::cout << "Enter the size of the array (up to 1000): ";
    std::cin >> size;

    if (size <= 0 || size > 1000) {
        std::cout << "Invalid array size. Please enter a size between 1 and 1000." << std::endl;
        return 1;
    }

    // Get the array elements from the user
    std::cout << "Enter the array elements:" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cin >> array[i];
    }

    int min_val = array[0];
    int max_val = array[0];
    int sum_val = 0;
    double avg_val = 0.0;

    #pragma omp parallel for reduction(min:min_val) reduction(max:max_val) reduction(+:sum_val)
    for (int i = 0; i < size; i++) {
        min_val = std::min(min_val, array[i]);
        max_val = std::max(max_val, array[i]);
        sum_val += array[i];
    }

    avg_val = static_cast<double>(sum_val) / size;

    std::cout << "Minimum: " << min_val << std::endl;
    std::cout << "Maximum: " << max_val << std::endl;
    std::cout << "Sum: " << sum_val << std::endl;
    std::cout << "Average: " << avg_val << std::endl;

    return 0;
}

