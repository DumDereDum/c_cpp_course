class Form {
public:
    virtual ~Form() {}
    virtual double area() const = 0;
};

class TwoDimensionalForm : public Form {
public:
    virtual ~TwoDimensionalForm() {}
    virtual double perimeter() const = 0;
};

class ThreeDimensionalForm : public Form {
public:
    virtual ~ThreeDimensionalForm() {}
    virtual double volume() const = 0;
};

class Circle : public TwoDimensionalForm {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    ~Circle() {}
    double area() const override;
    double perimeter() const override;
};

class Square : public TwoDimensionalForm {
private:
    double side;
public:
    Square(double s) : side(s) {}
    ~Square() {}
    double area() const override;
    double perimeter() const override;
};

class Triangle : public TwoDimensionalForm {
private:
    double side1, side2, side3;
public:
    Triangle(double s1, double s2, double s3) : side1(s1), side2(s2), side3(s3) {}
    ~Triangle() {}
    double area() const override;
    double perimeter() const override;
};

class Sphere : public ThreeDimensionalForm {
private:
    double radius;
public:
    Sphere(double r) : radius(r) {}
    ~Sphere() {}
    double area() const override;
    double volume() const override;
};

class Cube : public ThreeDimensionalForm {
private:
    double side;
public:
    Cube(double s) : side(s) {}
    ~Cube() {}
    double area() const override;
    double volume() const override;
};