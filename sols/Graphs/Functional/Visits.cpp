#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> funct, moos;
vector<vector<int>> rev;
vector<bool> vis;
void dfs(int node) {
    vis[node] = 1;
    for (int i : rev[node]) {
        if (!vis[i]) dfs(i);
    }
}
int skip(int node) {
    int t = funct[node];
    int h = funct[funct[node]];
    while (t != h) {
        t = funct[t];
        h = funct[funct[h]];
    }
    int least = moos[t];
    t = funct[t];
    while (t != h) {
        least = min(least, moos[t]);
        t = funct[t];
    }
    dfs(t);
    return least;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin >> n;
    funct.resize(n), moos.resize(n);
    rev.resize(n), vis.resize(n);
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> funct[i] >> moos[i]; ans += moos[i];
        funct[i]--; rev[funct[i]].push_back(i);
    }
    for (int i = 0; i < n; i++) {
        if (!vis[i]) ans -= skip(i);
    }
    cout << ans << "\n";
}