#include <bits/stdc++.h>
using namespace std;

int ask(string query, int a, int b) {
    cout << query << ' ' << a 
        << ' ' << b << '\n';
    cout << flush;
    int resp; cin >> resp;
    return resp;
}
int sum(int a, int b) {
    ++a, ++b;
    int v1 = ask("or", a, b),
        v2 = ask("and", a, b);
    int AND = 2 * (v1 & v2),
        XOR = (v1 | v2) - (v1 & v2);
    return AND + XOR;
}
int main() {
    int n, k; cin >> n >> k;
    int v1 = sum(0, 1), 
        v2 = sum(1, 2),
        v3 = sum(0, 2);
    int b = (v1 + v2 - v3) >> 1;
    vector<int> nums(n);
    nums[0] = v1 - b, nums[1] = b,
        nums[2] = v2 - b;
    for (int i = 3; i < n; i++) {
        nums[i] = sum(1, i) - b;
    }
    sort(begin(nums), end(nums));
    cout << "finish " << nums[k - 1] << '\n';
}
/*
You can get the sum A + B by using
the bit operators AND and OR.
A + B = 2(A & B) + A ^ B
A ^ B = A | B - A & B.
*/