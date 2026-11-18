#include <bits/stdc++.h>
using namespace std;

using ll = long long;

inline namespace Random {
    mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

    template<typename T> T random() {
        T MAX_VAL = numeric_limits<T>::max();
        return uniform_int_distribution<T>(0, MAX_VAL)(rng);
    }

    template<typename T> T random(T bound) {
        return uniform_int_distribution<T>(0, bound)(rng);
    }

    template<typename T> T random(T l, T r) {
        return uniform_int_distribution<T>(l, r)(rng);
    }

    template<typename T> void rand_shuffle(T l, T r) {
        shuffle(l, r, rng);
    }
}

/**
 * Returns a random tree that should be pretty random.
 */
vector<array<int, 2>> gen_tree(int n) {
    vector<array<int, 2>> edges(n - 1);
    vector<int> ord(n);
    iota(begin(ord), end(ord), 0);
    rand_shuffle(begin(ord), end(ord));
    for (int i = 1; i < n; i++) {
        int p = ord[random(i - 1)];
        edges[i - 1] = {min(p, ord[i]), max(p, ord[i])};
    }
    return edges;
}

/**
 * Retrurns a random undirected graph. Note that
 * multiedges and edges that don't connect two nodes
 * aren't allowed.
 */
vector<array<int, 2>> gen_graph(int n, int m) {
    set<array<int, 2>> edges;
    while (edges.size() < m) {
        int a = random(n - 1), b = random(n - 1);
        if (a > b) swap(a, b);
        if (a != b && !edges.count({a, b})) {
            edges.insert({a, b});
        }
    }
    return vector<array<int, 2>>(begin(edges), end(edges));
}

/** 
 * Same as gen_graph, but the graph needs to be connected.
 */
vector<array<int, 2>> gen_con_graph(int n, int m) {
    assert(m >= n - 1);
    auto res = gen_tree(n);
    set<array<int, 2>> added(begin(res), end(res));
    while (added.size() < m) {
        int u = random(n - 1), v = random(n - 1);
        if (u > v) { swap(u, v); }
        if (u != v && !added.count({u, v})) {
            added.insert({u, v});
        }
    }
    return vector<array<int, 2>>(begin(added), end(added));
}

/**
 * Returns a completely random graph with the only restriction being
 * that the graph can't have edges only involving one node.
 */
vector<array<int, 2>> gen_rand_graph(int n, int m) {
    vector<array<int, 2>> res(m);
    for (int i = 0; i < m; i++) {
        do {
            res[i] = {random(n - 1), random(n - 1)};
        } while (res[i][0] == res[i][1]);
    }
    return res;
}

/**
 * Returns a random array with values being on [low, high]
 */
template <typename T> vector<T> gen_arr(int n, T low, T high) {
    int diff = (int) (high - low);
    vector<T> res(n);
    for (int i = 0; i < n; i++) {
        res[i] = random(low, high);
    }
    return res;
}