#include <iostream>
#include "Rational.hpp"

int main() {
    Rational r1(30, 40);
    Rational r2(2, 4);

    std::cout << "r1 = ";
    r1.display();
    std::cout << std::endl;

    std::cout << "r2 = ";
    r2.display();
    std::cout << std::endl;

    std::cout << "r1 numerator: " << r1.getNumerator() << std::endl;
    std::cout << "r1 denominator: " << r1.getDenominator() << std::endl;

    r1.setNumerator(5);
    r1.setDenominator(6);
    std::cout << "After setting new values: " << std::endl;
    std::cout << "r1 = ";
    r1.display();
    std::cout << std::endl;

    Rational sum = r1 + r2;
    std::cout << "r1 + r2 = ";
    sum.display();
    std::cout << std::endl;

    Rational difference = r1 - r2;
    std::cout << "r1 - r2 = ";
    difference.display();
    std::cout << std::endl;

    Rational product = r1 * r2;
    std::cout << "r1 * r2 = ";
    product.display();
    std::cout << std::endl;

    Rational quotient = r1 / r2;
    std::cout << "r1 / r2 = ";
    quotient.display();
    std::cout << std::endl;

    std::cout << "Is r1 equal to r2? " << (r1 == r2 ? "Yes" : "No") << std::endl;

    std::cout << "r1: " << r1 << std::endl;
    std::cout << "r2: " << r2 << std::endl;

    std::cout << "r1: " << double(r1) << std::endl;
    std::cout << "r2: " << double(r2) << std::endl;

    std::cout << "1.4 + 1/2 = " << 1.4 + Rational(1, 2) << std::endl;
    

    return 0;
}
