#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 200500;
const long long INF = 0x7f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = (long long) 1e9 + 7;
const long long OVER_FLOW = 0xffffffff;

int n, m, model; /**< n个数,m个操作,以model为模 */
int a[15][MAXN];
pair<int , int > ans[15][MAXN << 2];

inline int  lchild(int  x)
/**<  每个树节点的编号*/
{
    return x << 1;
}

inline int  rchild(int  x) {
    return x << 1 | 1;
}

inline void push_up(int  idx, int  p) {
    int v[5];
    v[1]=ans[idx][lchild(p)].first;
    v[2]=ans[idx][lchild(p)].second;
    v[3]=ans[idx][rchild(p)].first;
    v[4]=ans[idx][rchild(p)].second;
    sort(v+1,v+1+4);
    ans[idx][p].first = v[1];
    ans[idx][p].second = v[2];
}

/**< 由顶向下建立线段树 */
/**< 左右均为闭区间 */
void build(int  idx, int  p, int  l, int  r) {
    if (l == r) {
        ans[idx][p].first = a[idx][l], ans[idx][p].second = INF;
        return;
    }
    int  mid = (l + r) >> 1;
    build(idx, lchild(p), l, mid);
    build(idx, rchild(p), mid + 1, r);
    push_up(idx, p);
}

/**< 区间赋值操作 */
/**< 区间内元素增加的值 */
inline void update(int  idx, int  nl, int  nr,   /**< 目标边界 */
                   int  l, int  r, int  p, int  tar /**< 当前边界和节点 */
) {
    if (nl <= l && r <= nr) {
        ans[idx][p].first = tar, ans[idx][p].second = INF;
        return;
    }
    int  mid = (l + r) >> 1;
    if (nl <= mid)
        update(idx, nl, nr, l, mid, lchild(p), tar);
    if (nr > mid)
        update(idx, nl, nr, mid + 1, r, rchild(p), tar);
    push_up(idx, p);
}


/**< 区间查询操作 */
pair<int , int > query(int  idx, int  q_x, int  q_y, int  l, int  r, int  p) {
    pair<int , int > res;
    if (q_x <= l && r <= q_y)
        return ans[idx][p];
    int  mid = (l + r) >> 1;

    int v[7],cnt=0;
    if (q_x <= mid) {
        pair<int , int > cur = query(idx, q_x, q_y, l, mid, lchild(p));
        v[++cnt]=cur.first;
        v[++cnt]=cur.second;
    }

    if (q_y > mid) {
        pair<int , int > cur = query(idx, q_x, q_y, mid + 1, r, rchild(p));
        v[++cnt]=cur.first;
        v[++cnt]=cur.second;
    }
    sort(v+1,v+1+cnt);
    res.first = v[1], res.second = v[2];

    return res;
}

template<class T>
inline bool scan_d(T &ret) {
    char c;
    int sgn;
    if (c = getchar(), c == EOF) return 0;
    while (c != '-' && (c < '0' || c > '9')) c = getchar();
    sgn = (c == '-') ? -1 : 1;
    ret = (c == '-') ? 0 : (c - '0');
    while (c = getchar(), c >= '0' && c <= '9') ret = ret * 10 + (c - '0');
    ret *= sgn;
    return 1;
}

inline void out(int x) {
    if (x > 9) out(x / 10);
    putchar(x % 10 + '0');
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

//    ios::sync_with_stdio(false);
//    cin >> n >> m;
    scan_d(n), scan_d(m);

    for (int  i = 1; i <= n; i++) {
        int  u;
        scan_d(u);
        int  t = u;
        for (int  j = 1; j <= 10; j++) {
            if (t % 10) {
                a[j][i] = u;
            } else a[j][i] = INF;
            t /= 10;
        }
    }

    for (int  i = 1; i <= 10; i++) {
        build(i, 1, 1, n);
    }
    for (int  i = 1; i <= m; i++) {
        int  u, v, w;
//        cin >> u >> v >> w;
        scan_d(u), scan_d(v), scan_d(w);
        if (u == 1) {
            int  t = w;
            for (int  j = 1; j <= 10; j++) {
                if (t % 10) {
                    update(j, v, v, 1, n, 1, w);
                } else update(j, v, v, 1, n, 1, INF);
                t /= 10;
            }
        } else {
            int  cur = INF;
            for (int  j = 1; j <= 10; j++) {
                pair<int , int > t = query(j, v, w, 1, n, 1);
                if (t.second != INF) {
                    cur = min(cur, t.first + t.second);
                }
            }
            if (cur != INF) {
//                cout << cur << '\n';
                out(cur);
                puts("");
            } else
//                cout << -1 << '\n';
                puts("-1");
        }
    }

#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}