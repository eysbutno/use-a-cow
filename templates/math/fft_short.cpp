#include <bits/stdc++.h>

using ll = long long;
using ld = long double;
using c_t = std::complex<double>;

const ld PI = std::acos(-1.0L);

void dft(std::vector<c_t> &v) {
    if (v.size() == 1) return;
    const int m = v.size();
    static std::vector<c_t> rt{1, 1};
    while (rt.size() < m) {
        int h = rt.size();
        rt.resize(2 * h);
        for (int k = 0; k < h; k++) rt[h + k] = std::polar(1.0L, PI * k / h);
    }

    std::vector<c_t> e, o;
    for (int i = 0; i < m; i++) {
        (i % 2 == 0 ? e : o).push_back(v[i]);
    }

    dft(e), dft(o);
    for (int i = 0; i < m / 2; i++) {
        v[i] = e[i] + rt[i + m / 2] * o[i];
        v[i + m / 2] = e[i] - rt[i + m / 2] * o[i];
    }
}

std::vector<ll> fft(std::vector<int> a, std::vector<int> b) {
    if (a.size() + b.size() == 2) return {1ll * a[0] * b[0]};
    const int sz_r = a.size() + b.size() - 1;
    const int sz = 2 << std::__lg(sz_r - 1);
    std::vector<c_t> a_c(sz), b_c(sz);
    std::copy(a.begin(), a.end(), a_c.begin());
    std::copy(b.begin(), b.end(), b_c.begin());
    for (int i = 0; i < a.size(); i++) a_c[i] = a[i];
    for (int i = 0; i < b.size(); i++) b_c[i] = b[i];
    dft(a_c), dft(b_c);
    for (int i = 0; i < sz; i++) a_c[i] *= b_c[i];
    dft(a_c);
    std::reverse(a_c.begin() + 1, a_c.end());
    std::vector<ll> res(sz_r);
    for (int i = 0; i < sz_r; i++) res[i] = ll(a_c[i].real() / sz + 0.5);
    return res;
}

std::vector<int> conv_mod(const std::vector<int> &a, const std::vector<int> &b, int mod) {
    const int n = a.size(), m = b.size();
    std::vector<int> a_l(n), a_h(n), b_l(m), b_h(m);
    for (int i = 0; i < n; i++) a_l[i] = a[i] & ((1 << 15) - 1), a_h[i] = a[i] >> 15;
    for (int i = 0; i < m; i++) b_l[i] = b[i] & ((1 << 15) - 1), b_h[i] = b[i] >> 15;
    auto c_ll = fft(a_l, b_l), c_lh = fft(a_l, b_h), c_hl = fft(a_h, b_l), c_hh = fft(a_h, b_h);

    std::vector<int> res(n + m - 1);
    const ll m15 = (1 << 15) % mod, m30 = (1 << 30) % mod;
    for (int i = 0; i < res.size(); i++) {
        res[i] = (c_ll[i] % mod + m15 * ((c_lh[i] + c_hl[i]) % mod) + m30 * (c_hh[i] % mod)) % mod;
    }
    
    return res;
}