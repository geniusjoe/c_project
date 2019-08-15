#include<bits/stdc++.h>

#define setbit(x, y) x|=(1ll<<y)

#define clrbit(x, y) x&=~(1ll<<y)

#define reversebit(x, y) x^=(1ll<<y)

#define getbit(x, y) ((x) >> (y)&1ll)


using namespace std;

const long long MAXN = 100;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
const long long MOD = 998244353;
const long long OVER_FLOW = 0xffffffff;

long long n, m;
long long nm[MAXN];
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
    2.实数精度有没有处理？
    3.特殊情况处理好了么？
    4.做一些总比不做好.
    5.排序之前不能取模.
思考提醒：
    1.最大值和最小值问题可不可以用二分答案？
    2.有没有贪心策略？否则能不能dp？
    3.如果规模小的话还能尝试dfs
*/

    ios::sync_with_stdio(false);
    long long a, b;
    cin >> a >> b;
    if (a < b) swap(a, b);
    long long tmp = a - b;

    for (long long i = 1; i * i <= tmp; i++) {
        if (tmp % i == 0) {
            v.push_back(i);
            if (i != tmp / i) v.push_back(tmp / i);
        }
    }
    long long res = 0, res_cnt = LINF;
    for (auto it:v) {
        long long k = (b + it - 1) / it * it - b;
        if (res_cnt > (a + k) * (b + k) / it) {
            res_cnt = (a + k) * (b + k) / it;
            res = k;
        }
    }
    cout << res << endl;


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}

