#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>

template<typename T>
struct Vector2D {
    T x, y;
    Vector2D() : x(T(0)), y(T(0)) {}
    Vector2D(T _x, T _y) : x(_x), y(_y) {}
    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }
    Vector2D operator-(const Vector2D& other) const {
        return Vector2D(x - other.x, y - other.y);
    }
    Vector2D operator*(const Vector2D& other) const {
        return Vector2D(x * other.x, y * other.y);
    }
    Vector2D operator/(const Vector2D& other) {
        if ((x || other.x || y || other.y) == 0) {
            printf("WARNING : Vector2D -> Division by zero not possible");
            return Vector2D(0, 0);
        } else {
            return Vector2D(x / other.x);
        }
    }
    T dot(const Vector2D& other) const {
        return x * other.x + y * other.y;
    }
    bool operator==(const Vector2D& other) const {
        return x == other.x && y == other.y;
    }
    bool operator>(const Vector2D& other) const {
        return x * y > other.x * other.y;
    }
    bool operator<(const Vector2D& other) const {
        return x * y < other.x * other.y;
    }
    bool operator<=(const Vector2D& other) const {
        return x * y <= other.x * other.y;
    }
    bool operator>=(const Vector2D& other) const {
        return x * y >= other.x * other.y;
    }
    bool operator!=(const Vector2D& other) const {
        return !(*this == other);
    }
    
    // Assignment operator
    Vector2D& operator=(const Vector2D& other) {
        x = other.x;
        y = other.y;
        return *this;
    }
};

template<typename T>
struct Vector3D {
    T x, y, z;

    Vector3D(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}

    // Addition
    Vector3D operator+(const Vector3D& other) const {
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }

    // Subtraction
    Vector3D operator-(const Vector3D& other) const {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }

    // Scalar Multiplication
    Vector3D operator*(const T& scalar) const {
        return Vector3D(x * scalar, y * scalar, z * scalar);
    }

    // Dot Product
    T dot(const Vector3D& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // Cross Product
    Vector3D cross(const Vector3D& other) const {
        return Vector3D(y * other.z - z * other.y,
                        z * other.x - x * other.z,
                        x * other.y - y * other.x);
    }
    bool operator==(const Vector3D& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    bool operator!=(const Vector3D& other) const {
        return !(*this == other);
    }

    // Assignment operator
    Vector3D& operator=(const Vector3D& other) {
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }
};

template<typename T>
struct Vector4D {
    T x, y, z, w;

    Vector4D(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w) {}

    // Addition
    Vector4D operator+(const Vector4D& other) const {
        return Vector4D(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    // Subtraction
    Vector4D operator-(const Vector4D& other) const {
        return Vector4D(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    // Scalar Multiplication
    Vector4D operator*(const T& scalar) const {
        return Vector4D(x * scalar, y * scalar, z * scalar, w * scalar);
    }

    // Dot Product
    T dot(const Vector4D& other) const {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }
    bool operator==(const Vector4D& other) const {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    bool operator!=(const Vector4D& other) const {
        return !(*this == other);
    }

    // Assignment operator
    Vector4D& operator=(const Vector4D& other) {
        x = other.x;
        y = other.y;
        z = other.z;
        w = other.w;
        return *this;
    }
};

#endif // VECTOR_HPP