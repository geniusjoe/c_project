#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 5005;
const long long INF = 0x7f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = 998244353;
const long long OVER_FLOW = 0xffffffff;

long long n; /**< n个数,m个操作,以model为模 */
long long res1[500010], res2[500010];


struct Trie {
    int next[500010][26], fail[500010], end[500010];
    int root, L;

    int newnode() {
        for (int i = 0; i < 26; i++)
            next[L][i] = -1;
        end[L++] = 0;
        return L - 1;
    }

    void init() {
        L = 0;
        root = newnode();
    }

    void insert(char buf[]) {
        int len = strlen(buf);
        int now = root;
        for (int i = 0; i < len; i++) {
            if (next[now][buf[i] - 'a'] == -1)
                next[now][buf[i] - 'a'] = newnode();
            now = next[now][buf[i] - 'a'];
        }
        end[now]++;
    }

    void build() {
        queue<int> Q;
        fail[root] = root;
        for (int i = 0; i < 26; i++)
            if (next[root][i] == -1)
                next[root][i] = root;
            else {
                fail[next[root][i]] = root;
                Q.push(next[root][i]);
            }
        while (!Q.empty()) {
            int now = Q.front();
            Q.pop();
            end[now]+=end[fail[now]];
            for (int i = 0; i < 26; i++)

                if (next[now][i] == -1)
                    next[now][i] = next[fail[now]][i];
                else {
                    fail[next[now][i]] = next[fail[now]][i];
                    Q.push(next[now][i]);
                }
        }
    }

    int query(char buf[], long long res1[]) {
        int len = strlen(buf);
        int now = root;
        int res = 0;
        for (int i = 0; i < len; i++) {
            now = next[now][buf[i] - 'a'];
            int temp = now;
//            while (temp != root) {
//                res += end[temp];
//                end[temp] = 0;
                res1[i] += end[temp];
//                temp = fail[temp];
//            }
        }
        return res;
    }

    void debug() {
        for (int i = 0; i < L; i++) {
            printf("id␣=␣%3d,fail␣=␣%3d,end␣=␣%3d,chi␣=␣[", i, fail[i
            ], end[i]);
            for (int j = 0; j < 26; j++)
                printf("%2d", next[i][j]);
            printf("]\n");
        }
    }
};

char buf[1000010], raw[1000010];
Trie ac1, ac2;

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
    3.下标能从最小值开始就从最小值开始
    5.排序之前不能取模.
    6.0-1子矩阵子序列:前缀和
    7.模拟题注意代码复用.
    8.单个区间问题考虑前缀和,多个区间左右端点拆开,排序,记录端点极值
思考提醒：
    1.最大值和最小值问题可不可以用二分+贪心？
    2.dp
    3.如果规模小的话还能尝试dfs
    4.如果存在等式.转换关系少可以暴力枚举变量,或者考虑从数据大小入手
*/

//    ios::sync_with_stdio(false);
    long long T;
//    cin >> raw;
//    cin >> T;
    scanf("%s", raw), scanf("%I64d", &T);
    ac1.init(), ac2.init();
    while (T--) {
//        cin >> buf;
        scanf("%s", buf);
        long long cur_len = strlen(buf);
        ac1.insert(buf);
        reverse(buf, buf + cur_len);
        ac2.insert(buf);
    }
    ac1.build(), ac2.build();
//    strcpy(buf, raw);
    long long str_len = strlen(raw);
    ac1.query(raw, res1);
    reverse(raw, raw + str_len);
    ac2.query(raw, res2);
    long long res = 0;
    for (long long i = 0; i < str_len - 1; i++) {
        res += res1[i] * res2[str_len - i - 2];
    }
//    cout << res << endl;
    printf("%I64d\n", res);

#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}