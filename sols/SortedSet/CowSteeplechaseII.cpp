#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define f first 
#define s second 

struct Segment {
    ll x1, y1, x2, y2, id;
    bool operator<(Segment y) const {
        return x2 > y.x2;
    }
};
int sign(ll x) {
    if (x == 0) return 0;
    return (x < 0) ? -1 : 1;
}
int operator*(pll p1, pll p2) {
    return sign(p1.f * p2.s - p1.s * p2.f);
}
pll operator-(pll p1, pll p2) {
    return make_pair(p1.f - p2.f, p1.s - p2.s);
}
bool intersects(Segment& a, Segment& b) {
    pii p1 = {a.x1, a.y1}, q1 = {a.x2, a.y2},
        p2 = {b.x1, b.y1}, q2 = {b.x2, b.y2};
    return ((q2 - p1) * (q1 - p1)) * ((q1 - p1) * (p2 - p1)) >= 0 &&
	        ((q1 - p2) * (q2 - p2)) * ((q2 - p2) * (p1 - p2)) >= 0;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    freopen("cowjump.in", "r", stdin);
    freopen("cowjump.out", "w", stdout);
    int n; cin >> n;
    vector<Segment> seg(n);
    vector<pair<ll, pii>> EOIs;
    for (int i = 0; i < n; i++) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 > x2) {
            swap(x1, x2);
            swap(y1, y2);
        }
        seg[i] = {x1, y1, x2, y2, i};
        EOIs.push_back({x1, {i, 1}});
        EOIs.push_back({x2 + 1, {i, 0}});
    }
    sort(begin(EOIs), end(EOIs), 
        [&](auto& x, auto& y) {
        if (x.f == y.f) {
            return x.s.s > y.s.s;
        }
        return x.f < y.f;
    });
    set<Segment> active;
    vector<int> counts(n);
    int intersections = 0;
    for (auto i : EOIs) {
        int idx = i.s.f, type = i.s.s;
        if (type == 1) {
            active.insert(seg[idx]);
        } else {
            for (Segment i : active) {
                if (i.x2 < seg[idx].x1) {
                    break;
                }
                if (intersects(i, seg[idx])
                    && i.id != idx) {
                    counts[i.id]++;
                    counts[idx]++;
                    ++intersections;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (counts[i] == intersections) {
            cout << i + 1 << '\n';
            return 0;
        }
    }
}
/*
Coordinate geo stuff: I ripped it off
from CPH/USACO Guide
Algorithm: Use line sweep to solve it.
Keep an "active" set of all the previous
segments, sorted by x2 value. Test
all the segments with x2 >= x1.
*/