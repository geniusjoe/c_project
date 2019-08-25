#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 300500;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
const long long MOD = 998244353;
const long long OVER_FLOW = 0xffffffff;

long long n, m, k, T;
long long buf[MAXN];
map<int, int> nxt, lst;


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
    cin >> n >> T;
    long long sm = 0;
    nxt[0] = 1;
    lst[1] = 0;
    for (long long i = 1; i <= n; i++) {
        cin >> buf[i];
        sm += buf[i];
        if (i == n) nxt[i] = -1;
        else nxt[i] = i + 1;
        lst[i] = i - 1;
    }
    long long res = 0, nm = n;
    long long mn = *min_element(buf + 1, buf + 1 + n);

    while (T >= mn) {
        if (T >= sm) {
            long long tme = T / sm;
            T -= T / sm * sm;
            res += nm * tme;
        } else {
            for (long long i = nxt[0]; i != -1; i = nxt[i]) {
                if (T >= buf[i]) {
                    T -= buf[i];
                    res++;
                } else if (T < buf[i]) {
                    nxt[lst[i]] = nxt[i];
                    lst[nxt[i]] = lst[i];
                    sm -= buf[i];
                    nm--;
                }
            }
        }
    }
    cout << res << endl;


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}