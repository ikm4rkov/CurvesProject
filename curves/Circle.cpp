#include "pch.h"
#include "Circle.h"
#include <memory>

Circle::Circle(double r) : radius(r > 0 ? r : 1.0) {}

double Circle::getRadius() const { return radius; }

Point3D Circle::getPoint(double t) const {
    return { radius * cos(t), radius * sin(t), 0.0 };
}

Vector3D Circle::getDerivative(double t) const {
    return { -radius * sin(t), radius * cos(t), 0.0 };
}

// Exported factory function
CURVES_API std::shared_ptr<Circle> CreateCircle(double radius) {
    return std::make_shared<Circle>(radius);
}