#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin ("hps.in");
    ofstream fout ("hps.out");
    int n; fin >> n;
    vector<int> h(n + 1); vector<int> p(n + 1); 
    vector<int> s(n + 1); vector<int> ph(n + 1); 
    vector<int> pp(n + 1); vector<int> ps(n + 1);
    for (int i = 1; i <= n; i++) {
        char a; fin >> a;
        if (a == 'H') h[i]++;
        else if (a == 'P') p[i]++;
        else s[i]++;
    }
    for (int i = 1; i <= n; i++) {
        ph[i] = ph[i - 1] + h[i]; 
        pp[i] = pp[i - 1] + p[i]; 
        ps[i] = ps[i - 1] + s[i];
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) { // where Bessie changes
        int temp = max(max(ph[i], pp[i]), ps[i]);
        int temp2 = max(max(ph[n] - ph[i], pp[n] - pp[i]), ps[n] - ps[i]);
        ans = max(temp + temp2, ans);
    }
    fout << ans << endl;
    return 0;
}