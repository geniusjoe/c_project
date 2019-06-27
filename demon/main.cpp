#include<bits/stdc++.h>
#define loc
#define debu
using namespace std;

#define MAXM    500000+5

const int MAXN = 500005;

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
struct Node{
    int l,r;
    int Max;
}segTree[MAXN*3];
void build(int i,int l,int r){
    segTree[i].l=l;
    segTree[i].r=r;
    segTree[i].Max=0;
    if(l==r) return;
    int mid=(l+r)>>1;
    build(i<<1,l,mid);
    build((i<<1)|1,mid+1,r);
}
void push_up(int i){
    segTree[i].Max=max(segTree[i<<1].Max,segTree[(i<<1)|1].Max);
}
void update(int i,int k,int val){
    if(segTree[i].l==k&&segTree[i].r==k){
        segTree[i].Max=val;
        return;
    }
    int mid=(segTree[i].l+segTree[i].r)/2;
    if(k<=mid)  update(i<<1,k,val);
    else    update((i<<1)|1,k,val);
    push_up(i);
}
int query(int i,int l,int r){
    if(segTree[i].l==l&&segTree[i].r==r)
        return segTree[i].Max;
    int mid=(segTree[i].l+segTree[i].r)/2;
    if(r<=mid)  return query(i<<1,l,r);
    else if(l>mid)  return query((i<<1)|1,l,r);
    else return max(query(i<<1,l,mid),query((i<<1)|1,mid+1,r));
}
int find(int u,int v){
    int f1=top[u],f2=top[v];
    int tmp=0;
    while(f1!=f2){
        if(deep[f1]<deep[f2]){
            swap(f1,f2);
            swap(u,v);
        }
        tmp=max(tmp,query(1,p[f1],p[u]));
        u=fa[f1];f1=top[u];
    }
    if(u==v) return tmp;
    if(deep[u]>deep[v]) swap(u,v);
    return max(tmp,query(1,p[son[u]],p[v]));
}
int e[MAXN]


int lowbit(int x){
    return x&(-x);
}
int c[MAXN],;
int n;
int sum(int i){
    int s=0;
    while(i>0){
        s+=c[i];
        i-=lowbit(i);
    }
    return s;
}
void add(int i,int val){
    while(i<=n){
        c[i]+=val;
        i+=lowbit(i);
    }
}
void Change(int u,int v,int val){
    int f1=top[u],f2=top[v];
    int tmp=0;
    while(f1!=f2){
        if(deep[f1]<deep[f2]){
            swap(f1,f2);
            swap(u,v);
        }
        add(p[f1],val);
        add(p[u]+1,-val);
        u=fa[f1];
        f1=top[u];
    }
    if(deep[u]>deep[v]) swap(u,v);
    add(p[u],val);
    add(p[v]+1,-val);
}
int a[MAXN];

int city_num,event_num;
int raw_city[100000+5][2];
void init() {

    tot = 0;
    memset(head, -1, sizeof(head));
    pos = 0;
    memset(son, -1, sizeof(son));

    cin >> city_num>>event_num;


    for(int i=1;i<=city_num;i++){
        cin>>raw_city[i][0]>>raw_city[i][1];
    }
    for(int i=1;i<=city_num-1;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }
    dfs1(1,0,0);
    getpos(1,1);
    memset()
}


int n, q, m, tot;
int a[MAXN], t[MAXN];
int times[MAXN];
int T[MAXN], lson[M], rson[M], c[M];
int seg_sum[M], seg_num[M];
long long seg_real[M];
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
