#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define pb push_back
#define ins insert
#define f first 
#define s second 

const int MAX = 2e5 + 1;
vector<int> adj[MAX];
ll cnt[MAX], sum[MAX], res[MAX], n;
void dfs(int node, int prev) {
    cnt[node] = 1;
    for (int i : adj[node]) {
        if (i != prev) {
            dfs(i, node);
            cnt[node] += cnt[i];
            sum[node] += sum[i];
        }
    }
    sum[node] += cnt[node];
}
void dfs2(int node, int prev) {
    for (int i : adj[node]) {
        if (i == prev) continue;
        res[i] = res[node] + n 
            - 2 * cnt[i];
        dfs2(i, node);
    }
}
int main() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        int x, y; cin >> x >> y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    dfs(1, -1);
    res[1] = sum[1];
    dfs2(1, -1);
    cout << *max_element(res, res + n + 1);
}
/**
 * If you start at a given root,
 * the sum will always be the same.
 * The problem is figuring out how
 * to reroot in O(N).
 * 
 * Rerooting formula:
 * res[cur] = res[prev] + n - 2 * cnt[cur]
 * Reasoning:
 * You need to subtract cnt[cur] twice
 * if you start at node cur. The reason is 
 * because res[node]'s sum already has 
 * cnt[cur], and by rerooting it you
 * won't have that added to your sum.
 * The +n is because when you start
 * at a node, you get all of the 
 * nodes added to the sum.
*/