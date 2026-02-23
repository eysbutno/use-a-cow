#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/**
 * Sparse segment tree.
 * Update: O(log n)
 * Query: O(log n)
 * Space: O(q log n)
 * 
 * info = tree values
 * tag = lazy updates
 */
template <class info, class tag>
class sparse_segtree {
  private:
    struct node {
        info info;
        tag tag;
        node *left = nullptr;
        node *right = nullptr;
    };
    node *root = new node;
    const int n;

    void apply(node *v, int l, int r, const tag &x) {
        (v -> info).apply(x, l, r);
        (v -> tag).apply(x);
    }

    void pushdown(node *v, int l, int r) {
        if ((v -> left) == nullptr) { (v -> left) = new node; }
        if ((v -> right) == nullptr) { (v -> right) = new node; }
        int m = (l + r) >> 1;
        apply(v -> left, l, m, v -> tag);
        apply(v -> right, m + 1, r, v -> tag);
        (v -> tag) = tag();
    }

    void upd(node *v, int l, int r, int ql, int qr, const tag &x) {
        if (qr < l || ql > r) { return; }
        if (ql <= l && r <= qr) {
            apply(v, l, r, x);
        } else {
            pushdown(v, l, r);
            int m = (l + r) >> 1;
            upd(v -> left, l, m, ql, qr, x);
            upd(v -> right, m + 1, r, ql, qr, x);
            (v -> info) = ((v -> left) -> info) + ((v -> right) -> info);
        }
    }

    info qry(node *v, int l, int r, int ql, int qr) {
        if (qr < l || ql > r) { return info(); }
        if (ql <= l && r <= qr) { return v -> info; }
        pushdown(v, l, r);
        int m = (l + r) >> 1;
        return qry(v -> left, l, m, ql, qr) + qry(v -> right, m + 1, r, ql, qr);
    }

    template<typename F>
    int walk(node *v, int l, int r, const info &pf, const F &f) {
        if (l == r) { return l; }
        pushdown(v, l, r);
        int m = (l + r) >> 1;
        info x = pf + ((v -> left) -> info);
        return f(x) ? walk(v -> left, l, m, pf, f)
                    : walk(v -> right, m + 1, r, x, f);
    }

  public:
    sparse_segtree() {}
    sparse_segtree(int n) : n(n) {}

    void upd(int ql, int qr, const tag &x) {
        upd(root, 0, n - 1, ql, qr, x); 
    }

    info qry(int ql, int qr) {
        return qry(root, 0, n - 1, ql, qr);
    }

    template<typename F>
    int walk(const F &fn) {
        return walk(root, 0, n - 1, info(), fn);
    }
};

struct tag {
    // tag values
    void apply(const tag &t) {
        // make sure tag isn't the default value
    }
};

struct info {
    // tree values
    void apply(const tag &t, int l, int r) {
        // make sure tag isn't the default value
    }
};

/** @return result of joining two tree nodes */
info operator+(const info &a, const info &b) {
    
}