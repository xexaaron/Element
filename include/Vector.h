#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <stdexcept>

template<typename T>
struct Vector2D {
    T x, y;
    Vector2D() : x(T(0)), y(T(0)) {}
    Vector2D(T _x, T _y) : x(_x), y(_y) {}
    Vector2D& operator=(const Vector2D& other) {
        x = other.x;
        y = other.y;
        return *this;
    }
    
    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }
    Vector2D operator+(const T& scalar) const {
        return Vector2D(x + scalar, y + scalar);
    }
    Vector2D operator-(const Vector2D& other) const {
        return Vector2D(x - other.x, y - other.y);
    }
    Vector2D operator-(const T& scalar) const {
        return Vector2D(x - scalar, y - scalar);
    }
    Vector2D operator*(const Vector2D& other) const {
        return Vector2D(x * other.x, y * other.y);
    }
    Vector2D operator*(const T& scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }
    Vector2D operator/(const Vector2D& other) {
        if ((x || other.x || y || other.y) == 0) {
            throw std::runtime_error("WARNING : Vector2D -> Division by zero not possible");
            return Vector2D(0, 0);
        } else {
            return Vector2D(x / other.x, y / other.y);
        }
    }
    Vector2D operator/(const T& scalar) const {
        if (scalar != T(0)) {
            return Vector2D(x / scalar, y / scalar);
        } else {
            throw std::runtime_error("WARNING : Vector2D -> Division by zero not possible");
            return Vector2D(0, 0);
        }
    }
    
    Vector2D operator+=(const Vector2D& other) const {
        return Vector2D(x += other.x, y += other.y);
    }
    Vector2D operator+=(const T& scalar) const {
        return Vector2D(x += scalar, y += scalar);
    }
    Vector2D operator-=(const Vector2D& other) const {
        return Vector2D(x -= other.x, y -= other.y);
    }
    Vector2D operator-=(const T& scalar) const {
        return Vector2D(x -= scalar, y -= scalar);
    }
    Vector2D operator*=(const Vector2D& other) const {
        return Vector2D(x *= other.x, y *= other.y);
    }
    Vector2D operator*=(const T& scalar) const {
        return Vector2D(x *= scalar, y *= scalar);
    }
    Vector2D operator/=(const Vector2D& other) {
        if ((x || other.x || y || other.y) == 0) {
            throw std::runtime_error("WARNING : Vector2D -> Division by zero not possible");
            return Vector2D(0, 0);
        } else {
            return Vector2D(x /= other.x, y /= other.y);
        }
    }
    Vector2D operator/=(const T& scalar) {
        if ((x || scalar || y ) == 0) {
            throw std::runtime_error("WARNING : Vector2D -> Division by zero not possible");
            return Vector2D(0, 0);
        } else {
            return Vector2D(x /= scalar, y /= scalar);
        }
    }
    
    T Magnitude() const {
        return sqrt(x * x + y * y);
    }
    T Dot(const Vector2D& other) const {
        return x * other.x + y * other.y;
    }
    Vector2D<T> CrossProduct(const Vector2D& other) const {
        return Vector2D(x * other.y - y * other.x);
    }
    Vector2D<T> Normalize() const {
        T mag = Magnitude();
        if (mag != T(0)) {
            return Vector2D<T>(x / mag, y / mag);
        } else {
            throw std::runtime_error("WARNING : Vector2D -> Division by zero not possible");
            return Vector2D<T>(0, 0);
        }
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
    
};

template<typename T>
struct Vector3D {
    T x, y, z;
    Vector3D() : x(T(0)), y(T(0)), z(T(0)) {}
    Vector3D(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
    Vector3D& operator=(const Vector3D& other) {
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }
    
    Vector3D operator+(const Vector3D& other) const {
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }
    Vector3D operator+(const T& scalar) const {
        return Vector3D(x + scalar, y + scalar, z + scalar);
    }
    Vector3D operator-(const Vector3D& other) const {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }
    Vector3D operator-(const T& scalar) const {
        return Vector3D(x - scalar, y - scalar, z - scalar);
    }
    Vector3D operator*(const Vector3D& other) const {
        return Vector3D(x * other.x, y * other.y, z * other.z);
    }
    Vector3D operator*(const T& scalar) const {
        return Vector3D(x * scalar, y * scalar, z * scalar);
    }
    Vector3D operator/(const Vector3D& other) const {
        return Vector3D(x / other.x, y / other.y, z / other.z);
    }
    Vector3D operator/(const T& scalar) const {
        return Vector3D(x / scalar, y / scalar, z / scalar);
    }
    
    Vector3D operator+=(const Vector3D& other) const {
        return Vector3D(x += other.x, y += other.y, z += other.z);
    }
    Vector3D operator+=(const T& scalar) const {
        return Vector3D(x += scalar, y += scalar, z += scalar);
    }
    Vector3D operator-=(const Vector3D& other) const {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }
    Vector3D operator-=(const T& scalar) const {
        return Vector3D(x -= scalar, y -= scalar, z -= scalar);
    }
    Vector3D operator*=(const Vector3D& other) const {
        return Vector3D(x *= other.x, y *= other.y, z *= other.z);
    }
    Vector3D operator*=(const T& scalar) const {
        return Vector3D(x *= scalar, y *= scalar, z *= scalar);
    }
    Vector3D operator/=(const Vector3D& other) const {
        return Vector3D(x /= other.x, y /= other.y, z /= other.z);
    }
    Vector3D operator/=(const T& scalar) const {
        return Vector3D(x /= scalar, y /= scalar, z /= scalar);
    }

    T Magnitude() const {
        return sqrt(x * x + y * y + z * z);
    }
    T Dot(const Vector3D& other) const {
        return x * other.x + y * other.y + z * other.z;
    }
    Vector3D CrossProduct(const Vector3D& other) const {
        return Vector3D(y * other.z - z * other.y,
                        z * other.x - x * other.z,
                        x * other.y - y * other.x);
    }
    Vector3D<T> Normalize() const {
        T mag = Magnitude();
        if (mag != T(0)) {
            return Vector3D<T>(x / mag, y / mag, z / mag);
        } else {
            throw std::runtime_error("WARNING : Vector2D -> Division by zero not possible");
            return Vector3D<T>(0, 0, 0);
        }
    }
    
    bool operator==(const Vector3D& other) const {
        return x == other.x && y == other.y && z == other.z;
    }
    bool operator>(const Vector3D& other) const {
        return x * y * z > other.x * other.y * other.z;
    }
    bool operator<(const Vector3D& other) const {
        return x * y * z < other.x * other.y * other.z;
    }
    bool operator<=(const Vector3D& other) const {
        return x * y * z <= other.x * other.y * other.z;
    }
    bool operator>=(const Vector3D& other) const {
        return x * y * z >= other.x * other.y * other.z;
    }
    bool operator!=(const Vector3D& other) const {
        return !(*this == other);
    }
    
};

template<typename T>
struct Vector4D {
    T x, y, z, w;
    Vector4D() : x(T(0)), y(T(0)), z(T(0)), w(T(0)) {}
    Vector4D(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w) {}
    Vector4D& operator=(const Vector4D& other) {
        x = other.x;
        y = other.y;
        z = other.z;
        w = other.w;
        return *this;
    }
    
