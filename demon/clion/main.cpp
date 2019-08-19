#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 100005;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
const long long MOD = 998244353;
const long long OVER_FLOW = 0xffffffff;

long long buf[MAXN];
long long n, k, a, b, m;
vector<long long> v;

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
    cin >> n >> k >> a >> b;
    long long tmp1 = a + b, tmp2 = a - b, tmp3 = -a + b, tmp4 = -a - b;
    long long mx = 0, mn = LINF;
    for (auto it : {tmp1, tmp2, tmp3, tmp4}) {
        for (long long i = 0; i <= n; i++) {
            if (i * k + it < 0) continue;
            mx = max(n * k / __gcd(n * k, i * k + it), mx);
            mn = min(n * k / __gcd(n * k, i * k + it), mn);
        }
    }
    cout << mn << " " << mx << endl;


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}