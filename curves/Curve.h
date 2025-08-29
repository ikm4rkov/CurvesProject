#ifdef CURVES_EXPORTS
#define CURVES_API __declspec(dllexport)
#else
#define CURVES_API __declspec(dllimport)
#endif

#pragma once
#include <cmath>

struct CURVES_API Point3D {
    double x, y, z;
};

struct CURVES_API Vector3D {
    double x, y, z;
};

class CURVES_API Curve {
public:
    virtual ~Curve() = default;

    virtual Point3D getPoint(double t) const = 0;
    virtual Vector3D getDerivative(double t) const = 0;

    Curve() = default;
};
