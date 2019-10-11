#include<bits/stdc++.h>

//#pragma GCC optimize(2)

using namespace std;

const long long MAXN = 150;
const long long PHI = (long long) 998244352;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
const long long MOD = (long long) 1e9 + 7;
const long long OVER_FLOW = 0x7fffffff;
const long long LOVER_FLOW = 0x7fffffffffffffff;

int n;
int dp[10050][MAXN];
int buf[MAXN], tme[MAXN];

long long C[MAXN][MAXN];

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
    1.数学公式尝试化简
    2.dp或者数值太大,尝试给出递推公式
    3.概率题随机生成考虑1/2的情况,或者是满足的方案/所有可能的方案
    5.排序之前不能取模.
    6.0-1子矩阵子序列:前缀和,异或和
    7.模拟题注意代码复用.
    8.单个区间问题考虑前缀和,多个区间左右端点拆开,排序,记录端点极值
思考提醒：
    1.最大值和最小值问题可不可以用二分+贪心？
    2.dp
    3.如果规模小的话还能尝试dfs
    4.如果存在等式.转换关系少可以暴力枚举变量,或者考虑从数据大小入手
    5.离散化+打表
*/

    ios::sync_with_stdio(false);
    cin >> n;

    C[0][0] = C[1][0] = C[1][1] = 1;
    for (register int i = 2; i <= 100; ++i) {
        C[i][0] = 1;
        for (register int j = 1; j <= i; ++j)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
    }


    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        int u;
        cin >> u;
        buf[i] = u;
        for (int j = 10000; j >= u; j--) {
            for (int k = 1; k <= 100; k++) {
                dp[j][k] += dp[j - u][k - 1];
            }
        }
    }

//    sort(buf + 1, buf + 1 + n);
    for (int i = 1; i <= n; i++) tme[buf[i]]++;

    long long cnt = 0;
    for (long long i = 1; i <= 100; i++) if (tme[i]) cnt++;
    if (cnt == 1 or cnt == 2) {
        cout << n << endl;
    } else {
        int res = 0;
        for (int i = 1; i <= 100; i++) {
            for (int j = tme[i]; j >= 1; j--) {
                if (dp[j * i][j] == C[tme[i]][j]) {
                    res = max(res, j);
                }
            }
        }
        cout << res << endl;
    }


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}