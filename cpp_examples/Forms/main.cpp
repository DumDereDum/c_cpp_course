#include <iostream>
#include "Forms.hpp"

int main() {
    Circle circle;
    Square square;
    Triangle triangle;
    Sphere sphere;
    Cube cube;


    const int size = 5;
    Form* forms[size] = {&circle, &square, &triangle, &sphere, &cube};

    std::cout << "\n<<< FORM COUT >>> \n";
    for (int i = 0; i < size; ++i) {
        std::cout << i <<" Area:  " << forms[i]->area() << std::endl;
        std::cout << "  Color: " << forms[i]->getColor() << std::endl;
    }

    const int d2size = 3;
    TwoDimensionalForm* d2forms[size] = {&circle, &square, &triangle};
    std::cout << "\n<<< 2D COUT >>> \n";
    for (int i = 0; i < d2size; ++i) {
        std::cout << i << " Area:      " << d2forms[i]->area() << std::endl;
        std::cout << "  Color:     " << d2forms[i]->getColor() << std::endl;
        std::cout << "  Coords:    (" 
                  << d2forms[i]->getX() << ", " 
                  << d2forms[i]->getY() << ")" << std::endl; 
        std::cout << "  Perimeter: " << d2forms[i]->perimeter() << std::endl;
    }

    const int d3size = 2;
    ThreeDimensionalForm* d3forms[size] = {&sphere, &cube};
    std::cout << "\n<<< 3D COUT >>> \n";
    for (int i = 0; i < d3size; ++i) {
        std::cout << i << " Area:   " << d3forms[i]->area() << std::endl;
        std::cout << "  Color:  " << d3forms[i]->getColor() << std::endl;
        std::cout << "  Coords: (" 
                  << d3forms[i]->getX() << ", " 
                  << d3forms[i]->getY() << ", " 
                  << d3forms[i]->getZ() << ")" << std::endl; 
        std::cout << "  Volume: " << d3forms[i]->volume() << std::endl;
    }

    return 0;
}
