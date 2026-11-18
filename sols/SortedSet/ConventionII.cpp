#include <bits/stdc++.h>
using namespace std;
#define f first 
#define s second 

struct Cow {
    int id, a, t;
    bool operator<(const Cow& y) const {
        return id > y.id;
    }
};
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    freopen("convention2.in", "r", stdin);
    freopen("convention2.out", "w", stdout);
    int n; cin >> n;
    vector<Cow> cows(n);
    for (int i = 0; i < n; i++) {
        int a, t; cin >> a >> t;
        cows[i] = {i, a, t};
    }
    sort(begin(cows), end(cows),
        [&](auto& x, auto& y) {
        return x.a < y.a;
    });
    priority_queue<Cow> pq;
    int idx = 0, time = 0, ans = 0;
    while (idx < n || !pq.empty()) {
        if (idx < n && cows[idx].a <= time) {
            pq.push(cows[idx]);
            ++idx;
        } else if (pq.empty()) {
            time = cows[idx].a + cows[idx].t;
            ++idx;
        } else {
            Cow c = pq.top(); pq.pop();
            ans = max(ans, time - c.a);
            time += c.t;
        }
    }
    cout << ans << '\n';
}
/*
For some reason I could not figure this 
out on my own.... ouchies!!

We essentially simulate every possible
state change. There are only 3 possible
state changes: we either add a new
cow to the queue, process a cow who's reached
it's time to eat the grass, or just quickly
process a cow arriving when there's no line.
*/