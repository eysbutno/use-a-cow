#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f first 
#define s second

struct EOI {
    ll f; int id; bool s;
    bool operator<(const EOI& y) const {
        return f < y.f;
    }
};
int main() {
    int n; cin >> n;
    vector<EOI> events;
    for (int i = 0; i < n; i++) {
        ll a, b; cin >> a >> b;
        events.push_back({a, i, 1});
        events.push_back({b + 1, i, 0});
    }
    sort(begin(events), end(events));
    ll prev = 0;
    vector<ll> cnt(n + 1);
    multiset<ll> active;
    for (auto& i : events) {
        cnt[size(active)] += i.f - prev;
        if (i.s) active.insert(i.id);
        else active.erase(active.find(i.id));
        prev = i.f;
    }
    for (int i = 1; i <= n; i++) {
        cout << cnt[i] << ' ';
    }
}
/*
Bit of an unconventional 
algorithm. Standard solution
for this problem is to use 
prefix sums + coordinate 
compression, but line sweep
also works (overkill though).
*/