#include <bits/stdc++.h>
using namespace std; 
using pii = pair<int, int>;
#define pb push_back
#define f first 
#define s second 

int pows[10];
int main() {
    vector<pii> edges = {
        {0, 1}, {0, 3}, {1, 4},
        {1, 2}, {2, 5}, {3, 4},
        {3, 6}, {4, 7}, {4, 5},
        {5, 8}, {6, 7}, {7, 8}
    };
    pows[0] = 1;
    for (int i = 1; i <= 9; i++) {
        pows[i] = pows[i - 1] * 9;
    }
    int res = 0;
    for (int i = 0; i < 9; i++) {
        res += i * pows[i];
    }
    int st = 0;
    for (int i = 0; i < 9; i++) {
        int num; cin >> num; --num;
        st += num * pows[i];
    }
    unordered_map<int, int> seen;
    queue<int> q;
    q.push(st);
    seen[st] = 0;
    auto swap = [&](int grid, int i, int j) {
        int f = (grid % pows[i + 1]) / pows[i], 
            s = (grid % pows[j + 1]) / pows[j];
        grid += pows[i] * (s - f);
        grid += pows[j] * (f - s);
        return grid;
    };
    auto process = [&](int node) {
        for (auto& i : edges) {
            int nxt = swap(node, i.f, i.s);
            if (!seen.count(nxt) || seen[node]
                + 1 < seen[nxt]) {
                seen[nxt] = seen[node] + 1;
                q.push(nxt);
            }
        }
    };
    while (size(q)) {
        int p = q.front(); q.pop();
        if (p == res) {
            cout << seen[res];
            return 0;
        }
        process(p);
    }
}
/*
Observation 1: There are only 9! states.
Reason: If the grid is laid out flat, you 
can only arrange the numbers in 9! ways.

Observation 2: You can store a grid as an
integer.
Reason: 0 * 9 ^ 0 + 1 * 9 ^ 1... + 8 * 9 ^ 8
is less than 2 ^ 31 - 1.

Observation 3: You can simply brute force all
the states using BFS.
Reason: Only 9! states and we only visit
a node once, so it's just O(n^2!).

Use an unordered map for improved speed.
*/