#include <bits/stdc++.h>

using ll = long long;

/**
 * https://codeforces.com/blog/entry/111371
 * 
 * Derived from this tutorial. Mildly scuffed.
 * 
 * Proof of AC: https://judge.yosupo.jp/submission/418040
 * (With Pragmas: https://judge.yosupo.jp/submission/418043)
 */

using c_t = std::complex<double>;
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

    static std::vector<c_t> rt{1.0, 1.0};
    while (rt.size() < n) {
        int h = rt.size();
        rt.resize(2 * h);
        for (int k = 0; k < h; k++) {
            // computed in long double, rounded to double once on store
            rt[h + k] = c_t(std::polar(1.0L, PI * k / h));
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
    for (c_t &i : c) i /= (double) sz;

    c.resize(res_sz);
    return c;
}

/**
 * We observe that:
 * - DFT(a + b) = DFT(a) + DFT(b) 
 * - FFT(a) only has real values as its output
 * 
 * So basically if we pack info into the complex, it will be returned into the 
 * complex once we are done with everything! This gets us down from 12 to 6 DFTs.
 * 
 * For a DFT on integer array x, x[-k] = conj(x[k]) and vice versa (mod size),
 * to do so you just expand it out and utilize the fact that w^-1 = conj(w).
 * 
 * If we pack z[i] = x[i] + iy[i], then Z[i] = X[i] + iY[i].
 * conj(Z[-k]) = conj(X[-k]) + conj(iY[-k]) = X[k] + conj(i)Y[k] = X[k] - iY[k].
 */
template <int M> std::vector<int> conv_mod(const std::vector<int>& a, const std::vector<int>& b) {
    const int n = a.size();
    const int m = b.size();
    int sz = 1;
    while (sz < n + m - 1) sz *= 2;

    // pack a_c[i] = lo_15_a[i] + i * hi_15_a[i]
    std::vector<c_t> a_c(sz);
    for (int i = 0; i < n; i++) {
        a_c[i] = c_t(a[i] & ((1 << 15) - 1), a[i] >> 15);
    }

    // do same thing for b_c
    std::vector<c_t> b_c(sz);
    for (int i = 0; i < m; i++) {
        b_c[i] = c_t(b[i] & ((1 << 15) - 1), b[i] >> 15);
    }

    dft(a_c), dft(b_c);

    std::vector<c_t> sl(sz), sh(sz);
    for (int i = 0; i < sz; i++) {
        int r = -i & (sz - 1); // (sz - i) mod sz
        auto al = (a_c[i] + std::conj(a_c[r])) / 2.0;
        auto bl = (b_c[i] + std::conj(b_c[r])) / 2.0;
        auto ah = (a_c[i] - std::conj(a_c[r])) / 2.0 * -1.0i;
        auto bh = (b_c[i] - std::conj(b_c[r])) / 2.0 * -1.0i;

        sl[i] = al * bl + 1.0i * al * bh;
        sh[i] = ah * bl + 1.0i * ah * bh;
    }

    dft(sl), dft(sh);
    std::reverse(sl.begin() + 1, sl.end());
    std::reverse(sh.begin() + 1, sh.end());

    std::vector<int> res(n + m - 1);
    const ll m15 = (1 << 15) % M, m30 = (1 << 30) % M;
    for (int i = 0; i < res.size(); i++) {
        sl[i] /= sz;
        sh[i] /= sz;
        ll c_ll = std::llround(sl[i].real());
        ll c_lh = std::llround(sl[i].imag());
        ll c_hl = std::llround(sh[i].real());
        ll c_hh = std::llround(sh[i].imag());
        res[i] = (c_ll % M + m15 * ((c_lh + c_hl) % M) + m30 * (c_hh % M)) % M;
    }

    return res;
}