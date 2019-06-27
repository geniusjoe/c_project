#include<bits/stdc++.h>
#define loc
#define debu
using namespace std;

#define MAXM    500000+5

const int MAXN = 500005;
const int M = MAXN * 40;


/**< 树链剖分 */
struct Edge {
    int to, next;
} edge[MAXN * 2];
int head[MAXN], tot;
int top[MAXN];
int fa[MAXN];
int deep[MAXN];
int num[MAXN];
int p[MAXN];
int fp[MAXN];
int son[MAXN];
int pos;

/**< 主席树 */
int n, q, m, tot;
int a[MAXN], t[MAXN];
int times[MAXN];
int T[MAXN], lson[M], rson[M], c[M];
int seg_sum[M], seg_max[M];

/**< 树链剖分 */
void addedge(int u, int v) {
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}
void dfs1(int u, int pre, int d) {
    deep[u] = d;
    fa[u] = pre;
    num[u] = 1;
    for(int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].to;
        if(v != pre) {
            dfs1(v, u, d + 1);
            num[u] += num[v];
            if(son[u] == -1 || num[v] > num[son[u]])
                son[u] = v;
        }
    }
}
void getpos(int u, int sp) {
    top[u] = sp;
    p[u] = pos++;
    fp[p[u]] = u;
    if(son[u] == -1)
        return ;
    getpos(son[u], sp);
    for(int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].to;
        if(v != son[u] && v != fa[u])
            getpos(v, v);
    }
}
void build(int l, int r) {
    int root = tot++;
    seg_sum[root] = 0;
    seg_max[root] = 0;
    if(l != r) {
        int mid = (l + r) >> 1;
        lson[root] = build(l, mid);
        rson[root] = build(mid + 1, r);
    }
    return root;
}
void push_up(int i) {
    seg_max[i] = max(seg_max[lson[i]], seg_max[rson[i]]);
    seg_sum[i] = seg_sum[lson[i]] + seg_sum[rson[i]]);
}
void update(int l, int r, int root, int pos, int val) {
    int newroot = ++tot, tmp = newroot;
    int mid = (l + r) >> 1;
    if(l == r) {
        seg_sum[i] = val;
        seg_max[i] = val;
        return;
    }
    if(pos <= mid) {
        lson[newroot] = update(l, mid, lson[root], k, val);
        rson[newroot] = rson[root];
    } else {
        rson[newroot] = update(mid + 1, r, rson[root], k, val);
        lson[newroot] = lson[root];
    }

    push_up(newroot);
    return newroot;
}


int query(int i, int l, int r) {
    if(segTree[i].l == l && segTree[i].r == r)
        return segTree[i].Max;
    int mid = (segTree[i].l + segTree[i].r) / 2;
    if(r <= mid)
        return query(i << 1, l, r);
    else if(l > mid)
        return query((i << 1) | 1, l, r);
    else
        return max(query(i << 1, l, mid), query((i << 1) | 1, mid + 1, r));
}
int find(int u, int v) {
    int f1 = top[u], f2 = top[v];
    int tmp = 0;
    while(f1 != f2) {
        if(deep[f1] < deep[f2]) {
            swap(f1, f2);
            swap(u, v);
        }
        tmp = max(tmp, query(1, p[f1], p[u]));
        u = fa[f1];
        f1 = top[u];
    }
    if(u == v)
        return tmp;
    if(deep[u] > deep[v])
        swap(u, v);
    return max(tmp, query(1, p[son[u]], p[v]));
}
int e[MAXN]

/**< 主席树 */
int n, q, m, tot;
int a[MAXN], t[MAXN];
int times[MAXN];
int T[MAXN], lson[M], rson[M], c[M];
int seg_sum[M], seg_num[M];
int build(int l, int r) {
    int root = tot++;
    seg_sum[root] = 0;
    seg_num[root] = 0;
    if(l != r) {
        int mid = (l + r) >> 1;
        lson[root] = build(l, mid);
        rson[root] = build(mid + 1, r);
    }
    return root;
}
int update(int root, int pos, int val) {
    int newroot = ++tot, tmp = newroot;
    seg_sum[newroot] = seg_sum[root] + pos * val;
    seg_num[newroot] = seg_num[root] + val;
    seg_real[newroot] = seg_real[root] + reverse_rnk[pos] * val;
    int l = 1, r = m;
    while(l < r) {
        int mid = (l + r) >> 1;
        if(pos <= mid) {
            lson[newroot] = ++tot;
            rson[newroot] = rson[root];
            newroot = lson[newroot];
            root = lson[root];
            r = mid;
        } else {
            rson[newroot] = ++tot;
            lson[newroot] = lson[root];
            newroot = rson[newroot];
            root = rson[root];
            l = mid + 1;
        }
        seg_sum[newroot] = seg_sum[root] + pos * val;
        seg_num[newroot] = seg_num[root] + val;
        seg_real[newroot] = seg_real[root] + reverse_rnk[pos] * val;
    }
    return tmp;
}
long long query(int root, int k) {
    if(seg_num[root] < k) {
        return  seg_real[root];
    }
    int l = 1, r = m;
    long long res = 0;
    while(l < r) {
        int mid = (l + r) >> 1;
        if(seg_num[lson[root]] >= k) {
            r = mid;
            root = lson[root];
        } else {
            res += seg_real[lson[root]];
            k -= seg_num[lson[root]];
            root = rson[root];
            l = mid + 1;
        }
    }
    if(l == r && k != 0)
        res += reverse_rnk[l] * k;
    return res;
}
void _copy(int x, int y) {
    lson[x] = lson[y];
    rson[x] = rson[y];
    seg_sum[x] = seg_sum[y];
    seg_num[x] = seg_num[y];
    seg_real[x] = seg_real[y];
}


int city_num, event_num;
int raw_city[100000 + 5][2];
void init() {

    tot = 0;
    memset(head, -1, sizeof(head));
    pos = 0;
    memset(son, -1, sizeof(son));

    cin >> city_num >> event_num;


    for(int i = 1; i <= city_num; i++) {
        cin >> raw_city[i][0] >> raw_city[i][1];
    }
    for(int i = 1; i <= city_num - 1; i++) {
        int u, v;
        cin >> u >> v;
        addedge(u, v);
        addedge(v, u);
    }
    dfs1(1, 0, 0);
    getpos(1, 1);
    /**< 建立线段树 */
    build(1, 1, pos - 1);
    T[0] = segTree[0];
    for(int i = 1; i <= )
    }


void work1() {
    n = m = rnk_cnt;

    T[0] = build(1, n);

    int cur_mission = 2;
    for(int i = 1; i <= time_num; i++) {
        T[i] = ++tot;
        _copy(T[i], T[i - 1]);
        while(brk_missions[cur_mission].pos == i) {
            T[i] = update(T[i], brk_missions[cur_mission].rnk, brk_missions[cur_mission].type);
            cur_mission++;
        }
    }

    int X, A, B, C;
    long long res = 1, K;
    for(int i = 1; i <= time_num; i++) {
        cin >> X >> A >> B >> C;
        K = 1 + (A * res + B) % C;
        cout << (res = query(T[X], K)) << endl;
    }
}

int main() {

#ifdef local
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif // local

    ios::sync_with_stdio(false);

    init();

    work1();

}
