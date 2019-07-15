#include<bits/stdc++.h>
#define loca
#define debu
using namespace std;

const int MAXN = 100010;
const int M = MAXN * 30;
int n,q,m0,m1,tot;
int a[MAXN], t[MAXN];
int T[MAXN], lson[M], rson[M], c[M];
int q_cnt,e_cnt,time_cnt,val_cnt;
int time[MAXN][2],val[MAXN];

struct event {
    int start,finish,val;
} events[MAXN];

struct que {
    int q_time,k;
} ques[MAXN];


void init() {
    scanf("%d",&q_num);
    int cur_type;
    scanf("%d",&cur_type);
    if(cur_type==1) {
        int start,finish,val;
        scanf("%d%d%d",&start,&val,&finish);
        events[++e_cnt].start=start;
        events[e_cnt].finish=finish;
        events[e_cnt].val=val;
    } else {
        int cur_time,cur_k;
        scanf("%d%d",&cur_time,&cur_k);
        ques[++q_cnt].q_time=cur_time;
        ques[q_cnt].k=cur_k;
    }

    for(int i=1; i<=e_cnt; i++) {
        time[++time_cnt]=events[i].start;
        time[++time_cnt]=events[i].finish;
        val[++val_cnt]=events[i].val;
    }
    for(int i=1; i<=q_cnt; i++) {
        time[++time_cnt]=ques[i].q_time;
    }

    sort(time+1,time+1+time_cnt);
    sort(val+1,val+1+val_cnt);

    m0 = unique(time+1,time+1+time_cnt)−time−1;
    m1=unique(val+1,val+1+val_cnt)−val−1;

}

int build(int l,int r) {
    int root = tot++;
    c[root] = 0;
    if(l != r) {
        int mid = (l+r)>>1;
        lson[root] = build(l,mid);
        rson[root] = build(mid+1,r);
    }
    return root;
}
int hash(int x,int type) {  /** 1表示查询时间下标,2表示查询值下标*/
    if(type==1)
        return lower_bound(time+1,time+1+m0,x) − time;
    else
        return lower_bound(val+1,val+1+m1,x)-val;
}
int update(int root,int pos,int val) {
    int newroot = tot++, tmp = newroot;
    c[newroot] = c[root] + val;
    int l = 1, r = m;
    while(l < r) {
        int mid = (l+r)>>1;
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
            l = mid+1;
        }
        c[newroot] = c[root] + val;
    }
    return tmp;
}
int query(int left_root,int right_root,int k) {
    int l = 1, r = m;
    while( l < r) {
        int mid = (l+r)>>1;
        if(c[lson[left_root]]−c[lson[right_root]] >= k ) {
            r = mid;
            left_root = lson[left_root];
            right_root = lson[right_root];
        } else {
            l = mid + 1;
            k −= c[lson[left_root]] − c[lson[right_root]];
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
    scanf("%d",&T);
    while(T--) {
        init();
        for(int i=1;i<=time_cnt;i++){

        }


        while(scanf("%d%d",&n,&q) == 2) {
            tot = 0;
            for(int i = 1; i <= n; i++)
                scanf("%d",&a[i]);
            Init_hash();
            T[n+1] = build(1,m);
            for(int i = n; i ; i−−) {
                int pos = hash(a[i]);
                T[i] = update(T[i+1],pos,1);
            }
            while(q−−) {
                int l,r,k;
                scanf("%d%d%d",&l,&r,&k);
                printf("%d\n",t[query(T[l],T[r+1],k)]);
            }
        }
    }


    return 0;
}



}
