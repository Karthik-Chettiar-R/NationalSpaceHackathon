#include <iostream>
#include <vector>
#include <cmath>
#include "nanoflann.hpp"

using namespace nanoflann;
using namespace std;

// -----------------------------
// Point Cloud for Debris
// -----------------------------
struct PointCloud {
    struct Point {
        double x, y, z;
    };

    vector<Point> pts;

    inline size_t kdtree_get_point_count() const { return pts.size(); }

    inline double kdtree_get_pt(const size_t idx, int dim) const {
        if (dim == 0) return pts[idx].x;
        if (dim == 1) return pts[idx].y;
        return pts[idx].z;
    }

    template <class BBOX>
    bool kdtree_get_bbox(BBOX&) const { return false; }
};

// -----------------------------
// KD Tree Type
// -----------------------------
typedef KDTreeSingleIndexAdaptor<
    L2_Simple_Adaptor<double, PointCloud>,
    PointCloud,
    3
> KDTree;

// -----------------------------
// Satellite Struct
// -----------------------------
struct Satellite {
    double x, y, z;
};

// -----------------------------
// Main
// -----------------------------
int main() {

    // -----------------------------
    // Dummy Debris Data
    // -----------------------------
    PointCloud cloud;

    cloud.pts = {
        {1000, 2000, 3000},
        {1010, 2010, 3010},
        {5000, 6000, 7000},
        {1020, 2020, 3020},
        {8000, 9000, 10000}
    };

    // -----------------------------
    // Dummy Satellite Data
    // -----------------------------
    vector<Satellite> satellites = {
        {1005, 2005, 3005},   // close to first few debris
        {7000, 8000, 9000}    // close to last debris
    };

    // -----------------------------
    // Build KD-tree
    // -----------------------------
    KDTree tree(3, cloud, KDTreeSingleIndexAdaptorParams(10));
    tree.buildIndex();

    // -----------------------------
    // Radius threshold (km)
    // -----------------------------
    double radius = 50.0;  // 50 units (assume km)
    double radius_sq = radius * radius;

    // -----------------------------
    // Query for each satellite
    // -----------------------------
    for (size_t i = 0; i < satellites.size(); i++) {

        double query_pt[3] = {
            satellites[i].x,
            satellites[i].y,
            satellites[i].z
        };

        vector<nanoflann::ResultItem<unsigned int, double>> matches;
        nanoflann::SearchParameters params;

        size_t found = tree.radiusSearch(query_pt, radius_sq, matches, params);

        cout << "\nSatellite " << i << " at ("
             << satellites[i].x << ", "
             << satellites[i].y << ", "
             << satellites[i].z << ")\n";

        cout << "Nearby debris found: " << found << endl;

        for (auto& match : matches) {
            size_t idx = match.first;
            double dist = sqrt(match.second);

            cout << "  Debris " << idx
                 << " at (" << cloud.pts[idx].x << ", "
                 << cloud.pts[idx].y << ", "
                 << cloud.pts[idx].z << ")"
                 << " | Distance = " << dist << endl;
        }
    }

    return 0;
}