#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 300500;
const long long INF = 0x7f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = 998244353;
const long long OVER_FLOW = 0xffffffff;

long long n, m; /**< n个数,m个操作,以model为模 */
vector<long long> v;
long long A[MAXN];

struct node {
    long long l, r;

    bool operator==(node node1) {
        return (this->l == node1.l && this->r == node1.r);
    }
} nodes[MAXN];

bool cmp1(node node1, node node2) {
    if (node1.l == node2.l)
        return node1.r < node2.r;
    return node1.l < node2.l;
}

bool cmp2(node node1, node node2) {
    if (node1.r == node2.r)
        return node1.l < node2.l;
    return node1.r < node2.r;
}

void arange() {
    A[1] = 1;
    for (long long i = 2; i <= n; i++)
        A[i] = A[i - 1] * i % MOD;
}

long long calc(long long type) {
    v.clear();
    long long cnt = 0;
    for (long long i = 1; i <= n; i++) {
        if (i == 1) cnt++;
        else if (type == 3 && nodes[i].l < nodes[i - 1].l) return 0;
        else if (type == 1 && nodes[i].l != nodes[i - 1].l) {
            v.push_back(cnt);
            cnt = 1;
        } else if (type == 2 && nodes[i].r != nodes[i - 1].r) {
            v.push_back(cnt);
            cnt = 1;
        } else if (type == 3 && (nodes[i].l > nodes[i - 1].l || nodes[i].r > nodes[i - 1].r)) {
            v.push_back(cnt);
            cnt = 1;
        } else
            cnt++;
    }
    v.push_back(cnt);

    long long cur = 1;
    for (auto it:v) {
        if (it > 1) {
            cur = cur * A[it] % MOD;
        }
    }
    return cur;
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

    ios::sync_with_stdio(false);
    cin >> n;
    arange();
    for (long long i = 1; i <= n; i++) {
        cin >> nodes[i].l >> nodes[i].r;
    }
    long long res = 1;
    res = res * A[n] % MOD;
    sort(nodes + 1, nodes + 1 + n, cmp1);
    res = (res - calc(1) + MOD) % MOD;

    sort(nodes + 1, nodes + 1 + n, cmp2);
    res = (res - calc(2) + MOD) % MOD;

    res = (res + calc(3)) % MOD;

    cout << res << endl;

#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}