#pragma once

#include <math.h>

class Vector
{
public:
    float x = 0.0f;
    float y = 0.0f;

    Vector(float x, float y) : x(x), y(y) {}
    Vector() : x(0), y(0) {}

    Vector operator+(const Vector &other) const
    {
        return Vector(x + other.x, y + other.y);
    }

    Vector operator-(const Vector &other) const
    {
        return Vector(x - other.x, y - other.y);
    }

    Vector operator*(const Vector &other) const
    {
        return Vector(x * other.x, y * other.y);
    }

    Vector operator/(const Vector &other) const
    {
        return Vector(x / other.x, y / other.y);
    }

    Vector operator*(const float &other) const
    {
        return Vector(x * other, y * other);
    }

    Vector operator/(const float &other) const
    {
        return Vector(x / other, y / other);
    }

    bool operator==(const Vector &other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Vector &other) const
    {
        return x != other.x || y != other.y;
    }

    Vector &operator+=(const Vector &other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector &operator-=(const Vector &other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vector &operator*=(const Vector &other)
    {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    Vector &operator/=(const Vector &other)
    {
        x /= other.x;
        y /= other.y;
        return *this;
    }

    Vector &operator*=(const float &other)
    {
        x *= other;
        y *= other;
        return *this;
    }

    Vector &operator/=(const float &other)
    {
        x /= other;
        y /= other;
        return *this;
    }

    Vector operator-() const
    {
        return Vector(-x, -y);
    }

    float magnitude() const;

    Vector normalize() const;

    float distanceTo(const Vector &other) const;

    Vector directionTo(const Vector &other) const;
};
