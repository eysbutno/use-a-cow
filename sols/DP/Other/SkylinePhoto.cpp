#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define pb push_back
#define ins insert
#define f first 
#define s second 

template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
template <class T> class ST {
    private:
        const T DEF = -1e18;
        vector<T> t;
        int len;
    public:
        ST(int len) : len(len),
            t(len * 2, DEF) {}
        ST() {} // for empty init (e.g. vector<ST<ll>>)
        void set(int idx, T val) {
            idx += len;
            t[idx] = val;
            for (; idx > 1; idx /= 2) {
                t[idx / 2] = max(t[idx], t[idx ^ 1]);
            }
        }
        T query(int l, int r) { // query on [l, r)
            T res = DEF;
            for (l += len, r += len; l < r; l /= 2, r /= 2) {
                if (l & 1) smax(res, t[l++]);
                if (r & 1) smax(res, t[--r]);
            }
            return res;
        }
        T get(int idx) {
            return query(idx, idx + 1);
        }
};
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int n; cin >> n;
    vector<ll> h(n), b(n);
    for (ll& i : h) cin >> i;
    for (ll& i : b) cin >> i;
    stack<int> stk;
    ST<ll> dp(n + 1);
    dp.set(n, 0);
    for (int i = n - 1; i >= 0; i--) {
        while (!stk.empty() && h[stk.top()] > h[i]) {
            stk.pop();
        }
        int j = stk.empty() ? n : stk.top();
        stk.push(i);
        ll res = -1;
        if (j == n) {
            // guaranteed to be featured.
            res = max(b[i], b[i] + dp.query(i, n + 1));
        } else {
            // case 1: just have it as a single
            res = b[i] + dp.get(i + 1);
            // case 2: have this photo be ignored
            smax(res, dp.get(j));
            // case 3: feature it, with starting seg somewhere
            smax(res, dp.query(i, j) + b[i]);
        }
        dp.set(i, res);
    }
    cout << dp.get(0) << '\n';
}
/**
 * TASK: Skyline Photo (CF).
 * So, basically you need to divide the
 * array into some subarrays.... sounds like
 * DP!
 * 
 * Let dp[i] be the the max beauty for a "division"
 * with an endpoint at i. Find the first point on the
 * range where h[j] < h[i]. This can be done with
 * a monotonic stack.
 * 
 * Now, we assert that every height on the range 
 * [j + 1, i - 1] is less than h[i]. So, we just
 * max RMQ this. 
 * 
 * NOTE: Implementing it backwards is easier.
*/