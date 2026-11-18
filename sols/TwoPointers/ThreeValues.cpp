#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, x; cin >> n >> x;
    vector<pair<int, int>> vals;
    for (int i = 0; i < n; i++) {
        int a; cin >> a; 
        vals.push_back({a, i + 1});
    }
    sort(begin(vals), end(vals));
    for (int i = 0; i < n - 2; i++) {
        int l = i + 1, r = n - 1; 
        int t = x - vals[i].first;
        while (l < r) {
            int num = vals[l].first + vals[r].first;
            if (num == t) {
                cout << vals[l].second << " " <<
                vals[i].second << " " << vals[r].second;
                return 0;
            } else if (num < t) {
                l++;
            } else {
                r--;
            }
        }
    }
    cout << "IMPOSSIBLE";
    return 0;
}