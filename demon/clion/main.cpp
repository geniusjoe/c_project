#include<bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

#define loca
#define debu

long long dp[2000 + 5][2000 + 5];
int n, m;

int main() {
#ifdef local
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif

//    ios::sync_with_stdio(false);

    while (~scanf("%d%d", &n, &m)) {
        if (n == 0 && m == 0) {
            printf("1\n");
            continue;
        }

        for (int i = 0; i <= n + m; i++) {
            for (int j = 0; j <= n + m; j++)
                dp[i][j] = 0;
        }

//        i为A的个数，j为B的个数

        for (int i = 1; i <= n; i++) dp[i][0] = 1;
        for (int j = 1; j <= m; j++) dp[0][j] = 1;

//      先取AB中的A，此时串必然满足题设
//      再取BA中的A，此时B必然要先出现.
        for (int i = 1; i <= n + m; i++) {
            for (int j = 1; j <= m + n; j++) {
                if (i <= n + j)
                    dp[i][j] += dp[i - 1][j] % MOD;
                if (j <= m + i)
                    dp[i][j] += dp[i][j - 1] % MOD;
                dp[i][j] %= MOD;
            }
        }

        cout << dp[m + n][m + n] << endl;
    }


}