#include <iostream>
#include "Forms.hpp"

int main() {
    Circle circle(5);
    Square square(4);
    Triangle triangle(3, 4, 5);
    Sphere sphere(6);
    Cube cube(7);


    const int size = 5;
    Form* forms[size] = {&circle, &square, &triangle, &sphere, &cube};

    for (int i = 0; i < size; ++i) {
        std::cout << "Area: " << forms[i]->area() << std::endl;
    }

    const int d2size = 3;
    TwoDimensionalForm* d2forms[size] = {&circle, &square, &triangle};

    for (int i = 0; i < d2size; ++i) {
        std::cout << "Area:      " << d2forms[i]->area() << std::endl;
        std::cout << "Perimeter: " << d2forms[i]->perimeter() << std::endl;
    }

    const int d3size = 2;
    ThreeDimensionalForm* d3forms[size] = {&sphere, &cube};

    for (int i = 0; i < d3size; ++i) {
        std::cout << "Area:   " << d3forms[i]->area() << std::endl;
        std::cout << "Volume: " << d3forms[i]->volume() << std::endl;
    }

    return 0;
}
