#include <bits/stdc++.h>
using namespace std;
#define f first 
#define s second

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int c, n; cin >> c >> n;
    vector<int> teams(n), edits(1 << c, INT_MAX);
    for (int i = 0; i < n; i++) {
        string t; cin >> t;
        for (int j = 0; j < c; j++) {
            if (t[j] == 'G') {
                teams[i] += 1 << (c - j - 1);
            }
        }
    }
    queue<pair<int, int>> q;
    for (int i : teams) {
        q.push({i, 0});
    }
    while (!q.empty()) {
        auto p = q.front(); q.pop(); 
        if (edits[p.f] != INT_MAX) continue;
        edits[p.f] = p.s; 
        for (int bit = 0; bit < c; bit++) {
            q.push({p.f ^ (1 << bit), p.s + 1});
        }
    }
    for (int i : teams) {
        int inv = i ^ ((1 << c) - 1);
        cout << c - edits[inv] << '\n';
    }
}