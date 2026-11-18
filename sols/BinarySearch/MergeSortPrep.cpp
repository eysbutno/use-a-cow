#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n; cin >> n;
    vector<int> a(n);
    for (int& i : a) cin >> i;
    vector<vector<int>> ans = {{a[0]}};
    auto search = [&](int val) {
        int l = 0, h = size(ans) - 1;
        while (l < h) {
            int mid = (l + h) / 2;
            if (ans[mid].back() < val) {
                h = mid;
            } else {
                l = mid + 1;
            }
        }
        return l;
    };
    for (int i = 1; i < n; i++) {
        int idx = search(a[i]);
        if (ans[idx].back() < a[i]) ans[idx].push_back(a[i]);
        else ans.push_back({a[i]});
    }
    for (auto& i : ans) {
        for (auto j : i) {
            cout << j << ' ';
        }
        cout << '\n';
    }
}