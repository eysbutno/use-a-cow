#include <bits/stdc++.h>
using namespace std;
#define LL long long
vector<bool> visited; vector<vector<int>> adj; 
vector<int> xVal; vector<int> yVal; int n;
// Gold, 2016 Dec P1
void dfs(int node) {
    visited[node] = true;
    for (int i : adj[node]) {
        if (!visited[i]) dfs(i);
    }
}
bool check(LL x) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            LL dist = pow(abs(xVal[i] - xVal[j]), 2) + 
                pow(abs(yVal[i] - yVal[j]), 2);
            if (dist <= x) {
                adj[i].push_back(j);
            }
        }
    }
    bool flag = false;
    for (int i = 0; i < n; i++) {
        dfs(i); bool temp = true;
        for (int j = 0; j < n; j++) {
            if (!visited[j]) temp = false;
            visited[j] = false;
        }
        if (temp) {flag = true; break;}
    }
    for (int i = 0; i < n; i++) adj[i].clear();
    return flag;
}
int main() {
    ifstream fin ("moocast.in");
    ofstream fout ("moocast.out");
    fin >> n; 
    visited.resize(n); adj.resize(n);
    xVal.resize(n); yVal.resize(n);
    for (int i = 0; i < n; i++) {
        int x, y; fin >> x >> y;
        xVal[i] = x; yVal[i] = y;
    }
    LL low = 0, high = -1;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            LL dist = pow(abs(xVal[i] - xVal[j]), 2) + 
            pow(abs(yVal[i] - yVal[j]), 2);
            high = max(high, dist);
        }
    }
    while (low < high) { // finding lowest true
        LL mid = low + (high - low) / 2;
        if (check(mid)) high = mid;
        else low = mid + 1;
    }
    fout << low << "\n";
    return 0;
}
/*
Binary saerch the value of X, then run DFS
*/