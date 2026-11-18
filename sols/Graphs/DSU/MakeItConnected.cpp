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
struct DSU {
    vector<int> e;
    DSU(int n) { e = vector<int>(n, -1); }
    int size(int x) { return -e[get(x)]; }
    int get(int x) { 
        return e[x] < 0 ? x : e[x] = get(e[x]); 
    }
    bool unite(int x, int y) {
        x = get(x), y = get(y);
        if (x == y) return false;
        if (e[x] > e[y]) swap(x, y);
        e[x] += e[y], e[y] = x;
        return true;
    }
};
void solve() {
    int n; cin >> n;
    DSU dsu(n);
    vector<int> deg(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char c; cin >> c;
            if (c == '1') {
                dsu.unite(i, j);
                ++deg[i], ++deg[j];
            }
        }
    }
    if (dsu.size(0) == n) {
        cout << 0 << '\n';
        return;
    }
    int comp = 0, uncut = -1;
    for (int i = 0; i < n; i++) {
        if ((dsu.size(i) - 1) * 2 != deg[i]) {
            // non-clique component, one operation
            if (uncut == -1) uncut = i;
            else if (deg[uncut] > deg[i]) uncut = i;
        }
        if (dsu.size(i) == 1) {
            // singular node, one operation
            cout << 1 << '\n' << i + 1 << '\n';
            return;
        }
        if (dsu.get(i) == i) {
            ++comp; // a component
        }
    }
    if (uncut != -1) {
        cout << 1 << '\n' << uncut + 1 << '\n';
        return;
    }
    if (comp > 2) {
        cout << 2 << '\n' << 1 << ' ';
        for (int i = 0; i < n; i++) {
            if (dsu.get(i) != 0) {
                cout << i + 1 << '\n';
                return;
            }
        }
    } else {
        int bst = dsu.get(0);
        for (int i = 1; i < n; i++) {
            if (dsu.size(i) < dsu.size(bst)) {
                bst = dsu.get(i);
            }
        }
        cout << dsu.size(bst) << '\n';
        for (int i = 0; i < n; i++) {
            if (dsu.get(i) == bst) {
                cout << i + 1 << ' ';
            }
        }
        cout << '\n';
    }
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}
/**
 * TASK: Make It Connected.
 * Observation 1:
 * If you do the operation on some vertex,
 * it will be connected to every other component,
 * and will be detached from it's current component
 * if it is a clique.
 * 
 * Observation 2:
 * If some node is NOT in a clique, then you can 
 * remove everything in one operation.
 * 
 * If every component is a clique, then we handle
 * it in the following fashion:
 * Case 1: 2 components.
 * You have to operate on each individual clique node.
 * Case 2: > 2 components.
 * Detach any arbitrary node. The component this node
 * will be in after the detachment will no longer be a 
 * clique, so you can detach again.
*/
/**
  * Make observations.
  * Try out various techniques in your head.
  * See if there are some "restrictions" that you
  * can place, to limit it to a set of states. This
  * often makes life a million times easier!
  * Actually do something and don't just stare at
  * the screen....!
  * 
  * Don't give up in contest, you clown!
*/