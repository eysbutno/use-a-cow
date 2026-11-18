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

struct DSU {
    vector<int> e;
    DSU(int n) { e = vector<int>(n, -1); }
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
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n; cin >> n; 
    DSU dsu(n * 2);
    auto isFriend = [&](int x, int y) {
        return dsu.get(x) == dsu.get(y);
    };
    auto isOpp = [&](int x, int y) {
        return (isFriend(x, y + n) || isFriend(y, x + n));
    };
    auto setFriend = [&](int x, int y) {
        if (isOpp(x, y) || isOpp(x + n, y + n)) {
            cout << -1 << '\n';
            return;
        }
        dsu.unite(x, y);
        dsu.unite(x + n, y + n);
    };
    auto setOpp = [&](int x, int y) {
        if (isFriend(x, y) || isFriend(x + n, y + n)) {
            cout << -1 << '\n';
            return;
        }
        dsu.unite(x, y + n);
        dsu.unite(y, x + n);
    };
    while (true) {
        int c, x, y; 
        cin >> c >> x >> y;
        if (!c && !x && !y) {
            break;
        }
        switch (c) {
            case 1:
                setFriend(x, y);
                break;
            case 2:
                setOpp(x, y);
                break;
            case 3:
                cout << isFriend(x, y) << '\n';
                break;
            case 4:
                cout << isOpp(x, y) << '\n';
                break;
        }
    }
}
/**
 * TASK: War (OnlineJudge)
 * 1. If x and y become friends, then
 * all of x's enemies will become y's
 * friends. (Given they are not enemies),
 * and their friends will become friends.
 * All of x's enemies will also become y's enemies.
 * 
 * 2. If x and y become enemies, then x's enemies
 * becomes y's friends, and vice versa.
 * 
 * IMPLEMENTATION: Maintain 1 DSU of size N * 2.
 * For an index i < n, set i stores a group of
 * friends. For an index i >= n, set i stores the
 * enemies of set i - n.
*/