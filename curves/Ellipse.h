#ifdef CURVES_EXPORTS
#define CURVES_API __declspec(dllexport)
#else
#define CURVES_API __declspec(dllimport)
#endif

#pragma once
#include "Curve.h"

class CURVES_API Ellipse : public Curve {
    double radiusX, radiusY;
public:
    Ellipse(double rx, double ry);

    Point3D getPoint(double t) const override;
    Vector3D getDerivative(double t) const override;
};
