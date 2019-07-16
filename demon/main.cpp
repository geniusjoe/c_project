#include<bits/stdc++.h>
#define loca
#define debu
using namespace std;

const int MAXN = 100010;
const int M = MAXN * 30;
int n, q,m, tot;
int a[MAXN], t[MAXN];
int lson[M], rson[M], c[M];
int T[MAXN],tme_buf[MAXN];

int q_cnt, tme_cnt;
struct timing{
    int type,date,val;
    bool operator <(timing time1)
    {
        return this->date<time1.date;
    }
}times[MAXN];

struct que {
    int q_time, k;
} ques[MAXN];


void init() {
    int cur_num;
    tme_cnt=q_cnt=0;
    cin>>cur_num;
    for(int i=1; i<=cur_num; i++) {
        int cur_type;
        cin>>cur_type;
        if(cur_type == 1) {
            int start, finish, val;
            cin>>start>>val>>finish;
            times[++tme_cnt].date = start;
            times[tme_cnt].type = 1;
            times[tme_cnt].val = val;
            times[++tme_cnt].date = finish + 1;
            times[tme_cnt].type = 2;
            times[tme_cnt].val = val;
        } else {
            int cur_time, cur_k;
            cin>>cur_time>>cur_k;
            ques[++q_cnt].q_time = cur_time;
            ques[q_cnt].k = cur_k;
            times[++tme_cnt].date = cur_time;
            times[tme_cnt].type = 3;
        }

        sort(times + 1, times + 1 + tme_cnt);
        for(int i=1;i<=tme_cnt;i++)
            tme_buf[i]=times[i].date;
        m = unique(tme_buf+1,tme_buf+1+tme_cnt)-tme_buf-1;
    }
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
int Hash(int x) {
    return lower_bound(tme_buf + 1, tme_buf + 1 + tme_cnt, x) - tme_buf;
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
int query(int root, int k) {
    int l = 1, r = m;
    if(c[root]<k)
        return -1;
    while( l < r) {
        int mid = (l + r) >> 1;
        if(c[lson[root]] >= k ) {
            r = mid;
            root = lson[root];
        } else {
            l = mid + 1;
            k -= c[lson[root]];
            root = rson[root];
        }
    }
    return l;
}
int main() {
#ifdef local
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif // local

    ios::sync_with_stdio(false);


    int k;
    cin>>k;
    for(int ii=1;ii<=k;ii++) {
        cout<<"Case "<<ii<<":"<<endl;
        tot=0;
        init();
        int cnt1=1;

        T[0]=build(1,1000000+5);

        for(int i = 1; i <=m; i++) {
            T[i]=T[i-1];
            while(Hash(times[cnt1].date)==i) {
                if(times[cnt1].type==1)
                    T[i]=update(T[i],times[cnt1].val,1);
                else if(times[cnt1].type==2)
                    T[i]=update(T[i],times[cnt1].val,-1);
                cnt1++;
            }
        }

        for(int i=1; i<=q_cnt; i++) {
            int num=Hash(ques[i].q_time);
            cout<<query(T[num],ques[i].k)<<endl;
        }
    }

    return 0;
}




