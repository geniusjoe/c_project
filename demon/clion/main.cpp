#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 5500;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
const long long MOD = 1e9 + 7;
const long long OVER_FLOW = 0xffffffff;

long long n, q, m, k, T;
string str;
bool tmp[MAXN][MAXN];
int buf[MAXN][MAXN];
vector<int> v;

bool ok(int x) {
    for (long long i = x; i <= n; i += x) {
        for (long long j = x; j <= n; j += x) {
            long long u = buf[i][j] - buf[i - x][j] - buf[i][j - x] + buf[i - x][j - x];
            if (u == x * x || u == 0)
                continue;
            else return false;
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
    for (long long i = 1; i <= n; i++) {
        cin >> str;
        for (long long j = 0; j < str.size(); j++) {
            long long cur = 0;
            if (str[j] >= '0' && str[j] <= '9') {
                cur = str[j] - '0';
            } else if (str[j] >= 'A' && str[j] <= 'F') {
                cur = str[j] - 'A' + 10;
            }
            if (cur / 8 == 1) tmp[i][4 * j + 1] = true;
            cur %= 8;
            if (cur / 4 == 1) tmp[i][4 * j + 2] = true;
            cur %= 4;
            if (cur / 2 == 1) tmp[i][4 * j + 3] = true;
            cur %= 2;
            if (cur / 1 == 1) tmp[i][4 * j + 4] = true;
            cur %= 1;
        }
    }

    for (long long i = 1; i <= n; i++) {
        for (long long j = 1; j <= n; j++) {
            buf[i][j] = buf[i - 1][j] + buf[i][j - 1] - buf[i - 1][j - 1] + tmp[i][j] ;
        }
    }

    for (long long i = 1; i * i <= n; i++)
        if (n % i == 0) {
            v.push_back(i);
            if (i != n / i) v.push_back(n / i);
        }
    sort(v.begin(), v.end());

    int res = 0;
    for (int i : v) {
        if (ok(i)) res = i;
        else continue;
    }
    cout << res << endl;


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}