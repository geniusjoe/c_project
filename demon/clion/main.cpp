#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 2005;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = (long long) 1e9 + 7;
const long long OVER_FLOW = 0xffffffff;


long long s, T, n, m, M, k, A, B, p;
vector<long long> row[MAXN], col[MAXN];
long long buf[MAXN][MAXN];

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
    cin >> n >> m;
    for (long long i = 1; i <= n; i++) {
        for (long long j = 1; j <= m; j++) {
            long long u;
            cin >> u;
            buf[i][j] = u;
            row[i].push_back(u), col[j].push_back(u);
        }
    }
    for (long long i = 1; i <= n; i++) {
        sort(row[i].begin(),row[i].end());
        auto ip=unique(row[i].begin(),row[i].end());
        row[i].resize(distance(row[i].begin(),ip));
    }
    for (long long i = 1; i <= m; i++) {
        sort(col[i].begin(),col[i].end());
        auto ip=unique(col[i].begin(),col[i].end());
        col[i].resize(distance(col[i].begin(),ip));
    }
    for (long long i = 1; i <= n; i++) {
        for (long long j = 1; j <= m; j++) {
            long long l1 = lower_bound(row[i].begin(), row[i].end(), buf[i][j]) - row[i].begin();
            long long r1 = upper_bound(row[i].begin(), row[i].end(), buf[i][j]) - row[i].begin();
            r1 = row[i].size() - r1;
            long long l2 = lower_bound(col[j].begin(), col[j].end(), buf[i][j]) - col[j].begin();
            long long r2 = upper_bound(col[j].begin(), col[j].end(), buf[i][j]) - col[j].begin();
            r2 = col[j].size() - r2;

            cout << max(l1, l2) + max(r1, r2) + 1 << " ";
        }
        cout << "\n";
    }
    cout << "\n";


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}