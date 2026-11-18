#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define pb push_back
#define ins insert
#define f first 
#define s second 

const int MAX = 1e5 + 1;
set<int> loc[MAX];
int main() {
    int n; cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        loc[a[i]].ins(i);
    }
    ll ans = n, idx = 1;
    sort(begin(a), end(a));
    for (int i = 1; i <= n; i++) {
        auto it = loc[a[i]].lower_bound(idx);
        if (it == end(loc[a[i]])) {
            ans += n - i + 1;
            it = begin(loc[a[i]]);
        }
        idx = *it;
        loc[a[i]].erase(it);
    }
    cout << ans;
}
/**
 * Can also use a Fenwick tree
 * to do, but it's more annoying 
 * that way.
 * 
 * Read in all the cards and then
 * add their indexes, sort them, etc.
 * 
 * For each card, find its index, 
 * and use lower bound to find the most
 * amount of that card you can get.
 * After that, repeat until all
 * the cards are done.
*/