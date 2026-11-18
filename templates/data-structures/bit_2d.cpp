#include <bits/stdc++.h>

using ll = long long;

template <typename T> class bit_2d {
  private:
    const int n, m;
    std::vector<std::vector<T>> arr;

  public:
    bit_2d(int _n, int _m) : n(_n), m(_m), arr(n + 1, vector<T>(m + 1)) {}
    
    /** adds val to location (r, c) */
    void add(int r, int c, T val) {
        r++, c++;
        for (; r <= n; r += r & -r) {
            for (int i = c; i <= m; i += i & -i) {
                arr[r][i] += val;
            }
        }
    }

    /** @return rectangle sum with corners (0, 0) and (r, c) */
    T rect_sum(int r, int c) {
        r++, c++;
        T sum = 0;
        for (; r > 0; r -= r & -r) {
            for (int i = c; i > 0; i -= i & -i) {
                sum += arr[r][i];
            }
        }
        return sum;
    }

    /** @return rectangle sum with corners (r1, c1) and (r2, c2) */
    T rect_sum(int r1, int c1, int r2, int c2) {
        return rect_sum(r2, c2) - rect_sum(r2, c1 - 1) - 
               rect_sum(r1 - 1, c2) + rect_sum(r1 - 1, c1 - 1);
    }
};
