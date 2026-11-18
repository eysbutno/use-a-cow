#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f first 
#define s second

int nums[1501];
int calc(int n, int cnt, int id) {
    int r = 0, res = 0, cur = 0;
    for (int l = 0; l < n; l++) {
        while (r < n && cur <= cnt) {
            if (nums[r] != id) {
                if (cur == cnt) break;
                ++cur;
            }
            ++r;
        }
        res = max(res, r - l);
        if (nums[l] != id) --cur;
    }
    return res;
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        char c; cin >> c;
        nums[i] = (c - 'a');
    }
    int q; cin >> q;
    while (q--) {
        int cnt; char c;
        cin >> cnt >> c;
        cout << calc(n, cnt, 
            (c - 'a')) << '\n';
    }
}
/*
Algorithm:
Find the largest substring starting at 
a certain index purely made of the 
favorite letter, using as many replacements
until the string ends or there are no
more replacements allowed . Uses two pointers.
*/