#include <bits/stdc++.h>
using namespace std;
// using dsu
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
    setIO();
    int n, m; cin >> n >> m;
    vector<int> nums(n);
    vector<int> con(n);
    DSU dsu(n); int ans = 0;
    for (int &i : nums) {
        cin >> i; i--;
    }
    while (m--) {
        int a, b; cin >> a >> b; --a, --b;
        dsu.unite(a, b); con[a] = 1, con[b] = 1;
    }
    for (int i = 0; i < n; i++) {
        if (con[i] && con[nums[i]]) ans += dsu.same_set(i, nums[i]);
        else ans += i == nums[i];
    }
    cout << ans << "\n";
}