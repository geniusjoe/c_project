#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 4000;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = (long long) 1e9 + 7;
const long long OVER_FLOW = 0xffffffff;

long long n;
int g[MAXN * MAXN];
int buf[MAXN][MAXN];
int mx[MAXN][MAXN];


deque<long long> q;

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
    long long m, a, b;
    cin >> n >> m >> a >> b;
    long long x, y, z;
    cin >> g[0] >> x >> y >> z;
    for (long long i = 1; i <= n * m; i++) g[i] = (g[i - 1] * x + y) % z;
    for (long long i = 1; i <= n; i++) {
        for (long long j = 1; j <= m; j++) {
            buf[i][j] = g[(i - 1) * m + j - 1];
        }
    }
    for (long long i = 1; i <= n; i++) {
        q.clear();
        for (long long j = 1; j <= m; j++) {
            while (!q.empty() && j - q.front() + 1 > b) q.pop_front();
            while (!q.empty() && buf[i][q.back()] > buf[i][j]) q.pop_back();
            q.push_back(j);
            mx[i][j] = buf[i][q.front()];
        }
    }

    long long res = 0;
    for (long long i = b; i <= m; i++) {
        q.clear();
        for (long long j = 1; j <= n; j++) {
            while (!q.empty() && j - q.front() + 1 > a) q.pop_front();
            while (!q.empty() && mx[q.back()][i] > mx[j][i]) q.pop_back();
            q.push_back(j);
            if (j >= a) res += mx[q.front()][i];
        }
    }
    cout << res << endl;


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}