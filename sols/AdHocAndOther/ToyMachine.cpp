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

int main() {
    int n, k; cin >> n >> k;
    if (k <= (n - 1) / 2) {
        for (int i = 1; i < k; i++) {
            cout << "LDRU";
        }
        cout << "L\n";
    } else {
        while (k + 2 < n){
            cout << "RDLU";
            ++k;
        }
        cout << "R";
        for (int i = n / 2; i; i--){
            cout << "RDRU";
        }
        cout << "LUL";
        for (int i = (n - 2) / 2; i > 0; i--){
            cout << "DRUL";
        }
        cout << "\n";
    }
}
/**
 * TASK: Toy Machine (CF).
 * OK, this is a bit of a casework bash.
 * 
 * Case 1: 1 <= k <= (n - 1) / 2.
 * Do LDRU k - 1 times, then L.
 * 
 * Case 2: (n - 1) / 2 < k <= n - 2.
 * Repeat RDLU a few times, RDRU, then DRUL a few times.
*/