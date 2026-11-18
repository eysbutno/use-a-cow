#include <bits/stdc++.h>
using namespace std;
#define f first 
#define s second

struct DSU {
	vector<int> e;
	DSU(int N) { 
        e = vector<int>(N, -1); 
    }
	int get(int x) { 
		return e[x] < 0 ? x : e[x] = get(e[x]); 
	}
	bool same_set(int a, int b) {
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
    cin.tie(0) -> sync_with_stdio(false);
    freopen("moop.in", "r", stdin);
    freopen("moop.out", "w", stdout);
    int n; cin >> n;
    vector<pair<pair<int, int>, int>> locs(n);
    for (int i = 0; i < n; i++) {
        cin >> locs[i].f.f >> locs[i].f.s;
        locs[i].s = i;
    }
    sort(begin(locs), end(locs));
    DSU dsu(n); vector<bool> con(n);
    set<pair<int, int>> active;
    for (auto i : locs) {
        for (auto j : active) {
            if (j.f <= i.f.s) {
                dsu.unite(j.s, i.s);
                con[j.s] = 1, con[i.s] = 1;
            } else {
                break;
            }
        }
        active.insert({i.f.s, i.s});
    }
    set<int> roots; int ans = 0;
    for (int i = 0; i < n; i++) {
        if (!con[i]) ans++;
        else if (!roots.count(dsu.get(i))) {
            ans++, roots.insert(dsu.get(i));
        }
    }
    cout << ans << '\n';
}
/*
You can represent this problem with a graph,
with each connected edge being a pair that can interact.
Use a disjoint set to find all the connected components. 
We know that for each distinct connected component, the 
least particles that will be left is one particle.
So, we print the sum of the unconnected particles
and the number of connected components.
*/