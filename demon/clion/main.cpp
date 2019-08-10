#include<bits/stdc++.h>

#define loca
#define debu
using namespace std;

const int MAXN = 1005;
const int INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
const long long MOD = 1000000007;

long long n, m, T, M;
long long x, y, z;
char buf[MAXN][MAXN];
long long dp[MAXN][MAXN], sm[MAXN][MAXN];

int main() {

#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif // ONLINE_JUDGE

#ifndef ONLINE_JUDGE
    auto start_time = clock();
    cerr << setprecision(3) << fixed;
#endif

//    ios::sync_with_stdio(false);
//    cin>>n>>m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%s", buf[i] + 1);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (buf[i][j] == buf[i - 1][j]) dp[i][j] = dp[i - 1][j] + 1;
            else dp[i][j] = 1;
        }

    long long res = 0;
    for (int i = 3; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            long long k = dp[i][j];
            if (dp[i][j] != dp[i - k][j] || dp[i - 2 * k][j] < k)
                continue;
            sm[i][j] = 1;
            if (dp[i][j - 1] == k && dp[i - k][j - 1] == k && dp[i - 2 * k][j - 1] >= k
                && buf[i][j] == buf[i][j - 1] && buf[i - k][j] == buf[i - k][j - 1] &&
                buf[i - 2 * k][j] == buf[i - 2 * k][j-1]) {
                sm[i][j] += sm[i][j - 1];
            }
            res += sm[i][j];
        }
    }
     cout << res << endl;

#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}

/*
写代码时请注意：
    1.是否要开Long Long？数组边界处理好了么？
    2.实数精度有没有处理？
    3.特殊情况处理好了么？
    4.做一些总比不做好。
思考提醒：
    1.最大值和最小值问题可不可以用二分答案？
    2.有没有贪心策略？否则能不能dp？
*/