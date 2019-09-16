#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 400050;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = (long long) 1e9 + 7;
const long long OVER_FLOW = 0xffffffff;

long long n;
vector<long long> edges[MAXN], hsh;
vector<pair<long long, long long>> points;
long long f[MAXN], cnt[MAXN];


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
    cin >> n;
    for (long long i = 1; i <= n; i++) {
        long long u, v;
        cin >> u >> v;
        points.emplace_back(v, u);
        hsh.push_back(u), hsh.push_back(v);
    }
    sort(hsh.begin(), hsh.end());
    auto ip = unique(hsh.begin(), hsh.end());
    hsh.resize(distance(hsh.begin(), ip));
    long long mx = 0;
    for (auto it:points) {
        long long u, v;
        u = lower_bound(hsh.begin(), hsh.end(), it.first) - hsh.begin();
        v = lower_bound(hsh.begin(), hsh.end(), it.second) - hsh.begin();
        edges[u].push_back(v);
        mx = max(mx, u);
    }

    long long res = 0, mn = INF;
    for (long long i = 0; i < hsh.size(); i++) {
        if (i == 0) {
            f[0] = 0, cnt[0] = 1;
        } else if (f[i] > f[i - 1]) {
            f[i] = f[i - 1];
            cnt[i] = cnt[i - 1];
        } else if (f[i] == f[i - 1]) {
            cnt[i] += cnt[i - 1];
            cnt[i] %= MOD;
        }

        for (auto it:edges[i]) {

            long long cur = f[i] + hsh[i];
            if (it > mx && cur == mn) {
                res += cnt[i];
                res %= MOD;
            } else if (it > mx && cur < mn) {
                res = cnt[i];
                mn = cur;
            }
            if (f[it] == cur - hsh[it]) {
                cnt[it] += cnt[i];
                cnt[it] %= MOD;
            } else if (f[it] > cur - hsh[it]) {
                f[it] = cur - hsh[it];
                cnt[it] = cnt[i];
            }
        }
    }

    cout << res << endl;


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}