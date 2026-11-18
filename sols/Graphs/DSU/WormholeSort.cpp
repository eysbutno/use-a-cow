#include <bits/stdc++.h>
using namespace std;
// explanation at bottom
struct Wormhole {
    int a, b, w;
    bool operator<(const Wormhole &y) {
        return w > y.w;
    }
};
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
void setIO(string name = "") {
    ios_base::sync_with_stdio(0); cin.tie(0);
    if (name.size()) {
       freopen((name + ".in").c_str(), "r", stdin);
       freopen((name + ".out").c_str(), "w", stdout);
    }
}
int main() {
    setIO("wormsort");
    int n, m; cin >> n >> m;
    vector<int> cows(n); bool sorted = 1;
    for (int i = 1; i <= n; i++) {
        cin >> cows[i - 1]; cows[i - 1]--;
        if (cows[i - 1] != i - 1) sorted = 0;
    }
    vector<Wormhole> wh(m);
    for (int i = 0; i < m; i++) {
        int a, b, w; cin >> a >> b >> w;
        wh[i] = {--a, --b, w};
    }
    sort(begin(wh), end(wh));
    if (sorted) {
        cout << -1 << "\n";
        return 0;
    }
    DSU dsu(n); int idx = 0;
    for (int i = 0; i < n; i++) {
        while (dsu.get(cows[i]) != dsu.get(i)) { // clever trick
            dsu.unite(wh[idx].a, wh[idx].b);
            idx++;
        }
    }
    cout << wh[--idx].w << "\n";
}
/*
Type: DSU, Sorting
Algorithm:
Read the input (and check if the cows are already sorted)
Sort the wormholes in descending order.
While the two locations are not in the same location, add a wormhole.
This is guaranteed to never TLE b/c there's always a solution
*/