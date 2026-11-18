#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n, m, k; cin >> n >> m >> k;
    map<string, int> mp;
    vector<string> pat(n);
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        pat[i] = s, mp[s] = i;
    }
    vector<vector<int>> adj(n);
    vector<int> deg(n);
    for (int i = 0; i < m; i++) {
        string s; cin >> s;
        int mt; cin >> mt; --mt;
        bool okay = false;
        for (int j = 0; j < (1 << k); j++) {
            string cpy = s;
            for (int k = 0; k < 4; k++) {
                if ((j >> k) & 1) cpy[k] = '_';
            }
            if (pat[mt] == cpy) {
                okay = true;
            }
            if (mp.count(cpy) && mp[cpy] != mt) {
                adj[mt].push_back(mp[cpy]);
                ++deg[mp[cpy]];
            }
        }
        if (!okay) {
            cout << "NO" << "\n";
            return 0;
        }
    }
    stack<int> q;
    for (int i = 0; i < n; i++) {
        if (!deg[i]) q.push(i);
    }
    vector<int> topsort;
    while (!q.empty()) {
        int u = q.top(); q.pop();
        topsort.push_back(u);
        for (int i : adj[u]) {
            if (--deg[i] == 0) {
                q.push(i);
            }
        }
    }
    if (size(topsort) < n) {
        cout << "NO" << "\n";
        return 0;
    }
    cout << "YES" << "\n";
    for (int i : topsort) {
        cout << i + 1 << ' ';
    }
    return 0;
}
/**
 * TASK: Pattern Matching (CF).
 * For each string, you can use bitmasks
 * to quickly find all the patterns that
 * are a match.
 * 
 * Interpret the question as a graph. Basically,
 * draw an edge between mt_j and all the possible
 * matching indices. If you can toposort it, then
 * print out the toposort.
 * 
 * NOTE: You first need to establish that for each
 * string, there exists a matching pattern at mt_j.
 * If there isn't one, then it can't work.
 * Why? IDK! This problem statement sucks!
 * (Actually tilting right now...)
*/