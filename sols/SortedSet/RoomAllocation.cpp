#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define f first 
#define s second 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin >> n;
    vector<pair<pair<int, int>, int>> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i].f.f >> c[i].f.s;
        c[i].s = i;
    }
    sort(begin(c), end(c));
    priority_queue<pair<int, int>> pq;
    vector<int> ans(n);
    pq.push({-c[0].f.s, 1}); ans[c[0].s] = 1;
    for (int i = 1; i < n; i++) {
        auto prev = pq.top();
        if (-prev.f < c[i].f.f) {
            pq.pop(), pq.push({-c[i].f.s, prev.s});
            ans[c[i].s] = prev.s;
        } else {
            pq.push({-c[i].f.s, pq.size() + 1});
            ans[c[i].s] = pq.size();
        }
    }
    cout << pq.size() << "\n";
    for (int i : ans) cout << i << ' ';
}