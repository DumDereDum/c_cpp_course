#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <iostream>

class Rational {
private:
    int numerator;
    int denominator;

    int gcd(int a, int b);
    void simplify();

public:
    Rational();
    Rational(int num, int denom);

    int getNumerator() const;
    int getDenominator() const;

    void setNumerator(int num);
    void setDenominator(int denom);

    void display() const;

    Rational operator+(const Rational& other) const;
    Rational operator-(const Rational& other) const;
    Rational operator*(const Rational& other) const;
    Rational operator/(const Rational& other) const;
    bool operator==(const Rational& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Rational& rational);

    operator double() const;
};

double operator+(double d, const Rational& rational);

#endif // RATIONAL_HPP
