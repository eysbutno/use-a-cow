#include <bits/stdc++.h>
using namespace std;

const int MAX = 501;
vector<int> adj[MAX];
int gifts[MAX][MAX];
bool con[MAX][MAX];
void dfs(int node, int start) {
    if (con[start][node]) return;
    con[start][node] = 1;
    for (int i : adj[node]) {
        dfs(i, start);
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> gifts[i][j];
        }
        bool before = false;
        for (int j = n; j > 0; j--) {
            before |= gifts[i][j] == i;
            if (before) adj[i].push_back(gifts[i][j]);
        }
    }
    for (int i = 1; i <= n; i++) dfs(i, i);
    vector<int> ans(n + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int gift = gifts[i][j];
            if (con[gift][i] && con[i][gift]) {
                cout << gift << "\n";
                break;
            }
        }
    }
}
/*
Time Complexity: O(N^3)
Create a graph, with edges i -> j only being added
if cow i prefers gift j. Use DFS to find if a cow i
is in a connected component with a gift j. If a cow i
is in the same component as a gift j, and the gift j is in
the same component as a cow i, then you have a cycle, where within 
that cycle the cows can feasibly swap gifts so a cow gets gift j.
Print out the most preferred gift that fulfills the condition above.
*/