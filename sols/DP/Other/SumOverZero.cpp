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
        ST() {} // for empty init
        void set(int idx, T val) {
            idx += len;
            t[idx] = val;
            for (; idx > 1; idx /= 2) {
                t[idx / 2] = max(t[idx], t[idx ^ 1]);
            }
        }
        T query(int l, int r) { // on [l, r)
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
    map<ll, int> mp;
    vector<int> a(n);
    ll pref = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i], pref += a[i], mp[pref] = 0;
    }
    mp[0] = 0; // can make 0
    int ptr = 0;
    for (auto &[k, v] : mp) {
        v = ++ptr;
    }
    vector<ll> dp(n);
    ST<ll> rmq(ptr + 2);
    rmq.set(mp[0], 1);
    pref = 0;
    for (int i = 0; i < n; i++) {
        if (i > 0) dp[i] = dp[i - 1];
        pref += a[i];
        int pos = mp[pref];
        smax(dp[i], i + rmq.query(0, pos + 1));
        if (dp[i] - i > rmq.get(pos)) {
            rmq.set(pos, dp[i] - i);
        }
    }
    cout << dp[n - 1] << '\n';
    return 0;
}
/**
 * RMQ + DP bash. Uses SOME math to 
 * RMQ the best answer in the DP state
 * transition. Pretty nice problem.
*/