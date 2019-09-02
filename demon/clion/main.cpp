#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 200500;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = 998244353;
const long long OVER_FLOW = 0xffffffff;

long long s, T, n, m, M, k, A, B;
long long buf[MAXN];
long long pre_sm[MAXN];

long long dfs(long long l, long long r) {
    long long head = lower_bound(buf + 1, buf + 1 + k, l) - buf;
    long long tail = upper_bound(buf + 1, buf + 1 + k, r) - buf;
    tail--;
    long long len = tail - head + 1;
    if (len == 0) return A;
    long long cur = (r - l + 1) * B * len;
    long long mid = (l + r) >> 1;
    if (l < r)
        cur = min(cur, dfs(l, mid) + dfs(mid + 1, r));
    return cur;

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
    5.排序之前不能取模.
    6.0-1子矩阵子序列:前缀和
    7.模拟题注意代码复用.
    8.单个区间问题考虑前缀和,多个区间左右端点拆开,排序,记录端点极值
思考提醒：
    1.最大值和最小值问题可不可以用二分答案？
    2.有没有贪心策略？否则能不能dp？
    3.如果规模小的话还能尝试dfs,如果存在等式.转换关系少可以暴力枚举变量
*/

    ios::sync_with_stdio(false);
    cin >> n >> k >> A >> B;
    for (long long i = 1; i <= k; i++) cin >> buf[i];
    sort(buf + 1, buf + 1 + k);
    long long ans = dfs(1, (1 << n));
    cout << ans << endl;

#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}