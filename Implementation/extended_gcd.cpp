#include <bits/stdc++.h>

using ll = long long;

/**
 * Solves the equation ax + by = gcd(a, b).
 * Returns {gcd(a, b), x, y}.
 * 
 * Stolen from Brian again.
 */
template <typename T> 
std::array<T, 3> extended_gcd(T m, T n) {
    T a = 1, a_in = 0, b = 0, b_in = 1;
    while (n) {
        const T q = m / n;
        a_in = std::exchange(a, a_in) - q * a_in;
        b_in = std::exchange(b, b_in) - q * b_in;
        n = std::exchange(m, n) - q * n;
    }
    return std::array<T, 3>({m, a, b});
}