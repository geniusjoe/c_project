#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 3000;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = 998244353;
const long long OVER_FLOW = 0xffffffff;


long long c, s, T, n, m, M, a, b;
vector<pair<long long, long long>> res;
long long buf[300050];

long long ans;//最小环长度
long long dis[MAXN][MAXN];//存储最后最短路的结果
long long mp[MAXN][MAXN]; //存储距离
void floyd() {
    ans = LINF;
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= k; ++i) {
            for (int j = i + 1; j <= k; ++j) {
                ans = min(ans, dis[i][j] + mp[i][k] + mp[k][j]);
            }
        }

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (dis[i][j] > dis[i][k] + dis[k][j])
                    dis[i][j] = dis[i][k] + dis[k][j];
            }
        }
    }
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
    cin >> n;
    long long cnt = 0;
    for (long long i = 1; i <= n; i++) {
        long long u;
        cin >> u;
        if (u != 0) buf[++cnt] = u;
    }
    for (long long i = 1; i < MAXN; i++) {
        for (long long j = 1; j < MAXN; j++) dis[i][j] = mp[i][j] = LINF;
    }
    if (cnt > 200) {
        cout << "3" << endl;
    } else {
        for (long long i = 1; i <= cnt; i++) {
            for (long long j = 1; j < i; j++) {
                if (buf[i] & buf[j]) {
                    mp[j][i] = mp[i][j] = 1;
                    //dis[i][j] = dis[j][i] = 1;
                }
            }
        }
        n = cnt;
        floyd();
        if (ans != LINF)
            cout << ans << endl;
        else cout << -1 << endl;
    }


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}