#include<bits/stdc++.h>

#define loca
#define debu
using namespace std;

const int MAXN = 300005;
const int INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
const long long MOD = 998244353;

long long n, T, m, k;
long long buf[MAXN];
long long dp[MAXN][15];

int main() {

#ifdef local
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif // local

#ifdef local
    auto start_time = clock();
    cerr << setprecision(3) << fixed;
#endif

    ios::sync_with_stdio(false);

    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) cin >> buf[i];
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
            dp[i][j] = -1e10;
    long long res = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (j == 1) dp[i][j] = max(dp[i - 1][m] + buf[i] - k, buf[i] - k);
            else
                dp[i][j] = dp[i - 1][j - 1] + buf[i];
            res = max(res, dp[i][j]);
        }
    }
    cout << res << endl;


#ifdef local
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}