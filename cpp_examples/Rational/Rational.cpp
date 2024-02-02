#include "Rational.hpp"

int Rational::gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

Rational::Rational() : numerator(0), denominator(1) {}

Rational::Rational(int num, int denom) : numerator(num), denominator(denom) {
    simplify();
}

void Rational::simplify() {
    int divisor = gcd(numerator, denominator);
    numerator /= divisor;
    denominator /= divisor;
}

void Rational::display() const {
    std::cout << numerator << "/" << denominator;
}

int Rational::getNumerator() const {
    return numerator;
}

int Rational::getDenominator() const {
    return denominator;
}

void Rational::setNumerator(int num) {
    numerator = num;
    simplify();
}

void Rational::setDenominator(int denom) {
    if (denom != 0) {
        denominator = denom;
    } else {
        std::cerr << "Denominator cannot be zero." << std::endl;
    }
    simplify();
}

Rational Rational::operator+(const Rational& other) const {
    int num = numerator * other.denominator + other.numerator * denominator;
    int denom = denominator * other.denominator;
    return Rational(num, denom);
}

Rational Rational::operator-(const Rational& other) const {
    int num = numerator * other.denominator - other.numerator * denominator;
    int denom = denominator * other.denominator;
    return Rational(num, denom);
}

Rational Rational::operator*(const Rational& other) const {
    int num = numerator * other.numerator;
    int denom = denominator * other.denominator;
    return Rational(num, denom);
}

Rational Rational::operator/(const Rational& other) const {
    int num = numerator * other.denominator;
    int denom = denominator * other.numerator;
    return Rational(num, denom);
}

bool Rational::operator==(const Rational& other) const {
    return (numerator == other.numerator) && (denominator == other.denominator);
}

std::ostream& operator<<(std::ostream& os, const Rational& rational) {
    os << rational.numerator << "/" << rational.denominator;
    return os;
}

Rational::operator double() const {
    return static_cast<double>(numerator) / denominator;
}

double operator+(double d, const Rational& rational) {
    return d + static_cast<double>(rational);
}
