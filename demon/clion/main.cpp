#include<bits/stdc++.h>

#define loca
#define debu
using namespace std;

const int MAXN = 300005;
const int INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
const long long MOD = 998244353;
const long long OVER_FLOW = 0xffffffff;

long long raw[MAXN];
long long buf[MAXN];
long long n, m;
bool vis[MAXN];

bool ok(long long x) {
    for (int i = 1; i <= n; i++)
        buf[i] = raw[i];
    for (int i = 1; i <= n; i++) {
        if (buf[i] == buf[i - 1]) {
            continue;
        } else if (buf[i] > buf[i - 1]) {
            if (buf[i] + x >= buf[i - 1] + m) {
                buf[i] = buf[i - 1];
            } else continue;
        } else if (buf[i] < buf[i - 1]) {
            if (buf[i] + x >= buf[i - 1]) {
                buf[i] = buf[i - 1];
            } else return false;
        }
    }
    return true;
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
    2.实数精度有没有处理？
    3.特殊情况处理好了么？
    4.做一些总比不做好。
思考提醒：
    1.最大值和最小值问题可不可以用二分答案？
    2.有没有贪心策略？否则能不能dp？
*/

    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> raw[i];
    }
    long long low = 0, high = m + 10, mid;
    while (low <= high) {
        mid = (low + high) >> 1;
        if (ok(mid))
            high = mid - 1;
        else
            low = mid + 1;
    }
    cout << low << endl;


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}

