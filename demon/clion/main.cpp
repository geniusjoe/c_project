#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 200500;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = 998244353;
const long long OVER_FLOW = 0xffffffff;

long long n;
long long lb[MAXN], rb[MAXN];
vector<long long> v[MAXN], buf;
long long dp[MAXN][2];

long long calc(long long y1, long long y2, long long line) {
    return abs(y1 - line) + abs(line - y2);
}

long long dist(long long x1, long long y1, long long x2, long long y2) {
    long long dis_x = abs(x1 - x2);
    long long dis_y = min(min(calc(y1, y2, lb[y1]), calc(y1, y2, lb[y2])),
                          min(calc(y1, y2, rb[y1]), calc(y1, y2, rb[y2])));
    return dis_x + dis_y;
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

//    ios::sync_with_stdio(false);
    long long m, k, q;
    cin >> n >> m >> k >> q;
    for (long long i = 1; i <= k; i++) {
        long long u, x;
        cin >> u >> x;
        v[u].push_back(x);
    }
    for (long long i = 1; i <= q; i++) {
        long long u;
        cin >> u;
        buf.push_back(u);
    }
    for (long long i = 1; i <= n; i++) sort(v[i].begin(), v[i].end());

    buf.push_back(INF), buf.push_back(-INF);
    sort(buf.begin(), buf.end());
    for (long long i = 1; i <= m; i++) {
        rb[i] = buf[lower_bound(buf.begin(), buf.end(), i) - buf.begin()];
        lb[i] = buf[lower_bound(buf.begin(), buf.end(), i) - buf.begin() - 1];
    }

    if (!v[1].empty()) {
        dp[1][1] = dp[1][0] = v[1].back() - 1;
        v[1][0]=v[1].back();
    } else {
        v[1].push_back(1);
        dp[1][1] = dp[1][0] = 0;
    }
    long long lst = 1;
    for (long long i = 2; i <= n; i++) {
        if (!v[i].empty()) {
            long long l_to_l = dp[lst][0] + dist(lst, v[lst].front(), i, v[i].front());
            long long r_to_l = dp[lst][1] + dist(lst, v[lst].back(), i, v[i].front());
            long long l_to_r = dp[lst][0] + dist(lst, v[lst].front(), i, v[i].back());
            long long r_to_r = dp[lst][1] + dist(lst, v[lst].back(), i, v[i].back());
            long long cur = v[i].back() - v[i].front();
            dp[i][0] = min(l_to_r, r_to_r) + cur;
            dp[i][1] = min(l_to_l, r_to_l) + cur;
            lst = i;
        }
    }
    cout << min(dp[lst][0], dp[lst][1]) << endl;


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}