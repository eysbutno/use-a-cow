#include <bits/stdc++.h>

using ll = long long;

/**
 * https://codeforces.com/blog/entry/111371
 * 
 * Derived from this tutorial. Mildly scuffed.
 * 
 * NOTE: If using split FFT, MUST use long double
 */

using c_t = std::complex<long double>;
using namespace std::complex_literals;

const long double PI = acosl(-1.0L);

/**
 * A TL;DR of DFT, so I don't forget:
 * - A DFT on a polynomial of length m is just evaluating it at each of 
 *   its m-th roots of unity, in circular order of exp(2pi*ij / m)
 * - For convenience, we assume m is a power of 2, since we can just
 *   append 0s and time complexity remains the same
 * - Okay explaining all the matrix operations is way too annoying, just
 *   read the article again. Just note that:
 *   - When reordering rows, we reorder the vector (RHS) values, so that 
 *     our output remains in order
 *   - For the overall LHS matrix, the rule is M[i][j] = w^ij (ij taken mod m)
 *   - For the evens LHS matrix, the rule is M[i][j] = w^2ij (ij taken mod m)
 *     - Note: since w^2 is just skipping over a step, this is why the "blue"
 *       side on their diagram is just another DFT!
 *   - For the odds RHS matrix, the rule is M[i][j] = w^(2ij + i)
 *   - As you can see, the rules for the evens and odds are pretty similar, so
 *     we just do some more matrix fuckery, and it works!
 * 
 * This isn't the standard impl; we use a trick to iterate on the subarrays
 * in order, avoiding a bunch of really expensive recursion.
 */
void dft(std::vector<c_t> &a) {
    const int n = a.size();
    assert((n & (n - 1)) == 0);

    static std::vector<c_t> rt{1, 1};
    while (rt.size() < n) {
        int h = rt.size();
        rt.resize(2 * h);
        for (int k = 0; k < h; k++) {
            rt[h + k] = std::polar(1.0L, PI * k / h);
        }
    }

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) std::swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        const int h = len / 2;
        for (int i = 0; i < n; i += len) {
            for (int k = 0; k < h; k++) {
                c_t u = a[i + k];
                c_t v = rt[h + k] * a[i + k + h];
                a[i + k] = u + v;
                a[i + k + h] = u - v;
            }
        }
    }
}

/**
 * A TL;DR of FFT, so I don't forget:
 * - Basically converting polynomial from coefficient to value (well, point-value) form
 * - Idea is that, by taking DFT of polynomials a and b, we can easily calculate 
 *   the DFT of c = a * b (or discrete convolution of a and b)
 * - Neat part is, DFT sorta undoes itself!
 *   - Precisely: DFT(DFT(a_0, a_1, ..., a_m-1)) = (ma_0, ma_m-1, ..., ma_1)
 * - So we can pretty easily get our coeffients of c by performing DFT on 
 *   the inferred DFT of a * b
 */
std::vector<c_t> conv(std::vector<c_t> a, std::vector<c_t> b) {
    // lol yosupo RTEs me if I don't have this
    if (a.size() == 1 && b.size() == 1) {
        return std::vector<c_t>{a[0] * b[0]};
    }

    // must be power of 2, for implementation convenience
    const int sz = 2 << std::__lg(a.size() + b.size() - 2);
    const int res_sz = a.size() + b.size() - 1;
    a.resize(sz);
    b.resize(sz);
    dft(a);
    dft(b);
    std::vector<c_t> c(sz);
    for (int i = 0; i < sz; i++) {
        c[i] = a[i] * b[i];
    }

    dft(c);
    std::reverse(c.begin() + 1, c.end());
    for (c_t &i : c) i /= (long double) sz;

    c.resize(res_sz);
    return c;
}

template <int M> std::vector<int> conv_mod(const std::vector<int>& a, const std::vector<int>& b) {
    const int n = a.size();
    const int m = b.size();
    const int sz = n + m - 1;
    std::vector<c_t> lo_a(n), hi_a(n), lo_b(m), hi_b(m);
    for (int i = 0; i < n; i++) {
        lo_a[i] = a[i] & ((1 << 15) - 1);
        hi_a[i] = a[i] >> 15;
    }
    for (int i = 0; i < m; i++) {
        lo_b[i] = b[i] & ((1 << 15) - 1);
        hi_b[i] = b[i] >> 15;
    }

    auto c_ll = conv(lo_a, lo_b);
    auto c_lh = conv(lo_a, hi_b);
    auto c_hl = conv(hi_a, lo_b);
    auto c_hh = conv(hi_a, hi_b);

    const ll m15 = (1 << 15) % M;
    const ll m30 = (1ll << 30) % M;
    std::vector<int> res(sz);
    for (int i = 0; i < sz; i++) {
        ll v_ll = (ll) std::llround(c_ll[i].real()) % M;
        ll v_mid = (std::llround(c_lh[i].real()) + std::llround(c_hl[i].real())) % M;
        ll v_hh = (ll) std::llround(c_hh[i].real()) % M;
        res[i] = (v_ll + v_mid * m15 + v_hh * m30) % M;
    }

    return res;
}