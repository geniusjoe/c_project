#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 300005;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
const long long MOD = 998244353;
const long long OVER_FLOW = 0xffffffff;

long long n, x;
long long buf[MAXN];
long long dp[5][MAXN];


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
    2.实数精度有没有处理？
    3.特殊情况处理好了么？
    4.做一些总比不做好.
    5.排序之前不能取模.
思考提醒：
    1.最大值和最小值问题可不可以用二分答案？
    2.有没有贪心策略？否则能不能dp？
    3.如果规模小的话还能尝试dfs
*/

    ios::sync_with_stdio(false);
//    scanf("%I64d", &n);
    cin >> n >> x;
    for (long long i = 1; i <= n; i++) cin >> buf[i];
    long long res = 0;
    for (long long i = 1; i <= n; i++) {
        dp[1][i] = max(dp[1][i - 1], 0ll) + buf[i];
        dp[2][i] = max(max(dp[1][i - 1], 0ll), dp[2][i - 1]) + buf[i] * x;
        dp[3][i] = max(max(dp[2][i - 1], 0ll), dp[3][i - 1]) + buf[i];
    }
    for (long long i = 1; i <= n; i++) {
        res = max(max(max(dp[1][i], dp[2][i]), dp[3][i]), res);
    }
    cout << res << endl;

#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}
