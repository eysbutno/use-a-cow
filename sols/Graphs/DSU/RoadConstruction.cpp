#include <bits/stdc++.h>
using namespace std;

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
	bool unite(int x, int y) {  // union by size
		x = get(x), y = get(y);
		if (x == y) return false;
		if (e[x] > e[y]) swap(x, y);
		e[x] += e[y];
		e[y] = x;
		return true;
	}
};
int main() {
    int n, m; cin >> n >> m;
    DSU dsu(n); int largest = 0, comps = n;
    while (m--) {
        int a, b; cin >> a >> b; --a, --b;
        if (dsu.unite(a, b)) {
            largest = max(largest, dsu.size(a));
            comps--; 
        }
        cout << comps << " " << largest << "\n";
    }
}
/*
Type: DSU
Algorithm:
Create a disjoint set structure.
For each query, try uniting the two
roads. If they're already connected,
use the current values of largest and comps.
Otherwise, recalculate those values.
*/