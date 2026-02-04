#include <bits/stdc++.h>

using ll = long long;
using ld = long double;

using T = ld;
using pt = std::array<T, 2>;
using vec = std::array<T, 2>;
using line = std::array<pt, 2>;
using linear = std::array<T, 2>;

constexpr ld eps = 1e-7; // change if needed

namespace Geo {
    T dot(const vec &a, const vec &b) {
        return a[0] * b[0] + a[1] * b[1];
    }
    
    T cross(const vec &a, const vec &b) {
        return a[0] * b[1] - a[1] * b[0];
    }
    
    vec operator-(const pt &a, const pt &b) {
        return {a[0] - b[0], a[1] - b[1]};
    }
    
    vec operator+(const pt &a, const pt &b) {
        return {a[0] + b[0], a[1] + b[1]};
    }
    
    vec operator*(const vec &v, T d) {
        return {v[0] * d, v[1] * d};
    }

    T orient(const pt &a, const pt &b, const pt &c) {
        return cross(b - a, c - a);
    }

    int sign(T val) {
        return (val > 0) - (val < 0);
    }

    bool colinear(const line &l, const pt &c) {
        const auto &[a, b] = l;
        const T o = orient(a, c, b);
        if ((std::is_integral_v<T> && o != 0) || std::abs(o) > eps) {
            return false;
        }

        return std::min(a[0], b[0]) <= c[0] && c[0] <= std::max(a[0], b[0]) &&
                std::min(a[1], b[1]) <= c[1] && c[1] <= std::max(a[1], b[1]);
    }

    bool intersect(const line &l1, const line &l2) {
        const auto &[a, b] = l1;
        const auto &[c, d] = l2;

        if (colinear(l1, c) || colinear(l1, d) ||
            colinear(l2, a) || colinear(l2, b)) {
            return true;
        }

        return sign(orient(a, b, c)) * sign(orient(a, b, d)) < 0 &&
               sign(orient(c, d, a)) * sign(orient(c, d, b)) < 0;
    }

    pt get_intersect(const line &l1, const line &l2) {
        const auto &[a, b] = l1;
        const auto &[c, d] = l2;

        return intersect(make_linear(l1), make_linear(l2));
    }

    T dist(const pt &a, const pt &b) {
        const T dx = std::abs(a[0] - b[0]);
        const T dy = std::abs(a[1] - b[1]);
        return std::sqrt(dx * dx + dy * dy);
    }

    T dist_sq(const pt &a, const pt &b) {
        const T dx = std::abs(a[0] - b[0]);
        const T dy = std::abs(a[1] - b[1]);
        return dx * dx + dy * dy;
    }

    T eval(const linear &a, const T &x) {
        return a[0] * x + a[1];
    } 

    pt intersect(const linear &a, const linear &b) {
        const auto &[m1, b1] = a;
        const auto &[m2, b2] = b;
        const T x = (b2 - b1) / (m1 - m2);
        return {x, eval(a, x)};
    }

    linear make_linear(const pt &loc, const T slope) {
        return {slope, loc[1] - slope * loc[0]};
    }

    linear make_linear(const pt &a, const pt &b) {
        const T slope = (b[1] - a[1]) / (b[0] - a[0]);
        return make_linear(a, slope);
    }

    linear make_linear(const line &l) {
        const auto [a, b] = l;
        return make_linear(a, (b[1] - a[1]) / (b[0] - a[0]));
    }

    T point_to_linear(const pt &p, const linear &l) {
        const auto [m, b] = l;
        T num = std::abs(m * p[0] - p[1] + b);
        T den = std::sqrt(m * m + 1);
        return num / den;
    }

    T polygon_area(const std::vector<pt> &locs) {
        const int n = locs.size();

        T res = 0;
        for (int i = 0; i < n; i++) {
            const auto &[x1, y1] = locs[i];
            const auto &[x2, y2] = locs[(i + 1) % n];
            res += x1 * y2 - y1 * x2;
        }

        return std::abs(res) / 2;
    }

    std::vector<pt> convex_hull(std::vector<pt> locs) {
        std::sort(std::begin(locs), std::end(locs));
        locs.erase(std::unique(std::begin(locs), std::end(locs)), std::end(locs));

        const int n = locs.size();
        if (n < 2) { return locs; }

        std::vector<pt> hull;
        for (int i = 0; i < n; i++) {
            while (hull.size() > 1 && 
                   cross(hull.back() - hull[hull.size() - 2], locs[i] - hull.back()) <= 0) {
                hull.pop_back();
            }
            
            hull.push_back(locs[i]);
        }

        const int lower_hull_len = hull.size();
        for (int i = n - 2; i >= 0; i--) {
            while (hull.size() > lower_hull_len && 
                   cross(hull.back() - hull[hull.size() - 2], locs[i] - hull.back()) <= 0) {
                hull.pop_back();
            }

            hull.push_back(locs[i]);
        }

        hull.pop_back();
        return hull;
    }

    std::vector<pt> lower_hull(std::vector<pt> locs) {
        std::sort(std::begin(locs), std::end(locs));
        locs.erase(std::unique(std::begin(locs), std::end(locs)), std::end(locs));

        const int n = locs.size();
        if (n < 2) { return locs; }

        std::vector<pt> hull;
        for (int i = 0; i < n; i++) {
            while (hull.size() > 1 && 
                   cross(hull.back() - hull[hull.size() - 2], locs[i] - hull.back()) <= 0) {
                hull.pop_back();
            }
            
            hull.push_back(locs[i]);
        }

        return hull;
    }
};