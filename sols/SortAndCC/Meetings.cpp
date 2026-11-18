#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f first 
#define s second 

const int MAX = 5e4 + 1;
pair<int, pair<int, int>> locs[MAX];
int getTime(int n, int l, int sum) {
    sort(locs, locs + n);
    vector<int> left, right;
    for (int i = 0; i < n; i++) {
        if (locs[i].s.s == -1) left.push_back(i);
        else right.push_back(i);
    }
    vector<pair<int, int>> col;
    for (int i = 0; i < size(left); i++) {
        int idx = left[i];
        col.push_back({locs[idx].f, locs[i].s.f});
    }
    for (int i = 0; i < size(right); i++) {
        int idx = right[i];
        col.push_back({l - locs[idx].f, 
            locs[size(left) + i].s.f});
    }
    sort(begin(col), end(col));
    int total = 0, idx = 0;
    while (total * 2 < sum) {
        total += col[idx].s;
        ++idx;
    }
    return col[idx - 1].f;
}
int getCount(int n, int t) {
    int cnt = 0;
    queue<int> r;
    for (int i = 0; i < n; i++) {
        if (locs[i].s.s == 1) {
            r.push(locs[i].f);
        } else {
            while (size(r) && r.front() + 
                t * 2 < locs[i].f) {
                r.pop();
            }
            cnt += size(r);
        }
    }
    return cnt;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    freopen("meetings.in", "r", stdin);
    freopen("meetings.out", "w", stdout);
    int n, l; cin >> n >> l;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        int w, x, d; cin >> w >> x >> d;
        locs[i] = {x, {w, d}};
        sum += w;
    }
    int t = getTime(n, l, sum);
    cout << getCount(n, t);
}
/*
Observation 1:
The "meeting" can be observed as 
two cows bouncing off each other.

Observation 2:
The arrival times of a cow will
be x_i if initially going left
and L - x_i if initially going right.

Observation 3:
The nth most cow in one direction 
will take on the edge weight of the
nth most cow overall.

Reasoning:
WLOG, assume there are z cows
going left. That means that z cows
will end up at the leftmost barn.
Crucially, these cows MUST be the 
z leftmost cows, because either these
cows are already going left, or were going
right but got bounced into going left. 
Similar reasoning is applied for if it's
going right.

Observation 4:
For the # of meetings, a cow going left
can meet with a rightside cow if 
r_loc + t * 2 >= l_loc.
*/