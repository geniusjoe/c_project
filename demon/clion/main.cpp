#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 800;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
const long long MOD = 998244353;
const long long OVER_FLOW = 0xffffffff;

long long n, x, m;
long long buf[MAXN][MAXN];


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

//    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (long long i = 1; i <= n; i++) {
        for (long long j = 1; j <= m; j++) cin >> buf[i][j];
    }

    long long cur = 0;
    bool flg = false;
    for (long long i = 1; i <= n; i++) cur ^= buf[i][1];
    if (!cur) {
        for (long long i = 1; i <= n; i++) {
            for (long long j = 2; j <= m; j++) {
                cur ^= buf[i][1];
                cur ^= buf[i][j];
                if (cur) {
                    cout << "TAK" << endl;
                    for (long long k = 1; k <= n; k++) {
                        if (k == i) cout << j << " ";
                        else cout << "1 ";
                    }
                    cout << endl;
                    flg = true;
                    break;
                }
                cur ^= buf[i][j];
                cur ^= buf[i][1];
            }
            if(flg) break;
        }
    } else {
        flg = true;
        cout << "TAK" << endl;
        for (long long i = 1; i <= n; i++) {
            cout << "1 ";
        }
        cout << endl;
    }


    if (!flg)
        cout << "NIE" << endl;


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}
