#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include <algorithm>
#include <cmath>

#include "Curve.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Helix.h"

#ifdef _OPENMP
#include <omp.h>
#endif

constexpr double PI = 3.14159265358979323846;

int main() {
    constexpr int N = 10;          // number of curves
    constexpr double t = PI / 4; // evaluation parameter

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> curveType(0, 2);
    std::uniform_real_distribution<> radiusDist(1.0, 10.0);
    std::uniform_real_distribution<> stepDist(0.5, 5.0);

    std::vector<std::shared_ptr<Curve>> curves;

    // populate curves
    for (int i = 0; i < N; ++i) {
        int type = curveType(gen);
        if (type == 0) {
            curves.push_back(std::make_shared<Circle>(radiusDist(gen)));
        }
        else if (type == 1) {
            curves.push_back(std::make_shared<Ellipse>(radiusDist(gen), radiusDist(gen)));
        }
        else {
            curves.push_back(std::make_shared<Helix>(radiusDist(gen), stepDist(gen)));
        }
    }

    // print points and derivatives
    std::cout << "All curves at t=PI/4:\n";
    for (const auto& c : curves) {
        Point3D p = c->getPoint(t);
        Vector3D d = c->getDerivative(t);
        std::cout << "Point: (" << p.x << ", " << p.y << ", " << p.z << ") "
            << " Derivative: (" << d.x << ", " << d.y << ", " << d.z << ")\n";
    }

    // extract circles
    std::vector<std::shared_ptr<Circle>> circles;
    for (const auto& c : curves) {
        if (auto circle = std::dynamic_pointer_cast<Circle>(c)) {
            circles.push_back(circle);
        }
    }

    // sort circles by radius
    std::sort(circles.begin(), circles.end(),
        [](const std::shared_ptr<Circle>& a, const std::shared_ptr<Circle>& b) {
            return a->getRadius() < b->getRadius();
        });

    // compute sum of radii
    double totalRadius = 0.0;
#ifdef _OPENMP
#pragma omp parallel for reduction(+:totalRadius)
#endif
    for (int i = 0; i < (int)circles.size(); ++i) {
        totalRadius += circles[i]->getRadius();
    }

    std::cout << "\nSorted circles by radius:\n";
    for (const auto& c : circles) {
        std::cout << "Circle radius: " << c->getRadius() << "\n";
    }
    std::cout << "Total radius sum = " << totalRadius << "\n";
}
