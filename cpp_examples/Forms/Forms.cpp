#include <cmath>

#include "Forms.hpp"

double Circle::area() const {
    return 3.14 * radius * radius;
}

double Circle::perimeter() const {
    return 2 * 3.14 * radius;
}


double Square::area() const {
    return side * side;
}

double Square::perimeter() const {
    return 4 * side;
}


double Triangle::area() const {
    double s = (side1 + side2 + side3) / 2;
    return sqrt(s * (s - side1) * (s - side2) * (s - side3));
}

double Triangle::perimeter() const {
    return side1 + side2 + side3;
}


double Sphere::area() const {
    return 4 * 3.14 * radius * radius;
}

double Sphere::volume() const {
    return (4.0 / 3) * 3.14 * radius * radius * radius;
}


double Cube::area() const {
    return 6 * side * side;
}

double Cube::volume() const {
    return side * side * side;
}
