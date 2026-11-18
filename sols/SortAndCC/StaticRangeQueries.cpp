#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f first 
#define s second

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, q; cin >> n >> q;
    vector<pair<pair<int, int>
        , int>> updates(n);
    vector<int> vals;
    for (int i = 0; i < n; i++) {
        int a, b, c; 
        cin >> a >> b >> c;
        updates[i] = {{a, b}, c};
        vals.push_back(a);
        vals.push_back(b);
    }
    vector<pair<int, int>> queries(q);
    for (int i = 0; i < q; i++) {
        int a, b; cin >> a >> b;
        queries[i] = {a, b};
        vals.push_back(a);
        vals.push_back(b);
    }
    sort(begin(vals), end(vals));
    vals.erase(unique(begin(vals), 
        end(vals)), end(vals));
    auto getIdx = [&](int v) {
        return (lower_bound(begin(vals), 
            end(vals), v) - begin(vals) + 1);
    };
    int sz = size(vals);
    // EVERYTHING ONE IDEXED NOW!
    vector<ll> diff(sz + 1);
    for (auto& i : updates) {
        diff[getIdx(i.f.f)] += i.s;
        diff[getIdx(i.f.s)] -= i.s;
    }
    for (int i = 1; i <= sz; i++) {
        diff[i] += diff[i - 1];
    }
    vector<ll> pref(sz + 1);
    // process pref sum
    // NOTE: [) RANGE!
    for (int i = 1; i <= sz; i++) {
        pref[i] = pref[i - 1] + (vals[i] 
            - vals[i - 1]) * diff[i];
    }
    for (auto& i : queries) {
        cout << pref[getIdx(i.s) - 1] - 
            pref[getIdx(i.f) - 1] << '\n';
    }
}
/*
Wowee... I can't implement algorithms!

Implementation Details:
#1: Reading in all the input first, to get
all the unique points. This speeds up our
query time drastically. 

#2: Difference array is 1 indexed because
doing prefix sums is easier that way.

#3: pref[i] represents the sum on [0, val[i]). 
Math behind pref[i] calculation: pref[i - 1]
is the previous prefix, (vals[i] - vals[i - 1])
is the length of the subinterval between the previous
and current prefix, and diff[i] is the sum for this subarray.
diff[i] is one indexed, which is why it's not diff[i - 1].
*/