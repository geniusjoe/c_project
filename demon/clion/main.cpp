#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 300500;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
const long long MOD = 998244353;
const long long OVER_FLOW = 0xffffffff;

long long n, q, m, k, T;
vector<long long> edge[MAXN];
bool vis[MAXN];
long long clr[MAXN];
vector<pair<long long, long long>> v;
long long odd, even;
bool flg;

// a ^ b % c
long long qpow(long long a, long long b, long long c) {
    long long cur = 1;
    while (b) {
        if (b & 1) cur = cur * a % c;
        a = a * a % c, b >>= 1;
    }
    return cur;
}


void dfs(long long p, long long x, long long color) {
    for (auto i:edge[x]) {
        if (!flg) break;
        if (i == p) continue;
        if (clr[i] != -1) {
            if (clr[i] == color) continue;
            else if (clr[i] != color) {
                flg = false;
                break;
            }
        } else {
            clr[i] = color;
            if (clr[i]) odd++;
            else even++;
            dfs(x, i, !color);
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
    4.做一些总比不做好.
    5.排序之前不能取模.
    6.0-1子矩阵子序列:前缀和
思考提醒：
    1.最大值和最小值问题可不可以用二分答案？
    2.有没有贪心策略？否则能不能dp？
    3.如果规模小的话还能尝试dfs,如果存在等式.转换关系少可以暴力枚举变量
*/

    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (long long i = 1; i <= n; i++) {
            vis[i] = false;
            edge[i].clear();
            clr[i] = -1;
            v.clear();
        }
        for (long long i = 1; i <= m; i++) {
            long long u, v;
            cin >> u >> v;
            edge[u].push_back(v), edge[v].push_back(u);
        }
        flg = true;
        for (long long i = 1; i <= n; i++) {
            if (clr[i] == -1) {
                odd = even = 0;
                clr[i] = 0;
                even++;
                dfs(-1, i, 1);
                v.emplace_back(odd, even);
            }
            if (!flg) break;
        }

        if (flg) {
            long long res = 1;
            for (auto it:v) {
                if (it.second == 1 && it.first == 0) res = res * 3 % MOD;
                else {
                    res *= qpow(2, it.first, MOD) + qpow(2, it.second, MOD);
                    res %= MOD;
                }
            }
            cout << res << endl;
        } else {
            cout << 0 << endl;
        }
    }


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}