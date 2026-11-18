#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ll n; cin >> n;
    ll low = 1, high = n * n;
    ll req = (n * n + 1) / 2;
    while (low < high) {
        ll mid = (low + high) / 2;
        ll less = 0;
        for (int i = 1; i <= n; i++) {
            less += min(mid / i, n);
        }
        if (less >= req) high = mid;
        else low = mid + 1;
    }
    cout << low << '\n';
}
/*
Algorithm:
Binary Search the number that will be the median.
We know that the number that's the median will have
(n * n + 1) / 2 numbers <= it. In order to calculate 
how many numbers in a row are less than our BS guess,
take note that each row's numbers can be represented by
1, 2, 3, 4..., except multiplied by the row's number.
If we divide the guess by the row number, you'll get the #
of #s less than the binary search guess.
*/