    Vector4D operator+(const Vector4D& other) const {
        return Vector4D(x + other.x, y + other.y, z + other.z, w + other.w);
    }
    Vector4D operator+(const T& scalar) const {
        return Vector4D(x + scalar, y + scalar, z + scalar, w + scalar);
    }
    Vector4D operator-(const Vector4D& other) const {
        return Vector4D(x - other.x, y - other.y, z - other.z, w - other.w);
    }
    Vector4D operator-(const T& scalar) const {
        return Vector4D(x - scalar, y - scalar, z - scalar, w - scalar);
    }
    Vector4D operator*(const Vector4D& other) const {
        return Vector4D(x * other.x, y * other.y, z * other.z, w * other.w);
    }
    Vector4D operator*(const T& scalar) const {
        return Vector4D(x * scalar, y * scalar, z * scalar, w * scalar);
    }
    Vector4D operator/(const Vector4D& other) const {
        return Vector4D(x / other.x, y / other.y, z / other.z, w / other.w);
    }
    Vector4D operator/(const T& scalar) const {
        return Vector4D(x / scalar, y / scalar, z / scalar, w / scalar);
    }
    
    Vector4D operator+=(const Vector4D& other) const {
        return Vector4D(x += other.x, y += other.y, z += other.z, w += other.w);
    }
    Vector4D operator+=(const T& scalar) const {
        return Vector4D(x += scalar, y += scalar, z += scalar, w += scalar);
    }
    Vector4D operator-=(const Vector4D& other) const {
        return Vector4D(x -= other.x, y -= other.y, z -= other.z, w -= other.w);
    }
    Vector4D operator-=(const T& scalar) const {
        return Vector4D(x -= scalar, y -= scalar, z -= scalar, w -= scalar);
    }
    Vector4D operator*=(const Vector4D& other) const {
        return Vector4D(x *= other.x, y *= other.y, z *= other.z, w *= other.w);
    }
    Vector4D operator*=(const T& scalar) const {
        return Vector4D(x *= scalar, y *= scalar, z *= scalar, w *= scalar);
    }
    Vector4D operator/=(const Vector4D& other) const {
        return Vector4D(x /= other.x, y /= other.y, z /= other.z, w /= other.w);
    }
    Vector4D operator/=(const T& scalar) const {
        return Vector4D(x /= scalar, y /= scalar, z /= scalar, w /= scalar);
    }
    
    T Dot(const Vector4D& other) const {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }
    T Magnitude() const {
        return sqrt(x * x + y * y + z * z + w * w);
    }
    Vector4D<T> Normalize() const {
        T mag = Magnitude();
        if (mag != T(0)) {
            return Vector5D<T>(x / mag, y / mag, z / mag, w / mag);
        } else {
            throw std::runtime_error("WARNING : Vector2D -> Division by zero not possible");
            return Vector4D<T>(0, 0);
        }
    }
    
    bool operator==(const Vector4D& other) const {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }
    bool operator>(const Vector4D& other) const {
        return x * y * z * w > other.x * other.y * other.z * other.w;
    }
    bool operator<(const Vector4D& other) const {
        return x * y * z * w < other.x * other.y * other.z * other.w;
    }
    bool operator<=(const Vector4D& other) const {
        return x * y * z * w <= other.x * other.y * other.z * other.w;
    }
    bool operator>=(const Vector4D& other) const {
        return x * y * z * w >= other.x * other.y * other.z * other.w;
    }
    bool operator!=(const Vector4D& other) const {
        return !(*this == other);
    }
};

#endif // VECTOR_HPP