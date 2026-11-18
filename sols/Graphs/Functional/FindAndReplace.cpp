#include <bits/stdc++.h>
using namespace std;
#define f first 
#define s second

int num(char let) {
    if ('a' <= let && let <= 'z') {
        return let - 'a';
    }
    return 26 + (let - 'A');
}
bool dfs(int node, int start, vector<int>& next, 
    vector<int>& vis, vector<int>& in, bool bad) {
    if (node == start && vis[node] && !bad 
        && next[node] != node) {
        return true;
    }
    if (vis[node] || next[node] == -1) return false;
    vis[node] = 1, bad |= in[node] > 1;
    return dfs(next[node], start, next, vis, in, bad);
}
void solve() {
    string a, b; cin >> a >> b;
    int n = a.length();
    vector<int> next(52, -1);
    set<int> chars; bool ok = true;
    for (int i = 0; i < n; i++) {
        int c1 = num(a[i]), c2 = num(b[i]);
        chars.insert(b[i]);
        if (next[c1] != -1 && next[c1] != c2) {
            ok = false;
        }
        next[c1] = c2;
    }
    if (size(chars) == 52) ok = false;
    if (a == b) ok = true;
    if (!ok) {
        cout << -1 << '\n';
        return;
    }
    vector<int> vis(52), in(52);
    int ans = 0;
    for (int i = 0; i < 52; i++) {
        if (next[i] != -1 && next[i] != i) {
            in[next[i]]++;
        } 
    }
    for (int i = 0; i < 52; i++) {
        if (next[i] != -1 && next[i] != i) {
            ans++;
        } 
    }
    for (int i = 0; i < 52; i++) {
        if (!vis[i]) ans += dfs(i, i, next, vis, in, 0);
    }
    cout << ans << '\n';
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}