#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 300005;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
const long long MOD = 1e9 + 7;
const long long OVER_FLOW = 0xffffffff;

long long buf[MAXN];
long long n, k, m, T, res;
vector<long long> v[MAXN];
long long nm[MAXN];

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
思考提醒：
    1.最大值和最小值问题可不可以用二分答案？
    2.有没有贪心策略？否则能不能dp？
    3.如果规模小的话还能尝试dfs
*/

    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (long long i = 1; i <= n; i++) cin >> buf[i];
    for (long long i = 1; i <= m; i++) {
        long long u, w;
        cin >> u >> w;
        v[w].push_back(u);
    }
    for (auto it:v[buf[n]]) nm[it]++;
    for (long long i = n - 1; i >= 1; i--) {
        if (nm[buf[i]] + i + res == n) res++;
        else
            for (auto it:v[buf[i]]) {
                nm[it]++;
            }
    }
    cout << res << endl;

#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}