#include "calculator.h"
#include <iostream>

using namespace buildsystems;

int main() {
    std::cout << "Build Systems Native Library Demo\n";
    std::cout << "===================================\n\n";
    
    std::cout << "Addition: 5 + 3 = " << Calculator::add(5, 3) << "\n";
    std::cout << "Subtraction: 10 - 4 = " << Calculator::subtract(10, 4) << "\n";
    std::cout << "Multiplication: 6 * 7 = " << Calculator::multiply(6, 7) << "\n";
    std::cout << "Division: 15 / 3 = " << Calculator::divide(15, 3) << "\n";
    
    std::cout << "\nAll tests passed!\n";
    return 0;
}
