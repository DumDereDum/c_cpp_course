#ifndef FORM_HPP
#define FORM_HPP

#include <iostream>


class Form {
public:
    Form(const char* color = "gray");
    virtual ~Form(); // Виртуальный деструктор
    virtual double area() const = 0; // Чисто виртуальная функция для вычисления площади
    const char* getColor() const; // Метод для возврата цвета
protected:
    char* color; // Поле для хранения цвета
    size_t color_length; // Длина строки цвета
    bool isValidColor(const char* color); // Функция для проверки допустимости цвета
};


class TwoDimensionalForm : public Form {
public:
    TwoDimensionalForm(const char* color = "gray", double x = 0.0, double y = 0.0)
        : Form(color), x(x), y(y) {};

    virtual ~TwoDimensionalForm() {} // Виртуальный деструктор
    
    // Геттеры и сеттеры для координат
    double getX() const { return x; }
    double getY() const { return y; }
    void setX(double x) { this->x = x; }
    void setY(double y) { this->y = y; }

    // Чисто виртуальная функция для вычисления периметра
    virtual double perimeter() const = 0;

protected:
    double x; // координата x
    double y; // координата y
};


class Circle : public TwoDimensionalForm {
public:
    Circle(const char* color = "gray", double x = 0.0, double y = 0.0, double r = 1.0)
        : TwoDimensionalForm(color, x, y), radius(r) {}
        
    ~Circle() {}

    // Переопределение виртуальной функции area() для вычисления площади круга
    double area() const override; 
    // Переопределение виртуальной функции perimeter() для вычисления периметра круга
    double perimeter() const override; 
private:
    double radius;
};

class Square : public TwoDimensionalForm {
public:
    Square(const char* color = "gray", double x = 0.0, double y = 0.0, double s = 1.0)\
        : TwoDimensionalForm(color, x, y), side(s) {}

    ~Square() {}

    // Переопределение виртуальной функции area() для вычисления площади квадрата
    double area() const override;
    // Переопределение виртуальной функции perimeter() для вычисления периметра квадрата
    double perimeter() const override;
private:
    double side;
};

class Triangle : public TwoDimensionalForm {
public:
    Triangle(const char* color = "gray", double x = 0.0, double y = 0.0, double s1 = 1.0, double s2 = 1.0, double s3 = 1.0)
        : TwoDimensionalForm(color, x, y), side1(s1), side2(s2), side3(s3) {}

    ~Triangle() {}

    // Переопределение виртуальной функции area() для вычисления площади треугольника
    double area() const override;
    // Переопределение виртуальной функции perimeter() для вычисления периметра треугольника
    double perimeter() const override;
private:
    double side1, side2, side3;
};


class ThreeDimensionalForm : public Form {
public:
    ThreeDimensionalForm(const char* color = "gray", double x = 0.0, double y = 0.0, double z = 0.0)
        : Form(color), x(x), y(y), z(z) {}

    virtual ~ThreeDimensionalForm() {} // Виртуальный деструктор

    // Геттеры и сеттеры для координат
    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }
    void setX(double x) { this->x = x; }
    void setY(double y) { this->y = y; }
    void setZ(double z) { this->z = z; }

    // Чисто виртуальная функция для вычисления объема
    virtual double volume() const = 0;

protected:
    double x; // координата x
    double y; // координата y
    double z; // координата z
};

class Sphere : public ThreeDimensionalForm {
private:
    double radius;
public:
    Sphere(const char* color = "gray", double x = 0.0, double y = 0.0, double z = 0.0, double r = 1.0)
        : ThreeDimensionalForm(color, x, y, z), radius(r) {}
    ~Sphere() {}
    
    // Переопределение виртуальной функции для вычисления площади поверхности сферы
    double area() const override;
    // Переопределение виртуальной функции для вычисления объема сферы
    double volume() const override;
};

class Cube : public ThreeDimensionalForm {
private:
    double side;
public:
    Cube(const char* color = "gray", double x = 0.0, double y = 0.0, double z = 0.0, double s = 1.0)
        : ThreeDimensionalForm(color, x, y, z), side(s) {}
    ~Cube() {}

    // Переопределение виртуальной функции для вычисления площади поверхности куба
    double area() const override;
    // Переопределение виртуальной функции для вычисления объема куба
    double volume() const override;
};

#endif // FORM_HPP
