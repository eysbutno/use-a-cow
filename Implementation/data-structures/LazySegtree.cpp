#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/**
 * Lazy segtree template that is like,
 * generic enough for 90% of stuff... at least,
 * it has been generic enough for every problem I've
 * done lmao.
 * 
 * Range Update: O(log n)
 * Range Query: O(log n)
 * Build: O(n)
 */
template <class Info, class Tag> 
class LazySegtree {
  private:
    const int n;
    std::vector<Info> t;
    std::vector<Tag> lz;
       
    void build(int v, int l, int r, const std::vector<Info> &a) {
        if (l == r) {
            t[v] = a[l];
        } else {
            int m = (l + r) / 2;
            build(2 * v, l, m, a);
            build(2 * v + 1, m + 1, r, a);
            t[v] = t[2 * v] + t[2 * v + 1];
        }
    }

    void apply(int v, int l, int r, const Tag &x) {
        t[v].apply(x, l, r);
        lz[v].apply(x);
    }

    void pushdown(int v, int l, int r) {
        int m = (l + r) / 2;
        apply(2 * v, l, m, lz[v]);
        apply(2 * v + 1, m + 1, r, lz[v]);
        lz[v] = Tag();
    }

    void upd(int v, int l, int r, int ql, int qr, const Tag &x) {
        if (qr < l || ql > r) { return; }
        if (ql <= l && r <= qr) {
            apply(v, l, r, x);
        } else {
            pushdown(v, l, r);
            int m = (l + r) / 2;
            upd(2 * v, l, m, ql, qr, x);
            upd(2 * v + 1, m + 1, r, ql, qr, x);
            t[v] = t[2 * v] + t[2 * v + 1];
        }
    }
    
    Info qry(int v, int l, int r, int ql, int qr) {
        if (qr < l || ql > r) return Info();
        if (l >= ql && r <= qr) return t[v];
        pushdown(v, l, r);
        int m = (l + r) / 2;
        return qry(2 * v, l, m, ql, qr) + qry(2 * v + 1, m + 1, r, ql, qr);
    }

    template <class F>
    int walkleft(int v, int l, int r, Info pref, const F &f) {
        if (l == r) return l;
        pushdown(v, l, r);
        int m = (l + r) / 2;
        Info add = pref + t[2 * v];
        return f(add) ? walkleft(2 * v, l, m, pref, f)
                      : walkleft(2 * v + 1, m + 1, r, add, f);
    }

  public:
    LazySegtree() {}
    
    LazySegtree(int n) : n(n) {
        t.assign(4 << std::__lg(n), Info());
        lz.assign(4 << std::__lg(n), Tag());
    }

    LazySegtree(const std::vector<Info> &a) : n(a.size()) {
        t.assign(4 << std::__lg(n), Info());
        lz.assign(4 << std::__lg(n), Tag());
        build(1, 0, n - 1, a);
    }

    /** updates [ql, qr] with the arbitrary update chosen */
    void upd(int ql, int qr, const Tag &x) {
        upd(1, 0, n - 1, ql, qr, x);
    }

    /** @return result of range query on [ql, qr] */
    Info qry(int ql, int qr) {
        return qry(1, 0, n - 1, ql, qr);
    }

    template <class F>
    int walkleft(const F &f) {
        return walkleft(1, 0, n - 1, Info(), f);
    }
};

struct Tag {
    // lazy tag values
    void apply(const Tag &t) {
        // tag to tag code
        // NOTE: make sure the no update tag is handled correctly
    }
};

struct Info {
    // tree values
    void apply(const Tag &t, int l, int r) {
        // tag to tree value code
        // NOTE: make sure the no update tag is handled correctly
    }
};

/** @return result of joining nodes a and b together */
Info operator+(const Info &a, const Info &b) {

}