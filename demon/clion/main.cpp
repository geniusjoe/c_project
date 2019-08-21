#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 5005;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
const long long MOD = 1e9 + 7;
const long long OVER_FLOW = 0xffffffff;

long long n, q;
vector<int> v[MAXN];
int a[MAXN], b[MAXN][MAXN];


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
    3.如果规模小的话还能尝试dfs,如果存在等式.转换关系少可以暴力枚举变量
*/

    ios::sync_with_stdio(false);
    cin >> n >> q;
    for (long long i = 1; i <= q; i++) {
        long long l, r;
        cin >> l >> r;
        for (long long j = l; j <= r; j++) v[j].push_back(i);
    }
    long long sm = 0;
    for (long long i = 1; i <= n; i++) {
        long long m = v[i].size();
        if (m > 0) sm++;
        if (m == 1) a[v[i][0]]++;
        else if (m == 2) b[v[i][0]][v[i][1]]++;
    }
    long long res = 0;
    for (long long i = 1; i <= q; i++) {
        for (long long j = i + 1; j <= q; j++) {
            res = max(res, sm - a[i] - a[j] - b[i][j]);
        }
    }
    cout << res << endl;


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}