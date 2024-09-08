#include <cmath>
#include <cstring>

#include "Forms.hpp"


Form::Form(const char* color) {
    // Проверяем входной цвет
    if (isValidColor(color)) {
        // Определяем длину строки цвета
        color_length = strlen(color);
        // Выделяем память и копируем строку
        this->color = new char[color_length + 1];
        strcpy(this->color, color);
    } else {
        // Если цвет недопустим, устанавливаем серый
        color_length = strlen("gray");
        this->color = new char[color_length + 1];
        strcpy(this->color, "gray");
    }
}

Form::~Form() {
    delete[] color; // освобождаем выделенную память для цвета
}

const char* Form::getColor() const {
    return color;
}

bool Form::isValidColor(const char* color) {
    // Здесь можно добавить проверку на допустимые цвета
    // Например, можно проверить, что строка color является одним из допустимых цветов
    return true; // пока просто возвращаем true, не выполняя проверку
}


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
