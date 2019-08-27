#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 20;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
const long long MOD = 998244353;
const long long OVER_FLOW = 0xffffffff;

long long a, b, c, s, T;

long long w[MAXN], len;
long long dp[MAXN][MAXN];

//判断n个数字中非零元素小于等于3的个数
long long dfs(int pos, int limit, int pre) {
    if (pos < 0) return pre <= 3;
    if (pre > 3) return 0;
    if (!limit && dp[pos][pre] != -1) return dp[pos][pre];
    int up = limit ? w[pos] : 9;
    long long res = 0;
    for (int i = 0; i <= up; i++) {
        res += dfs(pos - 1, limit && i == up, pre + (i != 0));
    }
    if (!limit) dp[pos][pre] = res;
    return res;
}

long long solve(long long x) {
    len = 0;
    while (x) {
        w[len++] = x % 10;
        x /= 10;
    }
    return dfs(len - 1, 1, 0);
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
    4.做一些总比不做好.
    5.排序之前不能取模.
    6.0-1子矩阵子序列:前缀和
    7.模拟题注意代码复用.
    8.单个区间问题考虑前缀和.
思考提醒：
    1.最大值和最小值问题可不可以用二分答案？
    2.有没有贪心策略？否则能不能dp？
    3.如果规模小的话还能尝试dfs,如果存在等式.转换关系少可以暴力枚举变量
*/

    ios::sync_with_stdio(false);
    cin >> T;
    memset(dp, -1, sizeof(dp));
    while (T--) {
        long long l, r;
        cin >> l >> r;
        cout << solve(r) - solve(l - 1) << endl;
    }


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}