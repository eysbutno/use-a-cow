#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f first 
#define s second 

int main() {
    int k; cin >> k;
    vector<int> dist(k, 2e9);
    dist[1] = 1;
    deque<int> q;
    q.push_front(1);
    while (!q.empty()) {
        int p = q.front(); 
        q.pop_front();
        int c1 = (p * 10) % k;
        if (dist[p] < dist[c1]) {
            dist[c1] = dist[p];
            q.push_front(c1);
        }
        int c2 = (p + 1) % k;
        if (dist[p] + 1 < dist[c2]) {
            dist[c2] = dist[p] + 1;
            q.push_back(c2);
        }
    }
    cout << dist[0] << '\n';
}
/*
Time Complexity: O(K)
Algorithm:
Uses 01 BFS to find the shortest
path between 1 (mod k) and 0 (mod k).
The edges are: node i to node (i * 10) % k,
with the cost being 0, and node i to node
(i + 1) % k, with cost being 1. We don't 
actually care about the raw numbers; all
numbers that are congruent to mod k will
share the same edges. 
*/