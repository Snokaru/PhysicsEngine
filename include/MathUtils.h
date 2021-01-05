#ifndef MATHUTILS_H
#define MATHUTILS_H
#include <cmath>
#include <ostream>

struct Vector2f {
    double x, y;
    Vector2f(double x, double y) {
        this->x = x;
        this->y = y;
    }
    Vector2f() {
        this->x = this->y = 0;
    }
    friend Vector2f operator+(const Vector2f& v1, const Vector2f& v2) {
        return Vector2f(v1.x + v2.x, v1.y + v2.y);
    }
    friend Vector2f operator-(const Vector2f& v1, const Vector2f& v2) {
        return Vector2f(v1.x - v2.x, v1.y - v2.y);
    }
    friend bool operator==(const Vector2f& v1, const Vector2f& v2) {
        return v1.x == v2.x && v1.y == v2.y;
    }
    friend double operator*(const Vector2f& v1, const Vector2f& v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }
    friend Vector2f operator*(const Vector2f& v1, const double value) {
        return Vector2f(v1.x * value, v1.y * value);
    }
    friend Vector2f operator/(const Vector2f& v, const double value) {
        return Vector2f(v.x / value, v.y / value);
    }
    friend std::ostream& operator<<(std::ostream& out, const Vector2f& v) {
        out << "(" << v.x << "," << v.y << ")";
        return out;
    }
    double length() { return std::sqrt(x * x + y * y); }
};

double clamp(double x, double min_value, double max_value);

#endif // MATHUTILS_H
