#include <bits/stdc++.h>

#define loc
const int INF = 0x3f3f3f3f;
using namespace std;
const long long MAXN = 1e5 + 5;


long long n;
long long buf[MAXN + 5];

int main() {
    ios::sync_with_stdio(false);

#ifdef local
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif // local

    cin >> n;
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        buf[u]++, buf[v]++;
    }
    bool flag = true;
    for (int i = 1; i <= n; i++)
        if (buf[i] == 2) {
            flag = false;
            break;
        }
    if (flag)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
}