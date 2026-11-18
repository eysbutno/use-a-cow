#include <bits/stdc++.h>
using namespace std;

struct Shift {
    int t, id; bool start;
};
bool cmp(Shift a, Shift b) {
    return a.t < b.t;
}
void setIO(string name = "") {
    ios_base::sync_with_stdio(0); cin.tie(0);
    if (name.size()) {
       freopen((name + ".in").c_str(), "r", stdin);
       freopen((name + ".out").c_str(), "w", stdout);
    }
}
int main() {
    setIO("lifeguards");
    int n; cin >> n;
    vector<Shift> shifts;
    for (int i = 0; i < n; i++) {
        int l, r; cin >> l >> r;
        shifts.push_back({l, i, 1});
        shifts.push_back({r, i, 0});
    }
    sort(begin(shifts), end(shifts), cmp);
    vector<int> alone(n);
    set<int> active;
    int prev = 0, tot = 0;
    for (Shift s : shifts) {
        int cur = s.t;
        if (active.size() > 0) {
            tot += cur - prev;
        }
        if (active.size() == 1) {
            alone[*begin(active)] = cur - prev;
        }
        if (s.start) {
            active.insert(s.id);
        } else {
            active.erase(s.id);
        }
        prev = cur;
    }
    int ma = 1e8;
    for (int i : alone) {
        ma = min(ma, i);
    }
    cout << tot - ma << "\n";
}
/*
Type: Sorting, Prefix (kind of)
Algorithm:
Split up each shift as being a start and end
Then, sort everything
Process each "event" (start or end)
If there are active cows at this given time, then increment the total time
(cur - prev works because we sorted it)
If there's only one cow, assign the value of the time the alone cow spent
If the event is the start of a shift, then add the cow
Otherwise, remove the cow
*/