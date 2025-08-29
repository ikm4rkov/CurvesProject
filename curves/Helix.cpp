#include "pch.h"
#include "Helix.h"
constexpr double PI = 3.14159265358979323846;

Helix::Helix(double r, double s)
    : radius(r > 0 ? r : 1.0), step(s) {
}

Point3D Helix::getPoint(double t) const {
    return { radius * cos(t), radius * sin(t), step * t / (2 * PI) };
}

Vector3D Helix::getDerivative(double t) const {
    return { -radius * sin(t), radius * cos(t), step / (2 * PI) };
}
