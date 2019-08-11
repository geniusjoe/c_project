#include<bits/stdc++.h>

#define loca
#define debu
using namespace std;

const int MAXN = 300005;
const int INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
const long long MOD = 998244353;
const long long OVER_FLOW = 0xffffffff;

long long n, m, T, M;
long long buf[MAXN];
long long pre_sum[MAXN];

struct qry {
    long long tme, val;
} qrys[MAXN];

vector<qry> v;

int main() {

#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif // ONLINE_JUDGE

#ifndef ONLINE_JUDGE
    auto start_time = clock();
    cerr << setprecision(3) << fixed;
#endif

    ios::sync_with_stdio(false);
    long long T, k, x = -1;
//    scanf("%I64d", &T);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> buf[i];
    long long res = 0;

    for (int i = n; i >= 1; i--) pre_sum[i] = pre_sum[i + 1] + buf[i];
    sort(pre_sum+1+1,pre_sum+1+n);
    res+=pre_sum[1];
    for(int i=1;i<=k-1;i++) res+=pre_sum[n-i+1];

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