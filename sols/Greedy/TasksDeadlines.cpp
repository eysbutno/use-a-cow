#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<pair<int, int>> tasks(n);
    for (int i = 0; i < n; i++) {
        cin >> tasks[i].first >> tasks[i].second;
    }
    sort(begin(tasks), end(tasks));
    long long time = 0; long long ans = 0;
    for (auto i : tasks) {
        time += i.first; ans += i.second - time;
    }
    cout << ans << endl;
    return 0;
}