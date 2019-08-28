#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 300500;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
const long long MOD = 998244353;
const long long OVER_FLOW = 0xffffffff;

long long c, s, T, n, m, q;
vector<pair<long long, long long>> res;

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
    cin >> n >> m;
    for (long long i = 1; i <= n; i++) {
        for (long long j = i + 1; j <= n; j++) {
            if (__gcd(i, j) == 1) {
                res.emplace_back(i, j);
                if (res.size() == m) {
                    break;
                }
            }
        }
        if (res.size() == m) break;
    }
    if (res.size() == m && m >= n - 1) {
        cout << "Possible" << endl;
        for (auto it:res) {
            cout << it.first << " " << it.second << endl;
        }
    } else if (res.size() < m || m < n - 1) {
        cout << "Impossible" << endl;
    }


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}