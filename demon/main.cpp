#include<bits/stdc++.h>
#define local
#define debu
using namespace std;

#define MAXM    500000+5

int buf1[MAXM];

const int MAXN = 200005;
const int M = MAXN * 50;

int mission_num, time_num, rnk_cnt;
int reverse_rnk[MAXN];
struct mission {
    int start, finish, val, rnk;
    bool operator<(mission mission1) {
        return this->val < mission1.val;
    }
} missions[MAXN];

struct mission1 {
    int pos, rnk;
    int type;
    bool operator<(mission1 mission2) {
        return this->pos < mission2.pos;
    }
} brk_missions[MAXN * 2 + 5];

void init() {
    cin >> mission_num >> time_num;
    for(int i = 1; i <= mission_num; i++) {
        cin >> missions[i].start >> missions[i].finish >> missions[i].val;
    }
    sort(missions + 1, missions + 1 + mission_num);

    for(int i = 1; i <= mission_num; i++) {
        if(missions[i].val != missions[i - 1].val)
            missions[i].rnk = ++rnk_cnt;
        else {
            missions[i].rnk = rnk_cnt;
        }
        reverse_rnk[rnk_cnt] = missions[i].val;
    }

    for(int i = 1; i <= mission_num; i++) {
        brk_missions[i * 2].pos = missions[i].start;
        brk_missions[i * 2].type = 1;
        brk_missions[i * 2].rnk = missions[i].rnk;
        brk_missions[i * 2 + 1].pos = missions[i].finish;
        brk_missions[i * 2 + 1].type = -1;
        brk_missions[i * 2 + 1].rnk = missions[i].rnk;
    }
    sort(brk_missions+2,brk_missions+2+2*mission_num);
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
    int newroot = tot++, tmp = newroot;
    seg_sum[newroot] = seg_sum[root] + pos * val;
    seg_num[newroot] = seg_num[root] + val;
    seg_real[newroot] = seg_real[root] + reverse_rnk[pos] * val;
    int l = 1, r = m;
    while(l < r) {
        int mid = (l + r) >> 1;
        if(pos <= mid) {
            lson[newroot] = tot++;
            rson[newroot] = rson[root];
            newroot = lson[newroot];
            root = lson[root];
            r = mid;
        } else {
            rson[newroot] = tot++;
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
int query(int root, int k) {
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
            root = rson[root];
            k -= seg_num[lson[root]];
            l = mid + 1;
        }
    }
    if(l==r&&k!=0)  res+=reverse_rnk[l]*k;
    return res;
}
void _copy(int x, int y) {
    lson[x] = lson[y];
    rson[x] = rson[y];
    seg_sum[x] = seg_sum[y];
    seg_num[x] = seg_num[y];
}

void work1() {
    n = m = rnk_cnt;

    T[0] = build(1, n);

    int cur_mission = 2;
    for(int i = 1; i <= time_num; i++) {
        _copy(i, i - 1);
        while(brk_missions[cur_mission].pos == i){
            update(T[i], brk_missions[cur_mission].rnk,brk_missions[cur_mission].type);
            cur_mission++;
        }
    }

    int X, A, B, C, res = 1, K;
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
