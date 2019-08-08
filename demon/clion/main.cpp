#include<bits/stdc++.h>

#define loca
#define debu
using namespace std;

const int MAXN = 100025;
const int INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
const long long MOD = 1000000007;

long long n, m;
long long pre_sum[MAXN], dp[MAXN], buf[MAXN];

struct bus {
    int strt, end;

    bool operator<(bus bus1) {
        if (this->end == bus1.end)
            return this->strt < bus1.strt;
        else
            return this->end < bus1.end;
    }
} buses[MAXN];

int main() {

#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif // ONLINE_JUDGE

#ifndef ONLINE_JUDGE
    auto start_time = clock();
    cerr << setprecision(3) << fixed;
#endif

//    ios::sync_with_stdio(false);
//    cin >> T;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> buses[i].strt >> buses[i].end;
        buf[i] = buses[i].end;
    }
    sort(buses + 1, buses + 1 + m), sort(buf + 1, buf + 1 + m);
    for (int i = 1; i <= m; i++) {
        if (buses[i].strt == 0) dp[i] += 1;
        int l = lower_bound(buf + 1, buf + 1 + m, buses[i].strt) - buf;
        int r = lower_bound(buf + 1, buf + 1 + m, buses[i].end) - buf;
        if (buses[r].end == buses[i].end) r--;
        if (r >= l)
            dp[i] = (dp[i] + pre_sum[r] - pre_sum[l - 1] + MOD) % MOD;
        pre_sum[i] = (pre_sum[i - 1] + dp[i]) % MOD;
    }
    long long res = 0;
    for (int i = 1; i <= m; i++) if (buses[i].end == n) res += dp[i];
    res %= MOD;
    cout << res << endl;

#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}

/*
写代码时请注意：
    1.是否要开Long Long？数组边界处理好了么？
    2.实数精度有没有处理？
    3.特殊情况处理好了么？
    4.做一些总比不做好。
思考提醒：
    1.最大值和最小值问题可不可以用二分答案？
    2.有没有贪心策略？否则能不能dp？
*/