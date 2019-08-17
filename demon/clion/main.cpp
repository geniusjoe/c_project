#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 300005;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
const long long MOD = 998244353;
const long long OVER_FLOW = 0xffffffff;

long long n, m, k;

bool type[MAXN];
vector<long long> v[MAXN];

long long dfs(long long p, long long x) {
    if (v[x].empty()) {
        k++;
        return 1;
    } else if (type[x] == 1) {
        long long res = LINF;
        for (auto it:v[x]) {
            res = min(res, dfs(x, it));
        }
        return res;
    } else if (type[x] == 0) {
        long long res = 0;
        for (auto it:v[x]) {
            res += dfs(x, it);
        }
        return res;
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
    2.实数精度有
    4.做一些总比不做好.
    5.排序之前不能取模.
思考提醒：
    1.最大值和最小值问题可不可以用二分答案？
    2.有没有贪心策略？否则能不能dp？
    3.如果规模小的话还能尝试dfs
*/

    ios::sync_with_stdio(false);
    cin >> n;
    for (long long i = 1; i <= n; i++) cin >> type[i];
    for (long long i = 2; i <= n; i++) {
        long long u;
        cin >> u;
        v[u].push_back(i);
    }
    long long cur = dfs(-1ll, 1ll);
    cout << k - cur + 1 << endl;


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}
