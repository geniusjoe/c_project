#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 55;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = 998244353;
const long long OVER_FLOW = 0xffffffff;

long long n;
long long dp[MAXN][MAXN][MAXN][MAXN];
string str[MAXN];

long long dfs(long long x1, long long y1, long long x2, long long y2) {
    if (dp[x1][y1][x2][y2] != -1) return dp[x1][y1][x2][y2];
    else {
        dp[x1][y1][x2][y2] = max(x2 - x1 + 1, y2 - y1 + 1);
        for (long long i = x1; i < x2; i++) {
            dp[x1][y1][x2][y2] = min(dp[x1][y1][x2][y2], dfs(x1, y1, i, y2) + dfs(i + 1, y1, x2, y2));
        }
        for (long long i = y1; i < y2; i++) {
            dp[x1][y1][x2][y2] = min(dp[x1][y1][x2][y2], dfs(x1, y1, x2, i) + dfs(x1, i + 1, x2, y2));
        }
    }
    return dp[x1][y1][x2][y2];
}


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
    3.下标能从最小值开始就从最小值开始
    5.排序之前不能取模.
    6.0-1子矩阵子序列:前缀和
    7.模拟题注意代码复用.
    8.单个区间问题考虑前缀和,多个区间左右端点拆开,排序,记录端点极值
思考提醒：
    1.最大值和最小值问题可不可以用二分+贪心？
    2.dp
    3.如果规模小的话还能尝试dfs
    4.如果存在等式.转换关系少可以暴力枚举变量,或者考虑从数据大小入手
*/

    ios::sync_with_stdio(false);
    cin >> n;
    memset(dp, -1, sizeof(dp));
    for (long long i = 1; i <= n; i++) {
        cin >> str[i];
        for (long long j = 1; j <= n; j++) {
            if (str[i][j - 1] == '#') dp[i][j][i][j] = 1;
            else dp[i][j][i][j] = 0;
        }
    }
    cout << dfs(1, 1, n, n) << endl;

#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}