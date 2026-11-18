#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define all(x) begin(x), end(x)
#define ckmin(a, b) a = min(a, b)
#define ckmax(a, b) a = max(a, b)
#define pb push_back 
#define ins insert
#define f first 
#define s second

struct Edge {
    int f, s, w, id;
};
bool operator<(const Edge& x, 
    const Edge& y) {
    return x.w > y.w;
}
struct DSU {
    vector<int> e;
    DSU(int n) { 
        e = vector<int>(n, -1); 
    }
    int get(int x) { 
        return e[x] < 0 ? x : e[x] = get(e[x]); 
    }
    bool con(int a, int b) {
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
    int n, m, k; cin >> n >> m >> k;
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        edges[i] = {x, y, w, i};
    }
    sort(all(edges));
    vector<int> owner(m);
    vector<DSU> child(k + 1, DSU(n + 1));
    for (auto& i : edges) {
        int low = 1, high = k;
        while (low < high) {
            int mid = (low + high) / 2;
            if (!child[mid].con(i.f, i.s)) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        if (!child[low].con(i.f, i.s)) {
            child[low].unite(i.f, i.s);
            owner[i.id] = low;
        }
    }
    for (int i : owner) {
        cout << i << '\n';
    }
}
/**
 * Process each edge, in decreasing
 * order of revenue. Binary search the
 * first child that can take said edge.
 * 
 * Note: The monotonic function is if
 * adding the edge to the mid value's
 * component will make it cyclic. This
 * is monotonic because the previous
 * graph will always have more restrictions
 * than the current one.
*/