#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <iostream>

class Rational {

public:
    Rational() : numerator(0), denominator(1) {};
    Rational(int num) : numerator(num), denominator(1) {};
    Rational(int num, int denom);
    Rational(double value);
    Rational(const Rational& other);
    Rational(Rational&& other);

    ~Rational(){};

    int getNumerator() const;
    int getDenominator() const;

    void setNumerator(int num);
    void setDenominator(int denom);

    void display() const;

    Rational operator+(const Rational& other) const;
    Rational operator-(const Rational& other) const;
    Rational operator*(const Rational& other) const;
    Rational operator/(const Rational& other) const;

    Rational& operator=(Rational& other);
    Rational& operator=(Rational&& other);

    bool operator==(const Rational& other) const;
    bool operator!=(const Rational& other) const;
    bool operator<(const Rational& other) const;
    bool operator>(const Rational& other) const;
    bool operator<=(const Rational& other) const;
    bool operator>=(const Rational& other) const;

    Rational operator!() const;
    int operator[](int index) const;
    double operator()() const;
    
    operator double() const;
    operator int() const;

    friend std::ostream& operator<<(std::ostream& os, const Rational& rational);
    friend std::istream& operator>>(std::istream& in, Rational& rational);

private:
    int numerator;
    int denominator;

    int gcd(int a, int b);
    void simplify();

};

Rational operator+(double d, const Rational& rational);
Rational operator-(double d, const Rational& rational);
Rational operator*(double d, const Rational& rational);
Rational operator/(double d, const Rational& rational);


#endif // RATIONAL_HPP
