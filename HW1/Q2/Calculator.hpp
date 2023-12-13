#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <iostream>
#include <cstdint>
#include <cmath>

template <typename T>
class Calculator
{
public:
    T addition(T num1, T num2) {    return num1 + num2; }

    T subtraction(T num1, T num2) { return num1 - num2; }

    T multiplication(T num1, T num2) {  return num1 * num2; }

    T division(T num1, T num2) {
        if (num2 == 0) {
            throw std::logic_error("Divide by zero error");
        }
        return num1 / num2;
    }

    T square(T num) {   return num * num;   }

    T exponentiation(T base, T pow) {   return std::pow(base, pow); }

    T modulus(T num1, T num2) { return num1 - (static_cast<int>(num1 / num2) * num2); }

};

#endif // !CALCULATOR_HPP