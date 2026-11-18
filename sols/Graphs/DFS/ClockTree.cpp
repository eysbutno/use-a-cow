#include <bits/stdc++.h>
using namespace std;

int dfs(int node, int prev, 
    vector<vector<int>>& adj,
    vector<int>& nums) {
    int sum = nums[node] + 1;
    for (int i : adj[node]) {
        if (i != prev) {
            sum += dfs(i, node, adj, nums);
            sum %= 12;
        }
    }
    return 1 + (12 - sum);
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    freopen("clocktree.in", "r", stdin);
    freopen("clocktree.out", "w", stdout);
    int n; cin >> n;
    vector<int> nums(n + 1);
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> nums[i];
    }
    for (int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int res = 13 - dfs(i, -1, adj, nums);
        res = (res + 11) % 12;
        ans += res <= 1;
    }
    cout << ans << '\n';
}
/*
Algorithm:
Set the root for each tree as a node i.
Set all the clock values to 12
for all the nodes not the root.
If the root node's final value is
12 or 13 (because this algorithm
has you always go back), the room is okay.
*/