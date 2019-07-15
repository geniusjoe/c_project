#include<bits/stdc++.h>
#define loca
#define debu
using namespace std;

const int MAXN = 100010;
const int M = MAXN * 30;
int n, q,m, tot;
int a[MAXN], t[MAXN];
int T[MAXN], lson[M], rson[M], c[M];

int q_cnt, tme_cnt;
struct time {       /**< type==1 为开始    type==2为结束  type==3为查询 */
    int type, date, val;
    bool operator < (time time1)
    return this->date < time1.date;
} times[MAXN];

struct que {
    int q_time, k;
} ques[MAXN];


void init() {
    scanf("%d", &q_num);
    int cur_type;
    scanf("%d", &cur_type);
    if(cur_type == 1) {
        int start, finish, val;
        scanf("%d%d%d", &start, &val, &finish);
        times[++tme_cnt].date = start;
        times[tme_cnt].type = 1;
        times[tme_cnt].val = val;
        times[++tme_cnt].date = finish + 1;
        times[tme_cnt].type = 2;
        times[tme_cnt].val = val;
    } else {
        int cur_time, cur_k;
        scanf("%d%d", &cur_time, &cur_k);
        ques[++q_cnt].q_time = cur_time;
        ques[q_cnt].k = cur_k;
        times[++tme_cnt].date = cur_time;
        times[++tme_cnt].type = 3;

    sort(times + 1, times + 1 + tme_cnt);

    m = unique(times + 1, times + 1 + tme_cnt)−times−1;

}

int build(int l, int r) {
    int root = tot++;
    c[root] = 0;
    if(l != r) {
        int mid = (l + r) >> 1;
        lson[root] = build(l, mid);
        rson[root] = build(mid + 1, r);
    }
    return root;
}
int hash(int x) {
        return lower_bound(times + 1, times + 1 + m0, x) − times;
}
int update(int root, int pos, int val) {
    int newroot = tot++, tmp = newroot;
    c[newroot] = c[root] + val;
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
        c[newroot] = c[root] + val;
    }
    return tmp;
}
int query(int left_root, int right_root, int k) {
    int l = 1, r = m;
    while( l < r) {
        int mid = (l + r) >> 1;
        if(c[lson[left_root]]−c[lson[right_root]] >= k ) {
            r = mid;
            left_root = lson[left_root];
            right_root = lson[right_root];
        } else {
            l = mid + 1;
            k − = c[lson[left_root]] − c[lson[right_root]];
            left_root = rson[left_root];
            right_root = rson[right_root];
        }
    }
    return l;
}
int main() {
#ifdef local
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif // local

    int T;
    scanf("%d", &T);
    while(T--) {
        init();
        int cnt1=1;

        T[0] = build(1, 1000000+5);

        for(int i = 1; i <=m; i++) {
            T[i]=T[i-1];
            while(hash(times[cnt1].date)==i){
                if(times[cnt1].type==1)
                    update(T[i],times[cnt1].val,1);
                else if(times[cnt1].type==2)
                    update(T[i],times[cnt1].val,-1);
                cnt1++;
            }
        }



            tot = 0;
            for(int i = 1; i <= n; i++)
                scanf("%d", &a[i]);
            Init_hash();
            T[n + 1] = build(1, m);
            for(int i = n; i ; i−−) {
                int pos = hash(a[i]);
                T[i] = update(T[i + 1], pos, 1);
            }
            while(q−−) {
                int l, r, k;
                scanf("%d%d%d", &l, &r, &k);
                printf("%d\n", t[query(T[l], T[r + 1], k)]);
            }
        }
    }


    return 0;
}



}
