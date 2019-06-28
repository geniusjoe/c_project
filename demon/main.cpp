#include<bits/stdc++.h>
#define local
#define debu
using namespace std;

#define MAXM     500000+5

const int MAXN = 500025;
const int M = MAXN * 40;

/**< 树链剖分 */
struct Edge {
    int to, next;
} edge[MAXN * 2];
int head[MAXN], TOT;
int top[MAXN];
int fa[MAXN];
int deep[MAXN];
int num[MAXN];
int p[MAXN];
int fp[MAXN];
int son[MAXN];
int pos;

/**< 主席树 */
int n, q, m,tot;
int a[MAXN], t[MAXN];
int times[MAXN];
int T[M], lson[M], rson[M], c[M];
int seg_sum[M], seg_max[M];
int city_num, event_num;
int raw_city[100000 + 5][2];

/**< 树链剖分 */
void addedge(int u, int v) {
    edge[TOT].to = v;
    edge[TOT].next = head[u];
    head[u] = TOT++;
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
int build(int l, int r) {
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
    seg_sum[i] = seg_sum[lson[i]] + seg_sum[rson[i]];
}
int update(int l, int r, int root, int pos, int val) {
    int newroot = ++tot;
    int mid = (l + r) >> 1;
    if(l == r) {
        seg_sum[newroot] = val;
        seg_max[newroot] = val;
        return newroot;
    }
    if(pos <= mid) {
        lson[newroot] = update(l, mid, lson[root], pos, val);
        rson[newroot] = rson[root];
    } else {
        rson[newroot] = update(mid + 1, r, rson[root], pos, val);
        lson[newroot] = lson[root];
    }
    push_up(newroot);
    return newroot;
}

int query(int l, int r, int x, int y, int root, int type) { /**< type==0 代表最大值， type==1 代表求和 */
    if(l == x && r == y) {
        if(type == 0)
            return seg_max[root];
        else
            return seg_sum[root];
    }

    int mid = (l + r) >> 1;
    if(mid >= y)
        return query(l, mid, x, y, lson[root], type);
    else if(mid < x)
        return query(mid + 1, r, x, y, rson[root], type);
    else {
        if(type == 0)
            return max(query(l, mid, x, y, lson[root], type), query(mid + 1, r, x, y, rson[root], type));
        if(type == 1)
            return query(l, mid, x, y, lson[root], type) + query(mid + 1, r, x, y, rson[root], type);
    }
}
int find(int u, int v, int type) {  /**< type==0 代表最大值， type==1 代表求和 */
    int f1 = top[u], f2 = top[v];
    int tmp = 0;
    while(f1 != f2) {
        if(deep[f1] < deep[f2]) {
            swap(f1, f2);
            swap(u, v);
        }
        if(type == 0)
            tmp = max(tmp, query(0, pos - 1, p[f1], p[u], T[raw_city[u][0]], type));
        else
            tmp += query(0, pos - 1, p[f1], p[u], T[raw_city[u][0]], type);
        u = fa[f1];
        f1 = top[u];
    }
    if(u == v)
        return tmp;
    if(deep[u] > deep[v])
        swap(u, v);
    if(type == 0)
        return max(tmp, query(0, pos - 1, p[u], p[v], T[raw_city[u][0]], type));
    else
        return tmp + query(0, pos - 1, p[u], p[v], T[raw_city[u][0]], type);
}
int e[MAXN];


void init() {
    TOT=tot = 0;
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
    T[0] = build(0, pos - 1);

    for(int i = 1; i <= MAXN; i++ ) {
        T[i] = T[0];
    }
    for(int i = 1; i <= city_num; i++) {
        T[raw_city[i][1]] = update(0, pos - 1, T[raw_city[i][1]], p[i], raw_city[i][0]);
    }
}


void work1() {
    for(int i = 1; i <= event_num; i++) {
        char tmp, tmp1, tmp2;
        int city1, city2;
        cin >> tmp1 >> tmp2 >> city1 >> city2;
        if(tmp1 == 'Q' && tmp2 == 'S') {
            cout << find(city1, city2, 1) << endl;
            continue;
        } else if(tmp1 == 'Q' && tmp2 == 'M') {
            cout << find(city1, city2, 0) << endl;
            continue;
        } else if(tmp1 == 'C' && tmp2 == 'C') {
            update(0, pos - 1, T[raw_city[city1][1]], p[city1], -raw_city[city1][0]);
            raw_city[city1][1] = city2;
            update(0, pos - 1, T[raw_city[city1][1]], p[city1], raw_city[city1][0]);
            continue;
        } else if(tmp1 == 'C' && tmp2 == 'W') {
            update(0, pos - 1, T[raw_city[city1][1]], p[city1], -raw_city[city1][0]);
            raw_city[city1][0] = city2;
            update(0, pos - 1, T[raw_city[city1][1]], p[city1], raw_city[city1][0]);
            continue;
        }
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
