#include <iostream>
#include "Calculator.hpp"

Calculator<int> intCalculator;
Calculator<float> floatCalculator;
Calculator<double> doubleCalculator;

template <typename T>
void performCalculations(Calculator<T>& calc) {
    char choice;
    do {
        T num1, num2, result;
        char operation;

        std::cout << "Enter num1, operation (+, -, *, /), and num2: ";
        std::cout << operation << std::endl;
        std::cin >> num1 >> operation >> num2;
        try {
            switch (operation) {
                case '+':
                    result = calc.addition(num1, num2);
                    break;
                case '-':
                    result = calc.subtraction(num1, num2);
                    break;
                case '*':
                    result = calc.multiplication(num1, num2);
                    break;
                case '/':
                    if (num2 == 0) {
                        throw std::runtime_error("Division by zero is not allowed.");
                    }
                    result = calc.division(num1, num2);
                    break;
                default:
                    throw std::runtime_error("Invalid operation.");
            }

            std::cout << "Result: " << result << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        std::cout << "Do you want to perform another calculation? (y/n): ";
        std::cin >> choice;
    } while (choice == 'y' || choice == 'Y');
}

int main() {
    std::string dataType;
    
    std::cout << "Choose data type (int or float or double): ";
    std::cin >> dataType;
    Calculator<float> floatCalculator;
    std::cout << floatCalculator.exponentiation(2.0, 5.2) << std::endl;
    if (dataType == "int") {
        performCalculations(intCalculator);
    } else if (dataType == "float") {
        performCalculations(floatCalculator);
    } else if (dataType == "double") {
        performCalculations(doubleCalculator);
    } else {
        std::cout << "Invalid data type. Please choose 'int' or 'float'." << std::endl;
    }

    return 0;
}
