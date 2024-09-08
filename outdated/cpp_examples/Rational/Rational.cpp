#include <cmath>

#include "Rational.hpp"

Rational::Rational(int num, int denom) : numerator(num), denominator(denom) {
    simplify();
}

Rational::Rational(double value) {
    const double EPSILON = 1e-9;
    int sign = (value < 0) ? -1 : 1;
    double absValue = std::abs(value);
    double fractionPart;
    double intPart = std::modf(absValue, &fractionPart);

    numerator = static_cast<int>(intPart) * sign;
    denominator = 1;
    if (fractionPart > EPSILON) {
        while (std::abs(fractionPart - round(fractionPart)) > EPSILON) {
            fractionPart *= 10;
            denominator *= 10;
        }
        numerator = static_cast<int>((numerator * denominator) + round(fractionPart)) * sign;
    }
}

Rational::Rational(const Rational& other) {
    numerator = other.numerator;
    denominator = other.denominator;
}

Rational::Rational(Rational&& other) {
    numerator = std::move(other.numerator);
    denominator = std::move(other.denominator);
}

int Rational::gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
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

Rational& Rational::operator=(Rational& other) {
    if (this != &other) {
        numerator = other.numerator;
        denominator = other.denominator;
    }
    return *this;
}

Rational& Rational::operator=(Rational&& other) {
    if (this != &other) {
        numerator = other.numerator;
        denominator = other.denominator;
        other.numerator = 0;
        other.denominator = 1;
    }
    return *this;
}

bool Rational::operator==(const Rational& other) const {
    return (numerator == other.numerator) && (denominator == other.denominator);
}

bool Rational::operator!=(const Rational& other) const {
    return (numerator * other.denominator != other.numerator * denominator);
}

bool Rational::operator<(const Rational& other) const {
    return (numerator * other.denominator < other.numerator * denominator);
}

bool Rational::operator>(const Rational& other) const {
    return (numerator * other.denominator > other.numerator * denominator);
}

bool Rational::operator<=(const Rational& other) const {
    return (numerator * other.denominator <= other.numerator * denominator);
}

bool Rational::operator>=(const Rational& other) const {
    return (numerator * other.denominator >= other.numerator * denominator);
}

Rational Rational::operator!() const {
    return Rational(denominator, numerator);
}

int Rational::operator[](int index) const {
    if (index == 0) return numerator;
    else if (index == 1) return denominator;
    else throw std::out_of_range("Index out of range for Rational object");
}

double Rational::operator()() const {
    return static_cast<double>(numerator) / static_cast<double>(denominator);
}

std::ostream& operator<<(std::ostream& os, const Rational& rational) {
    os << rational.numerator << "/" << rational.denominator;
    return os;
}

std::istream& operator>>(std::istream& in, Rational& rational) {
    int num, denom;
    char slash;
    in >> num;
    if (!in.eof() && in.peek() == '/') {
        in >> slash;
        in >> denom;
        if (denom == 0) {
            in.setstate(std::ios::failbit);
            return in;
        }
    } else {
        denom = 1;
    }
    rational = Rational(num, denom);
    return in;
}

Rational::operator double() const {
    return static_cast<double>(numerator) / denominator;
}

Rational::operator int() const {
    return numerator / denominator;
}

Rational operator+(double d, const Rational& rational) {
    return Rational(d) + rational;
}

Rational operator-(double d, const Rational& rational) {
    return Rational(d) - rational;
}

Rational operator*(double d, const Rational& rational) {
    return Rational(d) * rational;
}

Rational operator/(double d, const Rational& rational) {
    return Rational(d) / rational;
}