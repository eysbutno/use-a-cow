#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f first 
#define s second
    
int main() {
    int n; cin >> n;
    vector<pair<ll, ll>> itvs(n);
    set<ll> unique;
    for (auto& i : itvs) {
        cin >> i.f >> i.s;
        unique.insert(i.f);
        unique.insert(i.s + 1);
    }
    vector<ll> marks(size(unique));
    vector<ll> ref(size(unique));
    int idx = 0;
    for (ll i : unique) {
        ref[idx++] = i;
    }
    auto mark = [&](ll loc, int incr) {
        int idx = lower_bound(begin(ref), 
            end(ref), loc) - begin(ref);
        marks[idx] += incr;
    };
    for (auto& i : itvs) {
        mark(i.f, 1);
        mark(i.s + 1, -1);
    }
    vector<ll> cnt(n + 1);
    ll running = 0;
    for (ll& i : marks) {
        running += i;
        i = running;
    }
    for (int i = 0; i < size(marks) - 1; i++) {
        cnt[marks[i]] += ref[i + 1] - ref[i];
    }
    for (int i = 1; i <= n; i++) {
        cout << cnt[i] << ' ';
    }
}
/*
Algorithm:
Coordinate compress,
prefix sums. Boom.

Note: for unique locations,
you just need to add 1 to
the end index. How did I not 
realize that????
*/