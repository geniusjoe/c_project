#include<bits/stdc++.h>

#define loca
#define debu
using namespace std;

const int MAXN = 2000025;
const int INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
const long long MOD = 998244353;

long long n, m;
char str[MAXN];
int res[10 + 5][10 + 5];
int buf[10 + 5][10 + 5][10 + 5];

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

    scanf("%s", str);
    for (int i = 0; i <= 9; i++)
        for (int j = 0; j <= 9; j++) {
            for (int k = 0; k <= 9; k++) buf[i][j][k] = INF;
            for (int k = 0; k <= 10; k++) {
                for (int l = 0; l <= 10; l++) {
                    if(k==0&&l==0)  continue;
                    int cur = (i * k + j * l) % 10;
                    buf[i][j][cur] = min(buf[i][j][cur], k + l);
                }
            }
        }

    for (int i = 0; i <= 9; i++) {
        for (int j = 0; j <= 9; j++) {
            bool flg = true;
            int cur_res = 0;
            for (int k = 1; k < strlen(str); k++) {
                int cur = str[k] - str[k - 1];
                if (cur < 0) cur += 10;
                if (buf[i][j][cur] == INF) {
                    flg = false;
                    break;
                } else {
                    if (buf[i][j][cur] >= 2)
                        cur_res += buf[i][j][cur]-1;
                }
            }
            if (!flg)
                res[i][j] = -1;
            else
                res[i][j] = cur_res;
            printf("%d ", res[i][j]);
        }
        printf("\n");
    }


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