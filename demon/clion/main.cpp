#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 1050;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = (long long) 998244353;
const long long OVER_FLOW = 0xffffffff;

long long n;
long long a[MAXN], f[MAXN][MAXN], res[100050], s[MAXN][MAXN];

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
    5.离散化+打表
*/

    ios::sync_with_stdio(false);
    long long k;
    cin >> n >> k;
    for (long long i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + 1 + n);
    a[0] = -INF;
    long long ans = 0;
    for (long long v = 1; v * (k - 1) <= a[n]; v++) {
        f[0][0] = 1;
        long long now = 0;
        s[0][0] = 1;
        for (long long i = 1; i <= n; i++) {
            while (a[now] <= a[i] - v) now++;
            for (long long j = 0; j <= k; j++) {
                if (j) f[i][j] = s[now - 1][j - 1];
                s[i][j] = (s[i - 1][j] + f[i][j]) % MOD;
            }
            res[v] += f[i][k];
        }
        ans += res[v] % MOD;
    }
    cout << ans % MOD << endl;


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}