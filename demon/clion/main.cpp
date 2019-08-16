#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 100005;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
const long long MOD = 998244353;
const long long OVER_FLOW = 0xffffffff;

long long n, m;
long long id[MAXN][30];
char raw[MAXN];
char s1[300], s2[300], s3[300];
long long s1_len, s2_len, s3_len;
long long dp[300][300][300];

void init() {
    for (long long i = 1; i <= 26; i++) id[n][i] = n + 1;
    for (long long i = n - 1; i >= 0; i--) {
        for (long long j = 1; j <= 26; j++) {
            id[i][j] = id[i + 1][j];
        }
        id[i][raw[i + 1] - 'a' + 1] = i + 1;
    }

    dp[0][0][0] = 0;
}

long long add(long long n1, long long n2, long long n3) {
    for (long long i = n1; i <= s1_len; i++) {
        for (long long j = n2; j <= s2_len; j++) {
            for (long long k = n3; k <= s3_len; k++) {
                dp[i][j][k] = n + 1;
                if (i > 0 && dp[i - 1][j][k] <= n)dp[i][j][k] = min(dp[i][j][k], id[dp[i - 1][j][k]][s1[i]]);
                if (j > 0 && dp[i][j - 1][k] <= n)dp[i][j][k] = min(dp[i][j][k], id[dp[i][j - 1][k]][s2[j]]);
                if (k > 0 && dp[i][j][k - 1] <= n)dp[i][j][k] = min(dp[i][j][k], id[dp[i][j][k - 1]][s3[k]]);
            }
        }
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
    scanf("%I64d%I64d", &n, &m);
    scanf("%s", raw + 1);
    init();
    for (long long i = 1; i <= m; i++) {
        char tmp[10];
        scanf("%s", tmp);
        long long u;
        scanf("%I64d", &u);
        if (tmp[0] == '+') {
            scanf("%s", tmp);
            if (u == 1) {
                ++s1_len;
                s1[s1_len] = tmp[0]-'a'+1;
                add(s1_len, 0, 0);
            } else if (u == 2) {
                ++s2_len;
                s2[s2_len] = tmp[0]-'a'+1;
                add(0, s2_len, 0);
            } else if (u == 3) {
                ++s3_len;
                s3[s3_len] = tmp[0]-'a'+1;
                add(0, 0, s3_len);
            }
        } else if (tmp[0] == '-') {
            if (u == 1) s1_len--;
            else if (u == 2) s2_len--;
            else if (u == 3) s3_len--;
        }
        if (dp[s1_len][s2_len][s3_len] < n + 1) {
            printf("YES\n");
        } else printf("NO\n");
    }


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}

