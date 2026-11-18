#include <bits/stdc++.h>
using namespace std;
// two pointers version
int main() {
    int n, x; cin >> n >> x;
    vector<int> vals(n);
    for (int i = 0; i < n; i++) {
        cin >> vals[i];
    }
    int left = 0; int right = 0; 
    int prefix = 0; int count = 0;
    while (left < n && right < n) {
        while (right < n) {
            prefix += vals[right++];
            if (prefix > x) {
                prefix -= vals[--right]; 
                break;
            }
        }
        count += prefix == x;
        prefix -= vals[left++];
    }
    cout << count << endl;
    return 0;
}