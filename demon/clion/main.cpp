#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 1000;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
const long long MOD = 1e9 + 7;
const long long OVER_FLOW = 0xffffffff;

long long n, k, m, T, l, r;
long long a, b, c, d, na, nb, nc, nd;
string buf[3];

bool ok() {
    return (0 <= a && a <= na && 0 <= b && b <= nb && 0 <= c && c <= nc & 0 <= d && d <= nd
            && a + b + c + d == n / 2);
}

void print_ans() {
    bool flg = false;
    for (long long i = 0; i < buf[1].size(); i++) {
        flg = false;
        if (buf[1][i] == '0' && buf[2][i] == '0' && a) {
            a--;
            flg = true;
        } else if (buf[1][i] == '0' && buf[2][i] == '1' && b) {
            b--;
            flg = true;
        }
        if (buf[1][i] == '1' && buf[2][i] == '0' && c) {
            c--;
            flg = true;
        }
        if (buf[1][i] == '1' && buf[2][i] == '1' && d) {
            d--;
            flg = true;
        }
        if (flg)
            cout << i + 1 << endl;
    }
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
思考提醒：
    1.最大值和最小值问题可不可以用二分答案？
    2.有没有贪心策略？否则能不能dp？
    3.如果规模小的话还能尝试dfs,如果存在等式可以暴力枚举变量
*/

    ios::sync_with_stdio(false);
    cin >> n;
    cin >> buf[1], cin >> buf[2];
    for (long long i = 0; i < buf[1].size(); i++) {
        if (buf[1][i] == '0' && buf[2][i] == '0') na++;
        else if (buf[1][i] == '0' && buf[2][i] == '1') nb++;
        else if (buf[1][i] == '1' && buf[2][i] == '0') nc++;
        else if (buf[1][i] == '1' && buf[2][i] == '1') nd++;
    }
    bool flg = false;
    for (long long i = 0; i <= nb; i++) {
        for (long long j = 0; j <= nc; j++) {
            b = i, c = j;
            d = nd + nb - b - c;
            if (d % 2 == 1) continue;
            d /= 2;
            a = n / 2 - b - c - d;
            if (ok()) {
                flg = true;
                print_ans();
                break;
            }
        }
        if (flg)
            break;
    }
    if (!flg) {
        cout << -1 << endl;
    }


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}