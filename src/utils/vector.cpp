#include "jett/utils/vector.hpp"

float Vector::magnitude() const
{
    return sqrt(x * x + y * y);
}

Vector Vector::normalize() const
{
    float mag = magnitude();

    if (mag == 0)
    {
        return Vector(0, 0);
    }

    return Vector(x / mag, y / mag);
}

float Vector::distanceTo(const Vector &other) const
{
    return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
}

Vector Vector::directionTo(const Vector &other) const
{
    Vector direction = other - *this;

    return direction.normalize();
}