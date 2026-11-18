#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define pb push_back
#define ins insert
#define f first 
#define s second 

template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
template<class T> class FT {
    private:
        int sz; vector<T> pf;
    public:
        FT() {} // so vector<FT<ll>> works
        FT(int n) {
            sz = n + 1, pf.resize(n + 1);
        }
        T bit(int idx) {
            return idx & -idx;
        }
        T prefix(int idx) {
            T tot = 0;
            for (++idx; idx > 0; idx -= bit(idx)) {
                tot += pf[idx];
            }
            return tot;
        }
        T query(int l, int r) {
            return prefix(r) - prefix(l - 1);
        }
        void update(int idx, T dx) {
            for (++idx; idx < sz; idx += bit(idx)) {
                pf[idx] += dx;
            }
        }
};
int main() {
	cin.tie(0) -> sync_with_stdio(0);
	int n; cin >> n;
	vector<int> b(n);
	for (int& i : b) {
		cin >> i;
	}
	FT<int> ft(n);
	vector<int> lst(n, -1);
	ll res = 0;
	for (int i = n - 1; i >= 0; i--) {
		if (lst[b[i]] != -1) {
			res += ft.query(i, lst[b[i]] - 1);
			ft.update(lst[b[i]], -1);
			ft.update(i, 1);
			lst[b[i]] = i;
		} else {
			res += ft.query(i, n - 1);
			ft.update(i, 1);
			lst[b[i]] = i;
		}
	}
	cout << res << '\n';
}
/**
 * TASK: United Cows of Farmer John.
 * Observation 1: If we set an endpoint
 * to be an index i, the only cows that 
 * can be all endpoints where the following are
 * satisfied:
 * A. That endpoint is not identical to this endpoint.
 * B. From i to that endpoint, the second endpoint will
 *    not have any other cows between of the same breed.
 * To solve this, you just use a Fenwick tree.
*/