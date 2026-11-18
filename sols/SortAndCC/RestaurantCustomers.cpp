#include <bits/stdc++.h>
using namespace std;

struct Event {
    int t, id; bool s;
    bool operator<(const Event &y) {
        return t < y.t;
    }
};
int main() {
    int n; cin >> n;
    vector<Event> t(2 * n);
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        t[i * 2] = {a, i, 1};
        t[i * 2 + 1] = {b, i, 0};
    }
    sort(begin(t), end(t));
    set<int> inside; int ans = 0;
    for (auto i : t) {
        ans = max(ans, (int)inside.size());
        if (i.s) inside.insert(i.id);
        else inside.erase(i.id);
    }
    cout << ans << "\n";
}