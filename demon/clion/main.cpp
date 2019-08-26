#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 200500;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
const long long MOD = 998244353;
const long long OVER_FLOW = 0xffffffff;

int n, a, b, T;
long long dp[MAXN][5];
string str;


int main() {

#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif // ONLINE_JUDGE

#ifndef ONLINE_JUDGE
    auto start_time = clock();
    cerr << setprecision(3) << fixed;
#endif

/*
写代码时请注意：
    1.是否要开Long Long？数组边界处理好了么？
    2.实数精度
    4.做一些总比不做好.
    5.排序之前不能取模.
    6.0-1子矩阵子序列:前缀和
思考提醒：
    1.最大值和最小值问题可不可以用二分答案？
    2.有没有贪心策略？否则能不能dp？
    3.如果规模小的话还能尝试dfs,如果存在等式.转换关系少可以暴力枚举变量
*/

    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> a >> b >> str;
        for (long long i = 0; i <= n; i++) for (long long j = 0; j <= 3; j++) dp[i][j] = LINF;
        dp[0][0] = b;
        for (long long i = 1; i <= n; i++) {
            if (i == n || (str[i] == '0' && str[i - 1] == '0')) {
                dp[i][0] = min(dp[i - 1][1] + b + 2 * a, dp[i - 1][0] + b + a);
            }
            dp[i][1] = min(dp[i - 1][0] + 2 * a + 2 * b, dp[i - 1][1] + a + 2 * b);
        }
        cout << dp[n][0] << endl;
    }


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}