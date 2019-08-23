#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 100050;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
const long long MOD = 1e9 + 7;
const long long OVER_FLOW = 0xffffffff;

long long n, q, m, k, T, a, b;
vector<pair<long long, long long>> v, v1, v2;
long long res[MAXN];

struct point {
    long long l, r, id;

    bool operator<(point point1) {
        if (this->l == point1.l)
            return this->r < point1.r;
        else
            return this->l < point1.l;
    }
} points[MAXN];

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
        cin >> n;
        for (long long i = 1; i <= n; i++) {
            cin >> points[i].l >> points[i].r;
            points[i].id = i;
        }
        sort(points + 1, points + 1 + n);
        long long cur_r = points[1].l, pos = -1;
        for (long long i = 1; i <= n; i++) {
            if (points[i].l <= cur_r && points[i].r >= cur_r) {
                cur_r = points[i].r;
            } else if (points[i].r > cur_r) {
                pos = i;
                break;
            }
        }
        if (pos != -1) {
            for (long long i = 1; i <= n; i++) {
                if (i < pos) {
                    res[points[i].id] = 1;
                } else
                    res[points[i].id] = 2;
            }
            for (long long i = 1; i <= n; i++) {
                cout << res[i] << " ";
            }
            cout << endl;
        } else {
            cout << -1 << endl;
        }

    }


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}