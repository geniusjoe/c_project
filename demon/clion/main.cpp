#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 200500;
const long long PHI = (long long) 998244352;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = (long long) 998244353;
const long long OVER_FLOW = 0xffffffff;

long long n, k, m;

//******************************
//返回d=gcd(a,b); 和对应于等式ax+by=d 中的x,y
long long extend_gcd(long long a, long long b, long long &x, long long &y) {
    if (a == 0 && b == 0) return -1;//无最大公约数
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long d = extend_gcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

//********* 求逆元*******************
//ax = 1(mod n)
long long inv(long long a, long long n) {
    long long x, y;
    long long d = extend_gcd(a, n, x, y);
    if (d == 1) return (x % n + n) % n;
    else return -1;
}

long long a[MAXN], ans[MAXN << 2];

inline long long lchild(long long x)
/**<  每个树节点的编号*/
{
    return x << 1;
}

inline long long rchild(long long x) {
    return x << 1 | 1;
}

inline void push_up(long long p) {
    ans[p] = ans[lchild(p)] + ans[rchild(p)];
}

/**< 由顶向下建立线段树 */
/**< 左右均为闭区间 */
void build(long long p, long long l, long long r) {
    if (l == r) {
        ans[p] = 0;
        return;
    }
    long long mid = (l + r) >> 1;
    build(lchild(p), l, mid);
    build(rchild(p), mid + 1, r);
    push_up(p);
}
/**< 区间赋值操作 */
/**< 区间内元素增加的值 */
inline void update(long long nl, long long nr,   /**< 目标边界 */
                   long long l, long long r, long long p /**< 当前边界和节点 */
) {
    if (nl <= l && r <= nr) {
        ans[p] = 1;
        return;
    }
    long long mid = (l + r) >> 1;
    if (nl <= mid)
        update(nl, nr, l, mid, lchild(p));
    if (nr > mid)
        update(nl, nr, mid + 1, r, rchild(p));
    push_up(p);
}

/**< 区间查询操作 */
long long query(long long q_x, long long q_y, long long l, long long r, long long p) {
    long long res = 0;
    if (q_x <= l && r <= q_y)
        return ans[p];
    long long mid = (l + r) >> 1;
    if (q_x <= mid)
        res += query(q_x, q_y, l, mid, lchild(p));
    if (q_y > mid)
        res += query(q_x, q_y, mid + 1, r, rchild(p));
    return res;
}

long long buf[MAXN];

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
    1.数学公式尝试化简
    2.dp或者数值太大,尝试给出递推公式
    3.概率题随机生成考虑1/2的情况,或者是满足的方案/所有可能的方案
    5.排序之前不能取模.
    6.0-1子矩阵子序列:前缀和,异或和
    7.模拟题注意代码复用.
    8.单个区间问题考虑前缀和,多个区间左右端点拆开,排序,记录端点极值
思考提醒：
    1.最大值和最小值问题可不可以用二分+贪心？
    2.dp
    3.如果规模小的话还能尝试dfs
    4.如果存在等式.转换关系少可以暴力枚举变量,或者考虑从数据大小入手
    5.离散化+打表
*/

    ios::sync_with_stdio(false);
    cin >> n;
    build(1, 1, n);
    long long res = 0, tot = 0;
    for (long long i = 1; i <= n; i++) {
        cin >> buf[i];
        if (buf[i] == -1) {
            tot++;
        } else {
            res = (res + query(buf[i], n, 1, n, 1)) % MOD;
            update(buf[i], buf[i], 1, n, 1);
        }
    }

    res = (res + tot * (tot - 1) % MOD * inv(4ll, MOD) % MOD) % MOD;

    long long cnt = 0;
    if (tot > 0) {
        for (long long i = 1; i <= n; i++) {
            if (buf[i] == -1) cnt++;
            else {
                long long les = buf[i] - query(1, buf[i], 1, n, 1), grt = tot - les;
                res = (res + inv(tot, MOD) * grt % MOD * cnt % MOD) % MOD;
                res = (res + inv(tot, MOD) * les % MOD * (tot - cnt) % MOD) % MOD;
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