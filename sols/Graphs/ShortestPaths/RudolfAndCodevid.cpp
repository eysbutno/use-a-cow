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
const int INF = 1e9;
int toMask(string s) {
    int res = 0;
    for (int i = 0; i < s.length(); i++) {
        res |= (s[i] - '0') << i;
    }
    return res;
}
void solve() {
    int n, m; cin >> n >> m;
    string s; cin >> s;
    vector<array<int, 3>> meds(m);
    for (int i = 0; i < m; i++) {
        int days; cin >> days;
        string s1, s2; cin >> s1 >> s2;
        meds[i] = {toMask(s1), toMask(s2), days};
    }
    vector<int> dist(1 << n, INF);
    dist[toMask(s)] = 0;
    priority_queue<pii> pq;
    pq.push({0, toMask(s)});
    while (!pq.empty()) {
        auto [t, u] = pq.top(); pq.pop();
        if (-t != dist[u]) continue;
        for (auto [f, s, d] : meds) {
            int nxt = u;
            for (int i = 0; i < n; i++) {
                if ((nxt >> i & 1) && (f >> i & 1)) {
                    nxt ^= 1 << i;
                }
                if (!(nxt >> i & 1) && (s >> i & 1)) {
                    nxt |= 1 << i;
                }
            }
            if (smin(dist[nxt], d - t)) {
                pq.push({-dist[nxt], nxt});
            }
        }
    }
    cout << (dist[0] != INF ? dist[0] : -1) << '\n';
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t; cin >> t;
    while (t--) solve();
}
/**
 * TASK: Rudolf and CodeVid-23.
 * Seems like a bitmask/SP problem. 
 * Rudolf can only take one medicine at a time,
 * so this makes it easy.
*/