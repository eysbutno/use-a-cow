#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define smax(a, b) a = max(a, b)
#define smin(a, b) a = min(a, b)
#define pb push_back
#define ins insert
#define f first 
#define s second 

struct DSU {
    vector<int> e;
    DSU(int n) { 
        e = vector<int>(n, -1); 
    }
    int get(int x) { 
        return e[x] < 0 ? x : e[x] = get(e[x]); 
    }
    bool connected(int a, int b) {
        return get(a) == get(b); 
    }
    int size(int x) { 
        return -e[get(x)]; 
    }
    bool unite(int x, int y) {
        x = get(x), y = get(y);
        if (x == y) return false;
        if (e[x] > e[y]) swap(x, y);
        e[x] += e[y];
        e[y] = x;
        return true;
    }
};
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n, q; 
    cin >> n >> q;
    DSU dsu(n + 1);
    vector<int> nxt(n + 1);
    for (int i = 1; i <= n; i++) {
        nxt[i] = i + 1;
    }
    auto process = [&](int l, int r) {
        int ptr = nxt[l];
        while (ptr <= r) {
            dsu.unite(l, ptr);
            ptr = nxt[ptr];
        }
        while (l <= r) {
            int temp = nxt[l];
            nxt[l] = ptr;
            l = temp;
        }
    };
    while (q--) {
        int t, x, y;
        cin >> t >> x >> y;
        if (t == 1) {
            dsu.unite(x, y);
        } else if (t == 2) {
            process(x, y);
        } else {
            cout << (dsu.connected(x, y) ? 
                "YES" : "NO") << '\n';
        }
    }
}
/**
 * Funny problem. Thanks, Albert.
 * Queries 1 & 3: DSU.
 * Query 2: DSU, but for each range
 * you only care about the next one,
 * so just "jump" through ranges.
 * Pretty clever.
*/