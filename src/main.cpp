#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <complex>
#include <exception>

#include "Numeric.hpp"
#include "NumericType.hpp"

int main() {
    std::cout << "==========================================\n";
    std::cout << "    GENERIC NUMERIC DATA TYPE DEMO       \n";
    std::cout << "==========================================\n\n";

    // 1. Storing mixed numeric types in std::vector<std::unique_ptr<Numeric>>
    std::vector<std::unique_ptr<Numeric>> numbers;

    numbers.push_back(std::make_unique<NumericType<int>>(42));
    numbers.push_back(std::make_unique<NumericType<int>>(10));
    numbers.push_back(std::make_unique<NumericType<double>>(3.14159));
    numbers.push_back(std::make_unique<NumericType<double>>(1.414));
    numbers.push_back(std::make_unique<NumericType<std::complex<double>>>(std::complex<double>(3.0, 4.0))); // Magnitude = 5.0
    numbers.push_back(std::make_unique<NumericType<std::complex<double>>>(std::complex<double>(1.0, 1.0))); // Magnitude = 1.414

    // 2. Printing all elements via toString() and stream output
    std::cout << "--- Initial Vector Elements ---\n";
    for (size_t i = 0; i < numbers.size(); ++i) {
        std::cout << "Element [" << i << "]: ";
        numbers[i]->print(std::cout);
        std::cout << " (toString: " << numbers[i]->toString() << ")\n";
    }
    std::cout << "\n";

    // 3. Testing Arithmetic Operations (between matching types)
    std::cout << "--- Arithmetic Operations ---\n";
    try {
        // Adding two integers (index 0 and index 1)
        auto intSum = numbers[0]->add(*numbers[1]);
        std::cout << numbers[0]->toString() << " + " << numbers[1]->toString() 
                  << " = " << intSum->toString() << "\n";

        // Multiplying two doubles (index 2 and index 3)
        auto doubleProd = numbers[2]->multiply(*numbers[3]);
        std::cout << numbers[2]->toString() << " * " << numbers[3]->toString() 
                  << " = " << doubleProd->toString() << "\n";

        // Subtracting complex numbers (index 4 and index 5)
        auto complexDiff = numbers[4]->subtract(*numbers[5]);
        std::cout << numbers[4]->toString() << " - " << numbers[5]->toString() 
                  << " = " << complexDiff->toString() << "\n";

    } catch (const std::exception& e) {
        std::cerr << "Arithmetic Error: " << e.what() << "\n";
    }
    std::cout << "\n";

    // 4. Exception Handling (attempting arithmetic between different concrete types)
    std::cout << "--- Type Safety & Exception Handling ---\n";
    try {
        std::cout << "Attempting to add int (" << numbers[0]->toString() 
                  << ") and double (" << numbers[2]->toString() << ")... \n";
        auto invalidSum = numbers[0]->add(*numbers[2]);
    } catch (const std::invalid_argument& e) {
        std::cout << "Caught Expected Exception: " << e.what() << "\n";
    }
    std::cout << "\n";

    // Sorting Vectors of Polymorphic Pointers using std::sort
    // Sorting separate vectors for each concrete type to demonstrate comparison functions
    // Sorting can only work for same concrete type inside vector, otherwise it throws an exception of invalid argument due to incompatible comparison
    std::cout << "--- Sorting Numeric Elements ---\n";

    std::vector<std::unique_ptr<Numeric>> intVector;
    intVector.push_back(std::make_unique<NumericType<int>>(100));
    intVector.push_back(std::make_unique<NumericType<int>>(15));
    intVector.push_back(std::make_unique<NumericType<int>>(42));

    std::cout << "Before Sort: ";
    for (const auto& elem : intVector) std::cout << elem->toString() << " ";
    std::cout << "\n";

    // Sort using custom comparator that delegates to isLessThan
    std::sort(intVector.begin(), intVector.end(), 
        [](const std::unique_ptr<Numeric>& a, const std::unique_ptr<Numeric>& b) {
            return a->isLessThan(*b);
        });

    std::cout << "After Sort:  ";
    for (const auto& elem : intVector) std::cout << elem->toString() << " ";
    std::cout << "\n\n";

    std::cout << "==========================================\n";
    std::cout << "           ALL TESTS COMPLETED            \n";
    std::cout << "==========================================\n";

    return 0;
}