#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 100500;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
const long long MOD = 998244353;
const long long OVER_FLOW = 0xffffffff;

long long n, q, m, k, T;
long long buf[MAXN];
vector<pair<long long, long long>> dgre_else;
vector<long long> dgre_1;
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
思考提醒：
    1.最大值和最小值问题可不可以用二分答案？
    2.有没有贪心策略？否则能不能dp？
    3.如果规模小的话还能尝试dfs,如果存在等式.转换关系少可以暴力枚举变量
*/

    ios::sync_with_stdio(false);
    cin >> n;
    long long sm = 0;
    for (long long i = 1; i <= n; i++) {
        long long u;
        cin >> u;
        if (u == 1) dgre_1.push_back(i);
        else dgre_else.emplace_back(i, u);
        sm += u;
    }
    long long len = 0;
    if (sm < 2 * n - 2) cout << "NO" << endl;
    else {
        len = dgre_else.size() - 1;
        for (long long i = 1; i < dgre_else.size(); i++) {
            res.emplace_back(dgre_else[i - 1].first, dgre_else[i].first);
            dgre_else[i - 1].second--;
            dgre_else[i].second--;
        }
        if (!dgre_1.empty()) {
            len++;
            res.emplace_back(dgre_1.back(), dgre_else[0].first);
            dgre_1.pop_back();
            dgre_else[0].second--;
        }
        if (!dgre_1.empty()) {
            len++;
            res.emplace_back(dgre_1.back(), dgre_else.back().first);
            dgre_1.pop_back();
            dgre_else.back().second--;
        }
        while (!dgre_1.empty()) {
            while (dgre_else.back().second == 0) dgre_else.pop_back();
            res.emplace_back(dgre_1.back(), dgre_else.back().first);
            dgre_else.back().second--;
            dgre_1.pop_back();
        }

        cout << "YES" << " " << len << endl;
        cout << res.size() << endl;
        for (auto it:res) {
            cout << it.first << " " << it.second << endl;
        }
    }


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}