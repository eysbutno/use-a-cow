#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = array<int, 2>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int &i : a) {
        cin >> i;
    }
    multiset<int> left, right;
    auto add = [&](int v) -> void {
        if ((left.empty() && (right.empty() || v < *begin(right))) || 
            (!left.empty() && v <= *rbegin(left))) {
            left.insert(v);
        } else {
            right.insert(v);
        }
    };
    auto fix = [&]() -> void {
        while (sz(left) > (k + 1) / 2) {
            right.insert(*rbegin(left));
            left.erase(prev(end(left)));
        }
        while (sz(right) > k / 2) {
            left.insert(*begin(right));
            right.erase(begin(right));
        }
    };
    for (int i = 0; i < k; i++) {
        add(a[i]), fix();
    }
    cout << *rbegin(left) << " ";
    for (int i = k; i < n; i++) {
        if (a[i - k] <= *rbegin(left)) {
            left.erase(left.find(a[i - k]));
        } else {
            right.erase(right.find(a[i - k]));
        }
        assert(sz(left) + sz(right) == k - 1);
        add(a[i]), fix();
        cout << *rbegin(left) << " \n"[i == n - 1];
    }
}