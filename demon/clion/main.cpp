#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 200000;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = 998244353;
const long long OVER_FLOW = 0xffffffff;


long long c, s, T, n, m, M, a, b;
long long nxt[MAXN], l[MAXN], r[MAXN];  /**< f[i]记录父节点 */;
long long f[MAXN];


int find(int x) { //模板函数；
    if (f[x] != x)
        f[x] = find(f[x]);
    return f[x];
}


void combine(int a, int b) {
    int fa = find(a);
    int fb = find(b);
    if (fa != fb) {
        f[fb] = fa;
        nxt[r[fa]] = l[fb];
        r[fa] = r[fb];
        l[fb] = l[fa];
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
    for (int i = 1; i <= n; i++) {
        f[i] = i;
        l[i] = r[i] = i;
    }
    for (long long i = 1; i <= n - 1; i++) {
        long long u, v;
        cin >> u >> v;
        combine(u, v);
    }
    for (long long i = 1; i <= n; i++) {
        if (l[i] == i) {
            cout << i << " ";
            long long cur = nxt[i];
            while (cur) {
                cout << cur << " ";
                cur = nxt[cur];
            }
            cout << endl;
        }
    }


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}