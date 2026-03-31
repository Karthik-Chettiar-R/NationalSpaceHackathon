#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>
#include <cmath>

namespace py = pybind11;

// Constants
const double mu = 398600.4418;   // km^3/s^2
const double Re = 6378.137;      // km
const double J2 = 1.08263e-3;

// Function to compute acceleration
std::vector<double> satellite_acceleration(std::vector<double> r) {
    double x = r[0];
    double y = r[1];
    double z = r[2];

    double r_mag = sqrt(x*x + y*y + z*z);

    // --- Two-body gravity ---
    double factor = -mu / pow(r_mag, 3);
    double ax = factor * x;
    double ay = factor * y;
    double az = factor * z;

    // --- J2 perturbation ---
    double z2 = z * z;
    double r2 = r_mag * r_mag;

    double j2_factor = (3.0 / 2.0) * J2 * mu * Re * Re / pow(r_mag, 5);

    double ax_j2 = j2_factor * x * (5.0 * z2 / r2 - 1.0);
    double ay_j2 = j2_factor * y * (5.0 * z2 / r2 - 1.0);
    double az_j2 = j2_factor * z * (5.0 * z2 / r2 - 3.0);

    // Total acceleration
    return {
        ax + ax_j2,
        ay + ay_j2,
        az + az_j2
    };
}

// Python module
PYBIND11_MODULE(physicsEngine, m) {
    m.doc() = "Satellite motion with J2 perturbation";

    m.def("acceleration", &satellite_acceleration,
          "Compute acceleration vector given position [x, y, z]");
}