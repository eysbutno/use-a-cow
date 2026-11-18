#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
#define pb push_back
#define f first 
#define s second 

const int MAX = 5e5 + 1;
vector<int> ind[MAX];
int val[MAX];
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n; cin >> n;
    vector<int> ans;
    int sz = 0;
    auto merge = [&](int x, int y) {
        if (x == y) return;
        if (size(ind[x]) > size(ind[y])) {
            swap(ind[x], ind[y]);
        }
        while (size(ind[x])) {
            ind[y].pb(ind[x].back());
            ind[x].pop_back();
        }
    };
    for (int i = 0; i < n; i++) {
        int t, x, y; 
        cin >> t >> x;
        if (t == 2) {
            cin >> y;
        }
        if (t == 1) {
            ans.pb(sz);
            ind[x].pb(sz);
            ++sz;
        } else {
            merge(x, y);
        }
    }
    for (int i = 0; i < MAX; i++) {
        for (int j : ind[i]) {
            val[j] = i;
        }
    }
    for (int i : ans) {
        cout << val[i] << ' ';
    }
}
/**
 * Small to large merging
 * cheese.
*/