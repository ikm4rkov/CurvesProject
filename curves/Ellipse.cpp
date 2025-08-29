#include "pch.h"
#include "Ellipse.h"

Ellipse::Ellipse(double rx, double ry)
    : radiusX(rx > 0 ? rx : 1.0), radiusY(ry > 0 ? ry : 1.0) {
}

Point3D Ellipse::getPoint(double t) const {
    return { radiusX * cos(t), radiusY * sin(t), 0.0 };
}

Vector3D Ellipse::getDerivative(double t) const {
    return { -radiusX * sin(t), radiusY * cos(t), 0.0 };
}
