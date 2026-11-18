#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template<class T> int lis(const vector<T> &a) {
    vector<T> dp;
    for (T i : a) {
	    int pos = lower_bound(begin(dp), end(dp), i) - begin(dp);
        if (pos == dp.size()) { dp.push_back(i); } 
        else { dp[pos] = i; }
    }
    
    return (int) dp.size();
}
