#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define pb push_back
#define ins insert
#define f first 
#define s second 

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    freopen("swap.in", "r", stdin);
    freopen("swap.out", "w", stdout);
    int n, m, k; cin >> n >> m >> k;
    vector<int> ord(n + 1);
    iota(all(ord), 0);
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        reverse(begin(ord) + a, begin(ord) + b + 1);
    }
    vector<int> sz(n + 1), res(n + 1);
    auto process = [&](int node) {
        int a = node, b = ord[a], size = 1;
        while (a != b) {
            size++; b = ord[b];
        }
        b = ord[b];
        sz[a] = size;
        while (a != b) {
            sz[b] = size;
            b = ord[b];
        }
        for (int i = 0; i < k % size; i++) {
            b = ord[b];
        }
        for (int i = 0; i < size; i++) {
            res[node] = b;
            node = ord[node];
            b = ord[b];
        }
    };
    for (int i = 1; i <= n; i++) {
        if (!sz[i]) process(i);
    }
    for (int i = 1; i <= n; i++) {
        cout << res[i] << '\n';
    }
}
/**
 * Precalculate where each cow at a certain position will go after
 * one iteration of the swapping process. Because each spot has
 * an in and out degree of one, it is a functional graph
 * with a bunch of disjoint cycles. Because it's a cycle,
 * we only need to "simulate" k % (cycle size) iterations
 * of the process. 
*/