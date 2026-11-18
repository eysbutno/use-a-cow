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
    int left = 0; int right = n - 1;
    while (left < right) {
        int num = vals[left].first + vals[right].first;
        if (num == x) {
            cout << vals[left].second << " " << vals[right].second;
            return 0;
        } else if (num > x) {
            right--;
        } else {
            left++;
        }
    }
    cout << "IMPOSSIBLE";
    return 0;
}