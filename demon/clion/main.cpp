#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 1000500;
const long long INF = 0x7f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = 998244853;
const long long OVER_FLOW = 0xffffffff;

long long n, m; /**< n个数,m个操作,以model为模 */
long long res[MAXN];
vector<pair<long long, long long>> in[MAXN], out[MAXN];
multiset<long long> st[MAXN];


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
    long long w;
    cin >> n >> w;
    for (long long i = 1; i <= n; i++) {
        long long len;
        cin >> len;
        long long l = 1, r = w - len + 1;
        in[l].emplace_back(0, i);
        out[r].emplace_back(0, i);

        l = len + 1, r = w + 1;
        in[l].emplace_back(0, i);
        out[r].emplace_back(0, i);

        for (long long j = 1; j <= len; j++) {
            long long u;
            cin >> u;
            l = j, r = j + (w - len) + 1;
            in[l].emplace_back(u, i);
            out[r].emplace_back(u, i);
        }
    }

    for (long long i = 1; i <= w; i++) {
        res[i] = res[i - 1];
        for (auto it:in[i]) {
            if (!st[it.second].empty())
                res[i] -= *st[it.second].rbegin();
            st[it.second].insert(it.first);
            res[i] += *st[it.second].rbegin();
        }

        for (auto it:out[i]) {
            if (!st[it.second].empty())
                res[i] -= *st[it.second].rbegin();
            st[it.second].erase(st[it.second].find(it.first));
            res[i] += *st[it.second].rbegin();
        }
    }

    for (long long i = 1; i <= w; i++) {
        cout << res[i] << " ";
    }
    cout << endl;

#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}