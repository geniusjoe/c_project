#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 5005;
const long long INF = 0x7f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = 998244853;
const long long OVER_FLOW = 0xffffffff;

long long n, m;
bool flg;
long long vis[MAXN], color[MAXN];
vector <pair<long long, long long>> edges[MAXN];

void dfs(long long x) {
    for (auto it:edges[x]) {
        if (vis[it.first] == -1) {
            vis[it.first] = 0;
            dfs(it.first);
        } else if (vis[it.first] == 0) {
            color[it.second] = 1;
            flg = true;
        }
    }
    vis[x] = 1;
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
    cin >> n >> m;
    flg = false;
    for (long long i = 1; i <= n; i++) vis[i] = -1;
    for (long long i = 1; i <= m; i++) {
        long long u, v;
        cin >> u >> v;
        edges[u].emplace_back(v, i);
    }
    for (long long i = 1; i <= n; i++) {
        if (vis[i] == -1) dfs(i);
    }
    if (!flg) cout << 1 << endl;
    else cout << 2 << endl;
    for (long long i = 1; i <= m; i++) {
        cout << color[i] + 1 << " ";
    }
    cout << endl;


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}