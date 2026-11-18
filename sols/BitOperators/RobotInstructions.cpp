#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define f first 
#define s second

struct hsh {
	size_t operator()(const pair<ll, ll> &p) const {
		return p.f * 239 + p.s;
	}
};
void calcSums(vector<pair<int, int>>& inst, 
    vector<pair<pair<ll, ll>, ll>>& res) {
    int len = inst.size();
    for (ll i = 0; i < 1 << len; i++) {
        ll count = 0, sum1 = 0, sum2 = 0;
        for (ll j = 0; j < len; j++) {
            if (i & (1 << j)) {
                sum1 += inst[j].f;
                sum2 += inst[j].s;
                count++;
            }
        }
        res.push_back({{sum1, sum2}, count});
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n; cin >> n;
    pair<ll, ll> dest; 
    cin >> dest.f >> dest.s;
    vector<pair<int, int>> left(n / 2);
    vector<pair<int, int>> right((n + 1) / 2);
    for (int i = 0; i < n / 2; i++) {
        cin >> left[i].f >> left[i].s;
    }
    for (int i = 0; i < (n + 1) / 2; i++) {
        cin >> right[i].f >> right[i].s;
    }
    vector<pair<pair<ll, ll>, ll>> leftRes, rightRes;
    calcSums(left, leftRes), calcSums(right, rightRes);
    unordered_map<pair<ll, ll>, map<ll, ll>, hsh> half;
    for (auto i : leftRes) {
        half[i.f][i.s]++;
    }
    vector<ll> ans(n + 1);
    for (auto i : rightRes) {
        pair<ll, ll> complement = {dest.f - i.f.f, dest.s - i.f.s};
        auto it = half.find(complement);
        if (it != end(half)) {
            for (auto j : it -> second) {
                ans[i.s + j.f] += j.s;
            }
        }
    }
    for (int i = 1; i <= n; i++) cout << ans[i] << '\n';
}
/*
        for (auto j : half[complement]) {
            ans[i.s + j.f] += j.s;
        }
NOTE TO SELF: DO NOT USE THE ABOVE SNIPPET!
It'll keep on creating map objects, which slows
down the program a lot.

Algorithm:
Divide search space into half. Brute force all the
possibilities for both of the search spaces. 
Merge all the subsets using an unordered map
to get your final answer.
*/