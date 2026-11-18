#include <bits/stdc++.h>
using namespace std;

int add(int a, int b) {
    while (b > 0) {
        int c = a & b;
        a ^= b;
        b = c << 1;
    }
    return a;
}
int mult(int a, int b) {
    int ans = 0;
    while (b > 0) {
        if ((b & 1) == 1) ans = add(ans, a);
        a <<= 1, b >>= 1;
    }
    return ans;
}
int main() {
    cout << mult(69, 69);
}
/**
 * This is so stupid. lmao
*/